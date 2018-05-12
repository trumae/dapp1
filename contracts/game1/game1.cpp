/**
 *  @file
 *
 * 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
 * 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
 * 1188888881111888888811118888888111188888811111881111111111888881111118888811111888888811
 * 1188111111111881118811118811111111188111881111881111111118811188131188111881111881111111
 * 1188111111111881118811118111111111188111881111881111111118811188111188111111111881111111
 * 1188888811111881118811118888888111188888811111881111111118888888111188111111111888888111
 * 1188111111111881118811111111188111188111111111881111111118811188111188111111111881111111
 * 1188111111111881118811111111188111188111111111881111111118811188111188111881111881111111
 * 1188888881111888888811118888888111188111111111888888811118811188111118888811111888888811
 * 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
 * 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
 */

#include <utility>
#include <vector>
#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/crypto.h>
#include <eosiolib/print.hpp>
#include <ctime>
#include <sstream>

#include "cppjsindex.hpp"

using namespace eosio;

class game1 : public eosio::contract {
  enum GameStatus { waiting, open, deadline, closed };
  
public:
  using contract::contract;
  
  game1(account_name self) :
    contract(self){}

  //@abi action
  void newgame(const uint64_t o) {
  }

  //@abi action
  void newplayer(const std::string login, const std::string pass) {    
    eosio_assert(login.size() > 6, "Login name too small");
    eosio_assert(pass.size() > 9, "Password too small");    
        
    player_index players(_self, _self);    
    auto p = players.find(cppjsindex::index(login.c_str()));
    eosio_assert(p == players.end(), "This name is already used");
    
    players.emplace( _self, [&]( auto& s ) { 
	//s.id = players.available_primary_key();
	s.id = cppjsindex::index(login.c_str());
	s.login = login;
	s.passhash = hashloginpass(login, pass);
	s.balance = 1000;
	});
  }
  
private:
  static checksum256 hashloginpass(const std::string &login, const std::string &pass) {
    const std::string saltpass = "salt@!#@@";    
    checksum256 ret;
    
    std::string ss = login + "_" + pass + saltpass;
    sha256((char *) ss.c_str(), ss.size(), &ret);
    
    return ret;
  }
  
  static bool is_equal(const checksum256& a, const checksum256& b) {
    return memcmp((const void *)&a, (const void *)&b, sizeof(checksum256)) == 0;
  }
  
  //@abi table game i64
  struct game {
    uint64_t          id;
    uint64_t          owner;
    std::string       name;

    uint64_t primary_key()const { return id; }

    EOSLIB_SERIALIZE( game,
		      (id)
		      (owner)
		      (name))
  };  
  typedef eosio::multi_index< N(game), game> game_index;
  
  //@abi table bet i64
  struct bet {
    uint64_t          id;
    uint64_t          idgame;
    uint64_t          iduser;
    uint32_t          team1;
    uint32_t          team2;    

    uint64_t primary_key()const { return id; }

    EOSLIB_SERIALIZE( bet,
		      (id)
		      (idgame)
		      (iduser)
		      (team1)
		      (team1))
  };
  typedef eosio::multi_index< N(bet), bet> bet_index;
  
  //@abi table player i64
  struct player {
    uint64_t          id;
    std::string       login;
    checksum256       passhash;
    uint64_t          balance;

    uint64_t primary_key()const { return id; }

    EOSLIB_SERIALIZE( player,
		      (id)
		      (login)
		      (passhash)
		      (balance))
  };
  typedef eosio::multi_index< N(player), player> player_index;

  struct tconfig {
	  account_name application;

	  EOSLIB_SERIALIZE( tconfig, (application) )
  };
  typedef singleton<N(tconfigs), tconfig>  state_config;
};

EOSIO_ABI( game1, (newgame) (newplayer))
