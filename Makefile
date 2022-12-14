all:
	clang++ -g -std=c++2a game.cpp player.cpp card.cpp tile.cpp unclaimedTile.cpp claimedTile.cpp upgradedTile.cpp road.cpp

clean:
	rm *.o test

