CXX ?= g++-6
DEBUG = -g --coverage -O3
CCFLAGS = -std=c++14 --all-warnings --extra-warnings \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

all:
	$(MAKE) dft.o
	$(MAKE) --silent --jobs $(shell nproc) $(images)
	$(MAKE) readme.md

%.wav.png: %.wav dft.o
	./dft.o $<

images = $(foreach file, $(wildcard wav/*.wav), $(file).png)

readme.md:
	./create_readme.sh > $@

clean:
	rm -f *.o *.gcda *.gcno wav/*.gnuplot wav/*.csv readme.md
