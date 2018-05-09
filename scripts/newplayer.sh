echo "Your login:"
read login
echo "password:"
read password 

cleos -u http://127.0.0.1:8888/ push action game1 newplayer "[\"$login\",\"$password\"]" -p game1
