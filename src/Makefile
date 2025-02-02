test: main.o my_cv.o imgio.o data.o
	g++ -o test main.o my_cv.o imgio.o data.o -lm

main.o: main.cpp
	g++ -c main.cpp
my_cv.o: my_cv.cpp my_cv.hpp
	g++ -c my_cv.cpp
imgio.o: imgio.cpp imgio.hpp
	g++ -c imgio.cpp
data.o: data.cpp data.hpp
	g++ -c data.cpp

clean:
	del -rf *.o
