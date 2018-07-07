FLG = -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0  -pedantic  -g  -Itest_b/lib/SFML-2.5.0/include
LIBS = -Ltest_b/lib/SFML-2.5.0/lib/ -lsfml-graphics -lsfml-window -lsfml-system

main: MazeVisualizer.o  ../unit.o
	$(CXX) $(LIBS)  -o $@ $^ $(LIBS)
MazeVisualizer.o: MazeVisualizer.cpp ../unit.h
	$(CXX) $(FLG) $^ 
.PHONY:
clean:
	rm -f main 
run: main
	export LD_LIBRARY_PATH=./test_b/lib/SFML-2.5.0/lib && kdbg ./sfml_test
