COMP = g++-5.3.0
OBJS_TOUR = GameBoard_203537246.o GameFightInfo_203537246.o GameJokerChange_203537246.o GameManager_203537246.o \
AlgorithmRegistration.o GamePiece_203537246.o main_203537246.o MyPoint_203537246.o TournamentManager_203537246.o
OBJS_PLAYER = GameBoard_204573356.o GameFightInfo_204573356.o GameJokerChange_204573356.o GameMove_204573356.o \
GamePiece_204573356.o MyPoint_204573356.o RSPPlayer_204573356.o
EXEC = ex3
LIBS = -ldl
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG
CPP_COMP_FLAG_PLAYER = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG -fPIC

default:
	make all
	
all:
	make rps_lib
	make rps_tournament

rps_lib: RSPPlayer_204573356.so

rps_tournament: $(EXEC)

$(EXEC): $(OBJS_TOUR)
	$(COMP) $(OBJS_TOUR) -o $@ -lpthread -rdynamic $(LIBS)

RSPPlayer_204573356.so: $(OBJS_PLAYER)
	$(COMP) $(CPP_COMP_FLAG_PLAYER) -shared -Wl,-soname,RSPPlayer_204573356.so -o RSPPlayer_204573356.so $(OBJS_PLAYER)

RSPPlayer_204573356.o: RSPPlayer_204573356.cpp RSPPlayer_204573356.h \
 PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h \
 JokerChange.h AllGameParameters.h GameBoard_204573356.h GamePiece_204573356.h MyPoint_204573356.h \
 GameMove_204573356.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG_PLAYER) -c $*.cpp -mcmodel=large

GameBoard_204573356.o: GameBoard_204573356.cpp GameBoard_204573356.h Board.h GamePiece_204573356.h \
 PiecePosition.h MyPoint_204573356.h Point.h AllGameParameters.h
	$(COMP) $(CPP_COMP_FLAG_PLAYER) -c $*.cpp

GameBoard_203537246.o: GameBoard_203537246.cpp GameBoard_203537246.h Board.h GamePiece_203537246.h \
 PiecePosition.h MyPoint_203537246.h Point.h AllGameParameters.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

GameFightInfo_204573356.o: GameFightInfo_204573356.cpp GameFightInfo_204573356.h FightInfo.h MyPoint_204573356.h \
 Point.h
	$(COMP) $(CPP_COMP_FLAG_PLAYER) -c $*.cpp

GameFightInfo_203537246.o: GameFightInfo_203537246.cpp GameFightInfo_203537246.h FightInfo.h MyPoint_203537246.h \
 Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

GameJokerChange_204573356.o: GameJokerChange_204573356.cpp GameJokerChange_204573356.h JokerChange.h \
 MyPoint_204573356.h Point.h
	$(COMP) $(CPP_COMP_FLAG_PLAYER) -c $*.cpp

GameJokerChange_203537246.o: GameJokerChange_203537246.cpp GameJokerChange_203537246.h JokerChange.h \
 MyPoint_203537246.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

GameManager_203537246.o: GameManager_203537246.cpp GameManager_203537246.h PlayerAlgorithm.h Point.h \
 PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h GameBoard_203537246.h \
 GamePiece_203537246.h MyPoint_203537246.h AllGameParameters.h GameFightInfo_203537246.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

GameMove_204573356.o: GameMove_204573356.cpp GameMove_204573356.h Move.h MyPoint_204573356.h Point.h
	$(COMP) $(CPP_COMP_FLAG_PLAYER) -c $*.cpp

GamePiece_204573356.o: GamePiece_204573356.cpp GamePiece_204573356.h PiecePosition.h MyPoint_204573356.h Point.h
	$(COMP) $(CPP_COMP_FLAG_PLAYER) -c $*.cpp

GamePiece_203537246.o: GamePiece_203537246.cpp GamePiece_203537246.h PiecePosition.h MyPoint_203537246.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

MyPoint_204573356.o: MyPoint_204573356.cpp MyPoint_204573356.h Point.h
	$(COMP) $(CPP_COMP_FLAG_PLAYER) -c $*.cpp

MyPoint_203537246.o: MyPoint_203537246.cpp MyPoint_203537246.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

AlgorithmRegistration.o: AlgorithmRegistration.cpp \
 AlgorithmRegistration.h PlayerAlgorithm.h Point.h PiecePosition.h \
 Board.h FightInfo.h Move.h JokerChange.h TournamentManager_203537246.h \
 GameManager_203537246.h GameBoard_203537246.h GamePiece_203537246.h MyPoint_203537246.h AllGameParameters.h \
 GameFightInfo_203537246.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
TournamentManager_203537246.o: TournamentManager_203537246.cpp TournamentManager_203537246.h \
 GameManager_203537246.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h \
 FightInfo.h Move.h JokerChange.h GameBoard_203537246.h GamePiece_203537246.h MyPoint_203537246.h \
 AllGameParameters.h GameFightInfo_203537246.h AlgorithmRegistration.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
	
main_203537246.o:  main_203537246.cpp TournamentManager_203537246.h GameManager_203537246.h PlayerAlgorithm.h \
 Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h \
 GameBoard_203537246.h GamePiece_203537246.h MyPoint_203537246.h AllGameParameters.h GameFightInfo_203537246.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

clean:
	rm -f RSPPlayer_204573356.so *.o $(EXEC)
	
clean_rps_lib:
	rm -f $(OBJS_PLAYER)
	
clean_rps_tournament:
	rm -f $(OBJS_TOUR)
