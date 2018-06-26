COMP = g++-5.3.0
OBJS = main.o
EXEC = ex4
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG


$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
main.o: main.cpp unit_test_util.h ex4_header.h GameBoard.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)