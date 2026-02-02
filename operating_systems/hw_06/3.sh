#!/bin/bash

# Загружаем переменные из config.sh в текущий процесс
source config.sh

# Выводим переменные из config.sh
echo "Config successfully loaded"
echo "Database connection: $DATABASE_URL:$DATABASE_PORT"
echo "Database credentials: $DATABASE_LOGIN ($DATABASE_PASSWORD)"