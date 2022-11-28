default:
	g++ -c textures.cpp main.cpp -I SFML-2.5.1/include
	g++ main.o textures.o -o build/sfml-app -L SFML-2.5.1//lib -lsfml-graphics -lsfml-window -lsfml-system
	$(RM) main.o
	./build/sfml-app