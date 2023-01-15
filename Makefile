# Compiler
CXX := g++
CFLAGS=-Wall --std=c++11
# Libs
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
OBJECTS=PhotoMagic.o LFSR.o
# App name
EXECUTABLE=PhotoMagic

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LIBS)

clean:
	rm -rf ${EXECUTABLE} *.o

