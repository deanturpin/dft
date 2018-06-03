CXX = g++-6
CCFLAGS = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -g --coverage

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG) -c

all: spectrum

spectrum: spectrum.o fourier.o
	$(CXX) -o $@ $^ $(DEBUG)

clean:
	rm -f *.o spectrum

noise: spectrum
	arecord -q -f S16_LE -c1 -r 8000 | ./spectrum
