TwoPipesTwoChildren TwoPipesThreeChildren dynpipe : TwoPipesTwoChildren.o TwoPipesThreeChildren.o DynPipe.o
	g++ -o TwoPipesTwoChildren TwoPipesTwoChildren.o
	g++ -o TwoPipesThreeChildren TwoPipesThreeChildren.o
	g++ -o dynpipe DynPipe.o
TwoPipesTwoChildren.o TwoPipesThreeChildren.o DynPipe.o: TwoPipesTwoChildren.cpp TwoPipesThreeChildren.cpp DynPipe.cpp
	g++ -c -g TwoPipesTwoChildren.cpp
	g++ -c -g TwoPipesThreeChildren.cpp
	g++ -c -g DynPipe.cpp
clean :
	rm -rv *.o 
	rm -rv dynpipe
	rm -rv TwoPipesThreeChildren
	rm -rv TwoPipesTwoChildren
