#! /bin/bash

dialog --clear

next=about
while : ; do
    case "$next" in
	about)
	    next=name
	    dialog --backtitle 'Register' \
		   --msgbox 'Enter with your username and password' 0 0
	    ;;
	name)
	    previous=about
	    next=pass1
	    name=$(dialog --stdout \
			  --backtitle 'Register' \
			  --inputbox 'User Name:' 0 0)
	    ;;
	pass1)
	    previous=name
	    next=pass2
	    pass1=$(dialog --stdout \
			  --backtitle 'Register' \
			  --passwordbox 'Password:' 0 0)	    
	    ;;
	pass2)
	    previous=pass1
	    next=done
	    pass2=$(dialog --stdout \
			   --backtitle 'Register' \
			   --passwordbox 'Password again:' 0 0)
	    break
	    ;;
	*)	   
	    echo Aborting ...
	    exit
    esac
    
    ret=$?
    [ $ret -eq 1   ] && next=$previous   
    [ $ret -eq 255 ] && break                
done


if [ "$pass1" = "$pass2" ]; then
    res=$(cleos  -u http://192.168.0.111:8888/ --wallet-url http://192.168.0.111:8899  push action game1 newplayer "[\"$name\",\"$pass1\"]" -p game1)
    if [ -z $res ]; then
	dialog --backtitle 'Register' \
	       --msgbox "Error. wallet locked? $res" 0 0
    else
	dialog --backtitle 'Register' \
	       --msgbox "registered with sucess!!" 0 0
    fi
else
    dialog --backtitle 'Register' \
	   --msgbox 'Password not equals' 0 0
fi
