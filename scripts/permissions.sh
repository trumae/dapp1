cleos -u http://192.168.0.111:8888 set account permission --max-cpu-usage-ms 1000 game1 eosio EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M
cleos -u http://192.168.0.111:8888 set account permission --max-cpu-usage-ms 0 --max-net-usage 0 game1 eosio EOS7rMZfsA4yucaLyuEzAiBrhKj221qABT5zuKqtsq1Q1a1iVxe8M
cleos -u http://192.168.0.111:8888 get account game1
