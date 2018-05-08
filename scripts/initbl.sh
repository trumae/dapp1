URL=http://127.0.0.1:8888/
DIRCONTRACTS=eos/build/contracts/

# init

cleos -u ${URL} wallet create
cleos -u ${URL}  wallet unlock
cleos -u ${URL} set contract eosio eos/build/contracts/eosio.bios -p eosio
## cleos ${URL}-u ${URL} create key # so necessario se for gerar nova chave
cleos -u ${URL} wallet import 5KEFmzRkaWXZh2XF3SkPenzsGMrfdJvDGapmjBbKwZrGfU2ZWxa
cleos -u ${URL} create account eosio user  EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M
cleos -u ${URL} create account eosio tester  EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M

# deploy contract eosio.token
cleos -u ${URL} create account eosio eosio.token  EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M
cleos -u ${URL} set contract eosio.token build/contracts/eosio.token -p eosio.token

# deploy contract exchange
cleos -u ${URL} create account eosio exchange  EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M
cleos -u ${URL}set contract exchange build/contracts/exchange -p exchange

# deplay contract eosio.msig
cleos -u ${URL} create account eosio eosio.msig  EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M
cleos -u ${URL} set contract eosio.msig build/contracts/eosio.msig -p eosio.msig


