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
#include <eosiolib/crypto.h>
#include <eosiolib/eosio.hpp>
#include <ctime>

using namespace std;
using namespace eosio;

class game1 : public eosio::contract {
  enum GameStatus { waiting, open, deadline, closed };
  
public:
  game1(account_name self) :
    contract(self),
    bets(_self, _self),
    games(_self, _self),
    players(_self, _self){}

  //@abi action
  void newgame(const uint64_t o) {
  }

  //@abi action
  void newuser(const string login, const string pass) {
    eosio_assert(login.size() < 6, "Login name too small");
    eosio_assert(pass.size() < 9, "Password too small");

    
    
  }
  
private:
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
    string            login;
    string            passhash;

    uint64_t primary_key()const { return id; }

    EOSLIB_SERIALIZE( player,
		      (id)
		      (login)
		      (passhash))
  };
  typedef eosio::multi_index< N(player), player> player_index;

  bet_index bets;
  game_index games;
  player_index players;
};

EOSIO_ABI( game1, (newgame) (newuser))
