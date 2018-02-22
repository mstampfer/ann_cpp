CXX = g++
CXXFLAGS = -std=c++17 -Wall -MMD -Werror=vla 
OBJECTS = ann.o 
DEPENDS = ${OBJECTS:.o=.d}

EXEC = ann
${EXEC} : ${OBJECTS} 
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} 
-include ${DEPENDS} 
