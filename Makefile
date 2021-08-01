CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -g -Wall -MMD
OBJECTS = main.o ctorgame.o board.o  player.o strategy.o dice.o subject.o tile.o vertex.o edge.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = ctor

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

main.o: main.cc ctorgame.h board.h player.h tile.h vertex.h edge.h subject.h observer.h dice.h strategy.h
ctorgame.o: ctorgame.cc ctorgame.h board.h player.h tile.h vertex.h edge.h subject.h observer.h dice.h strategy.h
board.o: board.cc board.h tile.h player.h vertex.h edge.h subject.h observer.h dice.h strategy.h
player.o: player.cc player.h edge.h vertex.h observer.h tile.h subject.h dice.h strategy.h
dice.o: dice.cc dice.h strategy.h
strategy.o: strategy.cc strategy.h
subject.o: subject.cc subject.h observer.h
tile.o: tile.cc tile.h subject.h observer.h
vertex.o: vertex.cc vertex.h observer.h
edge.o: edge.cc edge.h vertex.h observer.h


.PHONY: clean

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
