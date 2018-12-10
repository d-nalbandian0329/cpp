include_dir = ../header/
g++_options = -std=c++17 -Wall --pedantic-errors -include $(include_dir)all.h

hello : hello.cpp
	g++ $(g++_options) -o hello hello.cpp

run :
	./hello

clean :
	rm -Rf ./hello

.PHONY : run clean
