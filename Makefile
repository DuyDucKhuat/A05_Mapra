FLG = -std=c++11
FLG2 = -D_GLIBCXX_USE_CXX11_ABI=0 -D_GLIBCXX_DEBUG

#main : CoordinateGraph.cpp unit.o
#	$(CXX) $(FLG) -g -o $@ $^
main : a_stern.cpp  CoordinateGraph.o unit.o maze.o
	$(CXX) $(FLG) $(FLG2) -g -o $@ $^
CoordinateGraph.o : CoordinateGraph.cpp unit.h
	$(CXX) -c $(FLG)  $^
maze.o: maze.cpp unit.h
	$(CXX) -c -g $(FLG) $^

.PHONY: clean
clean:
	rm -f main CoordinateGraph.o maze.o
