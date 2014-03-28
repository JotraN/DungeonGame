bin/play: main.o game.o room.o sprite.o player.o block.o attack.o enemy.o inventory.o item.o weapon.o menu.o potion.o stairs.o\
			spinbaddie.o physattack.o rangeattack.o scoremanager.o
	g++ main.o game.o room.o sprite.o player.o block.o attack.o enemy.o inventory.o item.o weapon.o menu.o potion.o stairs.o\
		spinbaddie.o physattack.o rangeattack.o scoremanager.o\
		-o bin/play -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -Wall

main.o : src/main.cpp inc/game.h
	g++ -I inc -c src/main.cpp -o main.o

game.o: src/game.cpp inc/game.h
	g++ -I inc -c src/game.cpp -o game.o -lsfml-window

room.o: src/room.cpp inc/room.h 
	g++ -I inc -c src/room.cpp -o room.o -lsfml-graphics -lsfml-window -lsfml-system

sprite.o: src/sprite.cpp inc/sprite.h
	g++ -I inc -c src/sprite.cpp -o sprite.o -lsfml-graphics

player.o: src/player.cpp inc/player.h
	g++ -I inc -c src/player.cpp -o player.o -lsfml-audio

block.o: src/block.cpp inc/block.h
	g++ -I inc -c src/block.cpp -o block.o

attack.o: src/attack.cpp inc/attack.h
	g++ -I inc -c src/attack.cpp -o attack.o
	
physattack.o: src/physattack.cpp inc/physattack.h
	g++ -I inc -c src/physattack.cpp -o physattack.o

rangeattack.o: src/rangeattack.cpp inc/rangeattack.h
	g++ -I inc -c src/rangeattack.cpp -o rangeattack.o

enemy.o: src/enemy.cpp inc/enemy.h
	g++ -I inc -c src/enemy.cpp -o enemy.o

spinbaddie.o: src/spinbaddie.cpp inc/spinbaddie.h
	g++ -I inc -c src/spinbaddie.cpp -o spinbaddie.o

inventory.o: src/inventory.cpp inc/inventory.h
	g++ -I inc -c src/inventory.cpp -o inventory.o
	
item.o: src/item.cpp inc/item.h
	g++ -I inc -c src/item.cpp -o item.o

weapon.o: src/weapon.cpp inc/weapon.h
	g++ -I inc -c src/weapon.cpp -o weapon.o 	

menu.o: src/menu.cpp inc/menu.h
	g++ -I inc -c src/menu.cpp -o menu.o

potion.o: src/potion.cpp inc/potion.h
	g++ -I inc -c src/potion.cpp -o potion.o

stairs.o: src/stairs.cpp inc/stairs.h
	g++ -I inc -c src/stairs.cpp -o stairs.o

scoremanager.o: src/scoremanager.cpp inc/scoremanager.h
	g++ -I inc -c src/scoremanager.cpp -o scoremanager.o

clean:
	rm *.o
