FLG = -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0  -pedantic  -g  -Itest_b/lib/SFML-2.5.0/include
LIBS = -Ltest_b/lib/SFML-2.5.0/lib/ -lsfml-graphics -lsfml-window -lsfml-system

main : a_stern.cpp  CoordinateGraph.o unit.o maze.o
	$(CXX) $(FLG)   -g -o $@ $^ 
CoordinateGraph.o : CoordinateGraph.cpp unit.h
	$(CXX) $(FLG) -c  $^
maze.o: maze.cpp unit.h
	$(CXX)  $(FLG) -c $^

.PHONY: clean
clean:
	rm -f main CoordinateGraph.o maze.o
run: main
	export LD_LIBRARY_PATH=./test_b/lib/SFML-2.5.0/lib && kdbg ./sfml_test
gdb: main
	gdb -ex "set enviroment LD_LIBRARY_PATH=./test_b/lib/SFML-2.5.0/lib" sfml_test
