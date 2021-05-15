
.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM

qwirkle: Tile.o Node.o LinkedList.o Cli.o GameState.o Player.o TileFactory.o GameEngine.o Board.o DataManager.o ScoreManager.cpp qwirkle.o Hand.o TileBag.o utils.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
