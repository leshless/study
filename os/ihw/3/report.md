# Вариант 35
- Лещук Глеб Олегович, 249

# Условие
«Камень, ножницы, бумага» 1 — однокруговая система. N cтудентов, изнывающих от скуки на лекции по архитектуре компьютера и операционным системам решили организовать однокруговой турнир в игру «Камень, ножницы, бумага». Каждый с каждым при этом играет только один раз. За победу дается два очка, за ничью — одно, за поражение — ноль.
Требуется создать многопроцессное приложение, моделирующее турнир.
Каждый студент — отдельный процесс. Генерация камня, ножниц и бумаги в каждом процессе формируется случайно.

# Решение (4-6 баллов)
Запускается родительские процесс (судья), который запускает дочерние процессы (игроков). Взаимодействие "судьи" и "игроков" происходит через разделяемую память, отображаемую на адресное пространство процесса и с помощью неименованных семафоров. Реализовано корректное завершение и отчистка ресурсов при получении терминирующих сигналов от ОС. Каждый процесс выводит в стандартный поток логи о своей работе.

Для того чтобы запустить демо решения можно воспользоваться утилитой make:
```bash
make sample
```

Вывод программы:
```bash
./judge 5
[112027] Starting the rock-paper-scissors tournament
[112027] Initializing game between players 0 and 1
[112028] Player 0 has chosen the move PAPER
[112029] Player 1 has chosen the move PAPER
[112027] Draw between players 0 and 1
[112027] Initializing game between players 0 and 2
[112030] Player 0 has chosen the move PAPER
[112031] Player 2 has chosen the move PAPER
[112027] Draw between players 0 and 2
[112027] Initializing game between players 0 and 3
[112032] Player 0 has chosen the move PAPER
[112033] Player 3 has chosen the move PAPER
[112027] Draw between players 0 and 3
[112027] Initializing game between players 0 and 4
[112034] Player 0 has chosen the move PAPER
[112035] Player 4 has chosen the move PAPER
[112027] Draw between players 0 and 4
[112027] Initializing game between players 1 and 2
[112036] Player 1 has chosen the move PAPER
[112037] Player 2 has chosen the move PAPER
[112027] Draw between players 1 and 2
[112027] Initializing game between players 1 and 3
[112038] Player 1 has chosen the move PAPER
[112039] Player 3 has chosen the move PAPER
[112027] Draw between players 1 and 3
[112027] Initializing game between players 1 and 4
[112040] Player 1 has chosen the move PAPER
[112041] Player 4 has chosen the move PAPER
[112027] Draw between players 1 and 4
[112027] Initializing game between players 2 and 3
[112042] Player 2 has chosen the move PAPER
[112043] Player 3 has chosen the move PAPER
[112027] Draw between players 2 and 3
[112027] Initializing game between players 2 and 4
[112044] Player 2 has chosen the move PAPER
[112045] Player 4 has chosen the move PAPER
[112027] Draw between players 2 and 4
[112027] Initializing game between players 3 and 4
[112046] Player 3 has chosen the move SCISSORS
[112047] Player 4 has chosen the move PAPER
[112027] Player 3 has defeated player 4
[112027] Winner of the tournament is player 3 with total score of 5
```

# Решение (4-6 баллов)
Запускаются процессы "игроков" и создают объекты разделяемой памяти с определенным префиксом. Процесс "судья" при запуске ищет объекты разделяемой памяти и семафоры соответствущие игрокам и взаимодействует через них. После окончания турнира судья сообщает процессам-игрокам, что следует завершиться. Реализовано корректное завершение и отчистка ресурсов при получении терминирующих сигналов от ОС. Каждый процесс выводит в стандартный поток логи о своей работе.

Для того чтобы запустить демо решения можно воспользоваться утилитой make:
```bash
make sample
```

Вывод программы:
```bash
./launch_players.sh
Launching 5 players...
Player 0 started (PID: 112105)
Player 1 started (PID: 112106)
Player 2 started (PID: 112107)
Player 3 started (PID: 112108)
Player 4 started (PID: 112109)
./judge
Discovering ready players
Found player: 112109
Found player: 112108
Found player: 112107
Found player: 112106
Found player: 112105
Found player: 112101
Found 6 ready players, starting the tournament
Initializing game between players 0 and 1
Player 1 has defeated player 0
Initializing game between players 0 and 2
Player 0 has defeated player 2
Initializing game between players 0 and 3
Player 3 has defeated player 0
Initializing game between players 0 and 4
Player 0 has defeated player 4
Initializing game between players 0 and 5
Player 5 has defeated player 0
Initializing game between players 1 and 2
Draw between players 1 and 2
Initializing game between players 1 and 3
Player 1 has defeated player 3
Initializing game between players 1 and 4
Player 4 has defeated player 1
Initializing game between players 1 and 5
Player 1 has defeated player 5
Initializing game between players 2 and 3
Draw between players 2 and 3
Initializing game between players 2 and 4
Player 2 has defeated player 4
Initializing game between players 2 and 5
Player 2 has defeated player 5
Initializing game between players 3 and 4
Player 3 has defeated player 4
Initializing game between players 3 and 5
Player 3 has defeated player 5
Initializing game between players 4 and 5
Draw between players 4 and 5
Winner of the tournament is player 1 with total score of 7
```

Для наглядности вывода процессов-игроков можно предварительно запустить еще один процесс, возпользовавшись вторым терминалом или утилитой tmux.