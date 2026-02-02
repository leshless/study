#!/bin/bash

# Загружаем функцию из file.sh
source ./file.sh

# Выводим ошибку, если передано больше одного аргумента
if [ $# -ne 1 ]; then
    echo "Exactly one argument expected"
    exit 1
fi

# Проверяем, существует ли файл через функцию и выводим соответствующий текст
if file_exists $1; then
    echo "File \"$1\" exists"
else
    echo "File \"$1\" does not exist"
fi