FLG = -std=c++11
FLG2 = -D_GLIBCXX_USE_CXX11_ABI=0
#main : CoordinateGraph.cpp unit.o
#	$(CXX) $(FLG) -g -o $@ $^
CoordinateGraph.o : unit.o
	$(CXX) -std=c++11 -c $< 
main : a_stern.cpp  CoordinateGraph.o unit.o
	$(CXX) $(FLG) $(FLG2) -g -o $@ $^

.PHONY: clean
clean:
	rm -f main CoordinateGraph.o
