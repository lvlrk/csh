CXX=g++
CXXFLAGS=-O2 -std=c++2b
SOURCES=src/new.cpp
OBJECTS=new.o
TARGET=csh

all: $(TARGET)

build: $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -c

$(TARGET): build $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)
