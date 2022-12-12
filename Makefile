all:
	clang++ -std=c++2a game.cpp player.cpp card.cpp tile.cpp unclaimedTile.cpp claimedTile.cpp upgradedTile.cpp

clean:
	rm *.o test

