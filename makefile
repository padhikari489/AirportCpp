#Pawan Raj Adhikari UTID:1001669750
SRC= airports.cpp  

OBJ = $(SRC:.cpp=.o)

EXE = $(SRC:.cpp=)
 
CFLAGS = -g -std=c++11 -Wall -g -O0

all : $(EXE)
 
$(EXE): $(OBJ)
	g++ $(CFLAGS) $(OBJ) -o $(EXE) 

$(OBJ) : $(SRC)
	g++ -c $(CFLAGS) $(SRC) -o $(OBJ) 
	
clean:
	-rm -r $(EXE)
	-rm -f $(OBJ)
