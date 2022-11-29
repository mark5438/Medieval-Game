default:
	g++ -c textures.cpp main.cpp map_loader.cpp -I SFML-2.5.1/include
	g++ main.o textures.o map_loader.o -o build/sfml-app -L SFML-2.5.1//lib -lsfml-graphics -lsfml-window -lsfml-system
	$(RM) main.o
	./build/sfml-app