Kompilator prostego jezyka imperatywnego napisany w ramach laboratorium kursu Jezyki Formalne i Teoria Translacji

Autor: Benjamin Jurczok
Nr indeksu: 244760

Pliki:
Makefile - służący do kompilacji projektu
lex.l - plik lexera (flex)
grammar.y - plik parsera (bison)
asm.cpp/asm.hpp - zawierają definicje i deklaracje obiektów słóżących do tworzenia pseudoassemblera
symbols.cpp/symbols.hpp - zawierają definicje i deklaracje tablicy symboli jak i pojedyńczego symbolu
code_gen.cpp/code_gen.hpp - zawierają funkcje i definicje funkcji służących do obsługi strumienia błędów i generacji kodu z wektora
ast.cpp/ast.hpp - zawierają obiektową strukturę Abstract Syntax Tree oraz deklaracje objektów z funkcjami generującymi pseudoassembler
main.cpp - główny plik programu, jest odpowiedzialny za czytanie pliku wejściowego, linkowanie go do pozostałych funkcji, a nastepnie zapis do pliku wynikowego

Użyte narzędzia:
flex 2.6.4
clang (clang++) 9.0.1
bison 3.5

Projekt powinien być kompilowany przy pomocy clang++, nie był on testowany dla g++. (Paczka 'clang-9' dla Ubuntu 18.04 LTS)

Sposób użycia:
W celu skompilowania projektu należy użyć polecenia 'make'. Program wynikowy będzie znajdował się pod nazwą 'kompilator' w katalogu 'binary'.

Kompilator uruchamia się komendą <./kompilator 'plik_wejściowy' 'plik_wynikowy'>. 