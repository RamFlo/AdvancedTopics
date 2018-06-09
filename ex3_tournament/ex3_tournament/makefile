COMP = g++-5.3.0
OBJS_TOUR = GameBoard.o GameFightInfo.o GameJokerChange.o GameManager.o \
AlgorithmRegistration.o GamePiece.o main.o MyPoint.o TournamentManager.o
OBJS_PLAYER = GameBoard.o GameFightInfo.o GameJokerChange.o GameMove.o \
GamePiece.o MyPoint.o RSPPlayer_204573356.o
EXEC = ex3
LIBS = -ldl
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

default:
	make all
	
all:
	make rps_lib
	make rps_tournament
	
rps_lib: CPP_COMP_FLAG += -fPIC
rps_lib: clean_rps_tournament
rps_lib: RSPPlayer_204573356.so

rps_tournament: clean_rps_lib
rps_tournament: $(EXEC)

$(EXEC): $(OBJS_TOUR)
	$(COMP) $(OBJS_TOUR) -o $@ -lpthread -rdynamic $(LIBS)

RSPPlayer_204573356.so: $(OBJS_PLAYER)
	$(COMP) $(CPP_COMP_FLAG) -shared -Wl,-soname,RSPPlayer_204573356.so -o RSPPlayer_204573356.so $(OBJS_PLAYER)
	
RSPPlayer_204573356.o: RSPPlayer_204573356.cpp RSPPlayer_204573356.h \
 PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h \
 JokerChange.h AllGameParameters.h GameBoard.h GamePiece.h MyPoint.h \
 GameMove.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp -mcmodel=large
	
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
 PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h GameBoard.h \
 GamePiece.h MyPoint.h AllGameParameters.h GameFightInfo.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
GameMove.o: GameMove.cpp GameMove.h Move.h MyPoint.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
GamePiece.o: GamePiece.cpp GamePiece.h PiecePosition.h MyPoint.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
MyPoint.o: MyPoint.cpp MyPoint.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
AlgorithmRegistration.o: AlgorithmRegistration.cpp \
 AlgorithmRegistration.h PlayerAlgorithm.h Point.h PiecePosition.h \
 Board.h FightInfo.h Move.h JokerChange.h TournamentManager.h \
 GameManager.h GameBoard.h GamePiece.h MyPoint.h AllGameParameters.h \
 GameFightInfo.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
TournamentManager.o: TournamentManager.cpp TournamentManager.h \
 GameManager.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h \
 FightInfo.h Move.h JokerChange.h GameBoard.h GamePiece.h MyPoint.h \
 AllGameParameters.h GameFightInfo.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
main.o:  main.cpp TournamentManager.h GameManager.h PlayerAlgorithm.h \
 Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h \
 GameBoard.h GamePiece.h MyPoint.h AllGameParameters.h GameFightInfo.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

clean:
	rm -f RSPPlayer_204573356.so *.o $(EXEC)
	
clean_rps_lib:
	rm -f $(OBJS_PLAYER)
	
clean_rps_tournament:
	rm -f $(OBJS_TOUR)
