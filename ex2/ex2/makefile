COMP = g++-5.3.0
#put all your object files here
OBJS = AutoPlayerAlgorithm.o FilePlayerAlgorithm.o FilePlayerParser.o \
GameBoard.o GameFightInfo.o GameJokerChange.o GameManager.o GameMove.o \
GamePiece.o main.o MyPoint.o 
#The executabel filename DON'T CHANGE
EXEC = ex2
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
AutoPlayerAlgorithm.o: AutoPlayerAlgorithm.cpp AutoPlayerAlgorithm.h \
 PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h \
 JokerChange.h AllGameParameters.h GameBoard.h GamePiece.h MyPoint.h \
 GameMove.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
FilePlayerAlgorithm.o: FilePlayerAlgorithm.cpp FilePlayerAlgorithm.h \
 PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h \
 JokerChange.h FilePlayerParser.h GamePiece.h MyPoint.h \
 AllGameParameters.h GameJokerChange.h GameMove.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
FilePlayerParser.o: FilePlayerParser.cpp FilePlayerParser.h \
 PiecePosition.h GamePiece.h MyPoint.h Point.h AllGameParameters.h \
 GameJokerChange.h JokerChange.h GameMove.h Move.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameBoard.o: GameBoard.cpp GameBoard.h Board.h GamePiece.h \
 PiecePosition.h MyPoint.h Point.h AllGameParameters.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameFightInfo.o: GameFightInfo.cpp GameFightInfo.h FightInfo.h MyPoint.h \
 Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameJokerChange.o: GameJokerChange.cpp GameJokerChange.h JokerChange.h \
 MyPoint.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameManager.o: GameManager.cpp GameManager.h PlayerAlgorithm.h Point.h \
 PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h \
 FilePlayerAlgorithm.h FilePlayerParser.h GamePiece.h MyPoint.h \
 AllGameParameters.h GameJokerChange.h GameMove.h AutoPlayerAlgorithm.h \
 GameBoard.h GameFightInfo.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameMove.o: GameMove.cpp GameMove.h Move.h MyPoint.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GamePiece.o: GamePiece.cpp GamePiece.h PiecePosition.h MyPoint.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
main.o: main.cpp GameManager.h PlayerAlgorithm.h Point.h PiecePosition.h \
 Board.h FightInfo.h Move.h JokerChange.h FilePlayerAlgorithm.h \
 FilePlayerParser.h GamePiece.h MyPoint.h AllGameParameters.h \
 GameJokerChange.h GameMove.h AutoPlayerAlgorithm.h GameBoard.h \
 GameFightInfo.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MyPoint.o: MyPoint.cpp MyPoint.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)