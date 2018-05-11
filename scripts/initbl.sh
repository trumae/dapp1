URL=http://192.168.0.111:8888/
URLWALLET=http://192.168.0.111:8899
DIRCONTRACTS=../../eos/build/contracts/

# init
cleos -u ${URL} --wallet-url ${URLWALLET} wallet create
cleos -u ${URL} --wallet-url ${URLWALLET} wallet unlock
cleos -u ${URL} --wallet-url ${URLWALLET} set contract eosio ${DIRCONTRACTS}eosio.bios -p eosio
## cleos ${URL}-u ${URL} create key # so necessario se for gerar nova chave
cleos -u ${URL} --wallet-url ${URLWALLET} wallet import 5KEFmzRkaWXZh2XF3SkPenzsGMrfdJvDGapmjBbKwZrGfU2ZWxa
cleos -u ${URL} --wallet-url ${URLWALLET} create account eosio user  EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M
cleos -u ${URL} --wallet-url ${URLWALLET} create account eosio tester  EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M

# # deploy contract eosio.token
# cleos -u ${URL} create account eosio eosio.token  EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M
# cleos -u ${URL} set contract eosio.token ${DIRCONTRACTS}eosio.token -p eosio.token

# # deploy contract exchange
# cleos -u ${URL} create account eosio exchange  EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M
# cleos -u ${URL}set contract exchange ${DIRCONTRACTS}exchange -p exchange

# # deplay contract eosio.msig
# cleos -u ${URL} create account eosio eosio.msig  EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M
# cleos -u ${URL} set contract eosio.msig sio.msig -p eosio.msig

cleos -u ${URL} --wallet-url ${URLWALLET} create account eosio game1  EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M
