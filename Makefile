main: main.o mappa.o oggetti_mappa.o
	g++ -o game main.o mappa.o oggetti_mappa.o

main.o: main.cpp
	g++ -c main.cpp

mappa.o: mappa.cpp
	g++ -c mappa.cpp

oggetti_mappa.o: oggetti_mappa.cpp
	g++ -c oggetti_mappa.cpp

clean:
	rm *.o main
