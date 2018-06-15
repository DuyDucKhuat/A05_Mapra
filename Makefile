FLG = -std=c++11
FLG2 = -D_GLIBCXX_USE_CXX11_ABI=0
#main : CoordinateGraph.cpp unit.o
#	$(CXX) $(FLG) -g -o $@ $^
main: a_stern.cpp unit.o
        $(CXX) $(FLG) $(FLG2) -g -o $@ $^
.PHONY: clean
clean:
	rm -f main 
