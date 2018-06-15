CXX = g++-6
CCFLAGS = -std=c++14 --all-warnings --extra-warnings \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -g --coverage -O3

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

all: images readme.md

images: dft.o
	$(foreach file, $(wildcard wav/*.wav), time ./dft.o $(file);)

readme.md:
	./create_readme.sh > $@

clean:
	rm -f *.o *.gcda *.gcno wav/*.gnuplot wav/*.csv readme.md
