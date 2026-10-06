#!/bin/bash
# ./gen-random <n caractere> <lung max atom> <numere %> <zecimale %> <numere lipite %> <functii %> <puncte separator %> [<max separatori>]
# tr -d '\r' ca .ok sa aiba \n si pe Windows

# teste mici, facute de mana
T=1; printf '1a1a1a 1.a1.a\n' > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=2; printf '  abc234   234abc A a Ab 0 007x9Y 12 z9Z  \n' > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=3; printf 'A1 a1 11 1A 1a aA Aa AA aa\n' > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=4; printf '1. .1 1.. ..1 1.2.3.4 a.b.C 5.x 5.X 0.0.0 x1.5 3 .14\n' > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=5; printf '.3.14abc.x.5.1.2.3.7Ab.\n' > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;

# teste aleatoare, mici spre mari
T=6; ./gen-random 20 4 40 40 50 30 30 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=7; ./gen-random 50 5 40 40 50 30 30 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=8; ./gen-random 100 8 40 40 50 30 30 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=9; ./gen-random 255 10 40 40 60 40 30 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=10; ./gen-random 1000 10 40 40 60 40 30 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=11; ./gen-random 5000 20 40 40 50 40 30 5 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=12; ./gen-random 20000 50 40 40 50 40 30 5 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=13; ./gen-random 100000 100 40 40 50 40 30 5 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=14; ./gen-random 500000 200 40 40 50 40 30 10 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=15; ./gen-random 2000000 20 40 40 50 40 30 5 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=16; ./gen-random 2000000 1000 40 40 50 40 30 20 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
T=17; ./gen-random 2000000 100000 40 50 60 50 30 100 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;

#  de un caracter, separatori simpli: multi atomi
T=18; ./gen-random 2000000 1 40 40 50 40 50 1 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
# doar puncte ca separatori (inafara de cei de dupa intregi): fara spatii intre atomi
T=19; ./gen-random 2000000 3 50 50 50 40 100 1 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
# aproape toate numerele lipite de nume, multe zecimale
T=20; ./gen-random 2000000 3 90 70 95 30 50 1 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
# functii rare, cu litera mare oriunde in nume lungi
T=21; ./gen-random 2000000 5000 20 30 50 5 30 3 > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;

# teste hardcore
# un singur numar intreg de 2 milioane de cifre
T=22; { head -c 2000000 /dev/zero | tr '\0' 7; printf '\n'; } > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
# un singur numar zecimal de 2 milioane de caractere
T=23; { head -c 1000000 /dev/zero | tr '\0' 3; printf '.'; head -c 999999 /dev/zero | tr '\0' 1; printf '\n'; } > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
# un singur nume lung, cu litera mare abia la final
T=24; { head -c 1999999 /dev/zero | tr '\0' a; printf 'A\n'; } > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
# 1a1a1a...1a: un numar si o variabila
T=25; { yes 1a | head -n 1000000 | tr -d '\n'; printf '\n'; } > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
# 1.1.1.1...: zecimale 1.1, separate de puncte
T=26; { yes 1. | head -n 1000000 | tr -d '\n'; printf '\n'; } > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
# x.x.x...: variabile separate de puncte
T=27; { yes x. | head -n 1000000 | tr -d '\n'; printf '\n'; } > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
# 9.Z.9.Z...: cate un numar zecimal si o functie
T=28; { yes 9.Z | head -n 500000 | tr '\n' '.'; printf '\n'; } > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
# a.5.a.5...: variabile si zecimale 5. (punctul de dupa 5 il face zecimal)
T=29; { yes a.5 | head -n 500000 | tr '\n' '.'; printf '\n'; } > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
# doar spatii
T=30; { head -c 2000000 /dev/zero | tr '\0' ' '; printf '\n'; } > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
# doar puncte
T=31; { head -c 2000000 /dev/zero | tr '\0' '.'; printf '\n'; } > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
# un milion de spatii, apoi un atom lipit de final
T=32; { head -c 1000000 /dev/zero | tr '\0' ' '; printf '123.45abcDEF\n'; } > variabile.in; time ./variabile-brut; cp variabile.in teste/grader_test$T.in; tr -d '\r' < variabile.out > teste/grader_test$T.ok;
