# DPLL és CDCL SAT solverek, CNF generátor

A gyökér mappában találhatók a DPLL implementációjához tartozó forrásfájlok, a 3sat-ban a .cnf input fájlok, valamint a cnf_generator ban a CNF generátor szkriptje. Úgy van beállítva, hogy automatikusan a test.cnf-el kezdjen el dolgozni a DPLL (ezt most a main.cpp-ben lehet módosítani).

Egyelőre a DPLL van kész, valamint a CNF generátor félig-meddig működik.
A DPLL-en még tervezek módosításokat végezni, a sok kiíratást beadás előtt még ki fogom venni. 

## DPLL futtatása

```sh
g++ *.cpp -o main
./main
```

## CNF generátor futtatása

```sh
python3 main.py
```

