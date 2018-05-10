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
#include <eosiolib/eosio.hpp>
#include <ctime>

using namespace std;
using namespace eosio;

class game1 : public eosio::contract {
  enum GameStatus { waiting, open, deadline, closed };
  
public:
  game1(account_name self) :
    contract(self){}

  //@abi action
  void newgame(const uint64_t o) {
  }

  //@abi action
  void newplayer(const string login, const string pass) {
    eosio_assert(login.size() > 6, "Login name too small");
    eosio_assert(pass.size() > 9, "Password too small");

    player_index players(_self, _self);    
    auto p = players.find(STN(login));
    eosio_assert(p == players.end(), "This name is already used");
    
    players.emplace( _self, [&]( auto& s ) { 
	//s.id = players.available_primary_key();
	s.id = STN(login); 
	s.login = login;
	s.passhash = hashloginpass(login, pass);
    });
  }
  
private:
  static checksum256 hashloginpass(const string &login, const string &pass) {
    const string saltpass = "salt@!#@@";    
    checksum256 ret;
    
    string ss = login + "_" + pass + saltpass;
    sha256((char *) ss.c_str(), ss.size(), &ret);
    
    return ret;
  }
  
  static bool is_equal(const checksum256& a, const checksum256& b) {
    return memcmp((const void *)&a, (const void *)&b, sizeof(checksum256)) == 0;
  }

  /*
   * I try use std::hash, but with std::hash the constexpr modifier is not possible. 
   */
  static constexpr uint64_t STN(const string& str ) { 
    uint32_t len = 0;
    while( str[len] ) ++len;

    uint64_t value = 0;
    for( uint32_t i = 0; i <= 12; ++i ) {
      uint64_t c = 0;
      if( i < len && i <= 12 ) c = uint64_t(char_to_symbol( str[i] ));

      if( i < 12 ) {
	c &= 0x1f;
	c <<= 64-5*(i+1);
      }
      else {
	c &= 0x0f;
      }
      value |= c;
    }
    return value;
  }
  
  //@abi table game i64
  struct game {
    uint64_t          id;
    uint64_t          owner;
    string            name;

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
    //uint64_t        keylogin;
    string            login;
    checksum256       passhash;

    uint64_t primary_key()const { return id; }

    //uint64_t get_secondary()const { return keylogin; }

    EOSLIB_SERIALIZE( player,
		      (id)
		      //(keylogin)
		      (login)
		      (passhash))
  };
  typedef eosio::multi_index< N(player), player
			      ///,indexed_by< N(keylogin), const_mem_fun<player, uint64_t, &player::get_secondary> >
			      > player_index;


  struct tconfig {
	  account_name application;

	  EOSLIB_SERIALIZE( tconfig, (application) )
  };
  typedef singleton<N(tconfigs), tconfig>  state_config;

  //bet_index bets;
  //game_index games;

  /**
   * config.set(tconfig{application}, _self); // set singleton 
   * config.get().application();              // get singleton
   */ 
  //state_config config;

};

EOSIO_ABI( game1, (newgame) (newplayer))
