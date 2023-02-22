CC=gcc
CFLAG=-std=c17 -Wall 
LDFLAGS=-lncurses

ALL1=$(OBJ)main_1.o $(OBJ)liste.o $(OBJ)atr.o\
	 $(OBJ)outils.o $(OBJ)levenshtein.o

ALL2=$(OBJ)main_2.o $(OBJ)liste.o $(OBJ)atr.o\
	 $(OBJ)levenshtein.o $(OBJ)outils.o

ALL3=$(OBJ)main_3.o $(OBJ)liste.o\
	 $(OBJ)arbre_bk.o $(OBJ)levenshtein.o\
	 $(OBJ)outils.o

INTERFACE=$(OBJ)interface.o $(OBJ)liste.o\
		  $(OBJ)arbre_bk.o $(OBJ)levenshtein.o\
		  $(OBJ)outils.o

# .exe
BIN=./bin/
# .c
SRC=./src/
# .h
INC=./inc/
# .o
OBJ=./obj/

$(BIN)correcteur_1: $(ALL1)
	$(CC) -o $@ $^ $(CFLAG) $(LDFLAGS)

$(BIN)correcteur_2: $(ALL2)
	$(CC) -o $@ $^ $(CFLAG)$(LDFLAGS)

$(BIN)correcteur_3: $(ALL3)
	$(CC) -o $@ $^ $(CFLAG)$(LDFLAGS)

$(BIN)application: $(INTERFACE)
	$(CC) -o $@ $^ $(CFLAG)$(LDFLAGS)

main_1.o: $(SRC)main_1.c $(INC)atr.h
main_2.o: $(SRC)main_2.c $(INC)atr.h
main_3.o: $(SRC)main_3.c $(INC)arbre_bk.h
interface.o: $(SRC)interface.c $(INC)arbre_bk.h

atr.o: $(SRC)atr.c $(INC)atr.h $(INC)outils.h
arbre_bk.o: $(SRC)arbre_bk.c $(INC)arbre_bk.h $(INC)outils.h
outils.o: $(SRC)outils.c $(INC)outils.h $(INC)levenshtein.h $(INC)liste.h
levenshtein.o: $(SRC)levenshtein.c $(INC)levenshtein.h
liste.o: $(SRC)liste.c $(INC)liste.h

$(OBJ)%.o:  $(SRC)%.c
	$(CC) -c $< -o $@ $(CFLAG)

clean:
	rm -f $(OBJ)*.o
	rm $(BIN)*
	rm visualise.pdf
	rm visualise.dot