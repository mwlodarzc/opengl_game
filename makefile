TRGDIR=./
OBJ=./obj
NAME=a.out
FLAGS= -Wall -pedantic -lglfw -ldl -iquote libraries -Ibuild/include

${TRGDIR}/${NAME}: ${OBJ} ${OBJ}/main.o ${OBJ}/glad.o
		g++ -o ${TRGDIR}/${NAME} ${OBJ}/main.o ${OBJ}/glad.o ${FLAGS} 

${OBJ}:
	mkdir ${OBJ}

${OBJ}/glad.o: glad.c
		c++ -c ${FLAGS} -o ${OBJ}/glad.o glad.c 

${OBJ}/main.o: main.cpp
		g++ -c ${FLAGS} -o ${OBJ}/main.o main.cpp

clear:
	rm -r ${OBJ} ${NAME}