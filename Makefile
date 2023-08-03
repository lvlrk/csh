CXX=g++
CXXFLAGS=-O2 -g
SOURCES=src/main.cpp
OBJECTS=main.o
TARGET=csh

all: $(TARGET)

build: $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -c

$(TARGET): build $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)
