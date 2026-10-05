CC = g++
CFLAGS = -c -Wall

TARGET = calc
OBJECTS = src/main.o src/calculator.o
LIB = libcalculator.a
LIB_OBJECTS = src/calculator.o

all: ${LIB} ${TARGET}

${LIB}: ${LIB_OBJECTS}
	ar rcs $@ $^

${TARGET}: src/main.o ${LIB}
	${CC} src/main.o -L. -lcalculator -o $@

src/%.o: src/%.cpp
	${CC} ${CFLAGS} $< -o $@

clean:
	rm -f ${TARGET} ${LIB} ${OBJECTS}

.PHONY: clean
