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
  game1(account_name self) : contract(self) {}

  //@abi action
  void newgame(const uint64_t o) {
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
		      ///(name)
		      )
  };
  
  /*
  //@abi table bet i64
  struct bet {
    uint64_t          id;
    uint64_t          idgame;
    uint64_t          iduser;
    uint32_t          team1;
    uint32_t          team2;    

    uint64_t primary_key()const { return id; }

    EOSLIB_SERIALIZE( bet, (id)(idgame)(iduser)(team1)(team1))
  };

  //@abi table player i64
  struct player {
    uint64_t          id;
    char              login[20];
    char              passhash[36];

    uint64_t primary_key()const { return id; }

    EOSLIB_SERIALIZE( player, (id)(login)(passhash))
  };
  */
  
};

EOSIO_ABI( game1, (newgame) )
