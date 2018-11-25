CXX ?= g++-8
DEBUG = -O3
CCFLAGS = -std=c++17 --all-warnings --extra-warnings \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

all:
	$(MAKE) dft.o
	$(MAKE) --jobs $(shell nproc) $(images)
	$(MAKE) readme.md

%.png: %.wav dft.o
	./dft.o $<

images = $(patsubst %.wav, %.png, $(wildcard wav/*.wav))

readme.md: $(images)
	./create_readme.sh > $@

clean:
	rm -f *.o *.gcda *.gcno wav/*.gnuplot wav/*.csv readme.md
