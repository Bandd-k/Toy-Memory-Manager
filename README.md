
«Игрушечный» менеджер памяти, управляющий количество памяти ,которое вводит пользователь при запуске менеджера. Предпологаем ,что «игрушечное» машиное слово имеет размер 64 бита, т.е. каждая ячейка памяти имеет размер 8 байт. Это означает ,что за каждый запрос менеджер памяти может выделить или освободить блок памяти ,кратный 8-ми байтам. В частности это означает ,что если при выделении памяти требуется 1 байт, менеджер выделит 8 байт(7 из которых не будут использоваться).
