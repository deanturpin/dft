CXX = g++-6
CCFLAGS = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -g --coverage

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

all: spectrum.o
	cat template.md > readme.md
	TZ=BST-1 date >> readme.md
	./spectrum.o
	gnuplot gnuplot.config
	echo '![](spectrum.png)' >> readme.md

clean:
	rm -f *.o
