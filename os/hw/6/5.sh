#!/bin/bash

# Выводим ошибку, если передано больше одного аргумента
if [ $# -ne 1 ]; then
    echo "Exactly one argument expected"
    exit 1
fi

# Выводим строку для цвета символов
case $1 in
    black)   echo -ne "\033[0;30m" ;;
    red)     echo -ne "\033[0;31m" ;;
    green)   echo -ne "\033[0;32m" ;;
    yellow)  echo -ne "\033[0;33m" ;;
    blue)    echo -ne "\033[0;34m" ;;
    magenta) echo -ne "\033[0;35m" ;;
    cyan)    echo -ne "\033[0;36m" ;;
    white)   echo -ne "\033[0;37m" ;;
    *)       echo "Unknown color"; exit 1 ;;
esac

# Выводим корову
echo "   ^__^"
echo "   (oo)\_______"
echo "   (__)\       )\/\\"
echo "        ||----w |"
echo "        ||     ||"

# Сбрасываем цвет 
echo -ne "\033[0m"