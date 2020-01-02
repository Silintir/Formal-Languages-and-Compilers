CXX = g++
MAIN = clear
SRC = clear.l

$(MAIN):	lex.yy.c
	$(CXX) -o $(MAIN) lex.yy.c

lex.yy.c:	$(SRC)
	lex $(SRC)

all:	$(MAIN)
