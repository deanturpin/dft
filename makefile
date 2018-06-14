CXX = g++-6
CCFLAGS = -std=c++14 --all-warnings --extra-warnings \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -g --coverage -O3

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

all: readme.md

images: dft.o
	$(foreach file, $(wildcard wav/*.wav), $(shell ./dft.o $(file)))

readme.md: images
	./create_readme.sh > $@

clean:
	rm -f *.o *.gcda *.gcno wav/*.svg wav/*.gnuplot wav/*.csv readme.md
