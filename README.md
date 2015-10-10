Russian
«Игрушечный» менеджер памяти, управляющий количество памяти ,которое вводит пользователь при запуске менеджера. Предпологаем ,что «игрушечное» машиное слово имеет размер 64 бита, т.е. каждая ячейка памяти имеет размер 8 байт. Это означает ,что за каждый запрос менеджер памяти может выделить или освободить блок памяти ,кратный 8-ми байтам. В частности это означает ,что если при выделении памяти требуется 1 байт, менеджер выделит 8 байт(7 из которых не будут использоваться).
English
Toy memory manger, which control amount of memory you entered. One word needs 64 bit, it means that every memory cell need 8 bytes. Manager can alloc or dealloc amount of memory like 8*N. It means that if user needs 1 byte manager will alloc 8 bytes.
