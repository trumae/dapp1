echo "Your login:"
read login
echo "password:"
read password 

cleos  -u http://192.168.0.111:8888/ --wallet-url http://192.168.0.111:8899  push action game1 newplayer "[\"$login\",\"$password\"]" -p game1
