#!/bin/bash

# Выводим ошибку, если передано больше одного аргумента
if [ $# -ne 1 ]; then
    echo "Exactly one argument expected"
    exit 1
fi

# Объявляем переменные
n=$1
i=0
a=0
b=1

# Итерируемся
while ((i < n-1))
do
    t=$b
    ((b = a + b))
    ((a = t))
    ((i++))
done

# Выводим результат
echo "fib($n)=$b"