#! /bin/bash

dialog --clear

while : ; do
    c=$(
	dialog --stdout                    \
	       --backtitle 'Welcome'       \
	       --menu 'Choose one option:' \
	       0 0 0                   \
	       1 'Login'     \
	       2 'Register'  \
	       0 'Quit'      )

    [ $? -ne 0 ] && break

    case "$c" in
	1) source login.sh ;;
	2) source register.sh ;;
	0) break ;;
    esac
done
