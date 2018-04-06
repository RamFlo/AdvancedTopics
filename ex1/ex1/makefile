COMP = g++-5.3.0
#put all your object files here
OBJS = GameBoard.o GamePiece.o main.o mainAux.o 
#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp mainAux.h GameBoard.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
mainAux.o: mainAux.h GameBoard.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GamePiece.o: GamePiece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameBoard.o: GameBoard.h mainAux.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)