CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

ES := Encryption-Software
SRC     := src
INCLUDE := include
ESSRC1 := es_src.cpp
ESSRC2 := SHA256.cpp

EXECUTABLE  := a.exe

all: $(EXECUTABLE)

run: clean all
	clear
	./$(EXECUTABLE)

$(EXECUTABLE): $(SRC)/*.cpp $(ES)/$(SRC)/$(ESSRC1) $(ES)/$(SRC)/$(ESSRC2)
	@$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(ES)/$(INCLUDE) $^ -o $@

clean:
	@-rm *.exe