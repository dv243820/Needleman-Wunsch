CXX = g++
CXXFLAGS = -Wall -Werror
SRC = nw.cc
EXECUTABLE = nw.out

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(SRC)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

.PHONY: all run clean