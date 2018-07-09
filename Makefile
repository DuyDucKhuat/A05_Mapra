FLG = -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0  -pedantic -IVisualizer.cpp/test_b/lib/SFML-2.5.0/include
LIBS = -LVisualizer.cpp/test_b/lib/SFML-2.5.0/lib/ -lsfml-graphics -lsfml-window -lsfml-system

main : a_stern.cpp  CoordinateGraph.o unit.o maze.o  MazeVisualizer.o c_graph_visualizer.p
	$(CXX) $(FLG)   -g -o $@ $^ $(LIBS)

CoordinateGraph.o : CoordinateGraph.cpp unit.h
	$(CXX) $(FLG) -c  $^
maze.o: maze.cpp unit.h
	$(CXX)  $(FLG) -c $^

MazeVisualizer.o: MazeVisualizer.cpp unit.h
	$(CXX) $(FLG) -c $^
c_graph_visualizer.o: c_graph_visualizer.cpp unit.h
	$(CXX) $(FLG) -c $^

.PHONY: clean
clean:
	rm -f main CoordinateGraph.o maze.o
run: main
	export LD_LIBRARY_PATH=./Visualizer.cpp/test_b/lib/SFML-2.5.0/lib &&./main
gdb: main
	gdb -ex "set enviroment LD_LIBRARY_PATH=./Visualizer.cpp/test_b/lib/SFML-2.5.0/lib" main
