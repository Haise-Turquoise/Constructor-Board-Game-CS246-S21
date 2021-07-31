CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -g -Wall -MMD
OBJECTS = a6test.o board.o player.o tile.o subject.o vertex.o edge.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = ctor

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

a6test.o: a6test.cc board.h tile.h player.h vertex.h edge.h subject.h observer.h
board.o: board.cc board.h tile.h player.h vertex.h edge.h subject.h observer.h
player.o: player.cc player.h edge.h vertex.h observer.h tile.h subject.h
subject.o: subject.cc subject.h observer.h
tile.o: tile.cc tile.h subject.h observer.h
vertex.o: vertex.cc vertex.h observer.h
edge.o: edge.cc edge.h vertex.h observer.h


.PHONY: clean

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
