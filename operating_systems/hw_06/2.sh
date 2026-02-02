#!/bin/bash

# Выводим ошибку, если передано больше одного аргумента
if [ $# -ne 1 ]; then
    echo "Exactly one argument expected"
    exit 1
fi

# Проверяем, существует ли файл и выводим соответствующий текст
if [ -f $1 ]; then
    echo "File \"$1\" exists"
else
    echo "File \"$1\" does not exist"
fi