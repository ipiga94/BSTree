main.exe: main.o
	g++ main.o -o main.out

main.o: main.cpp BSTree.h
	g++ -c main.cpp -o main.o