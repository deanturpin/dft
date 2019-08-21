CXX ?= g++-8
CXXFLAGS ?= --std=c++2a --all-warnings --extra-warnings \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor -O1

%.o: %.cpp
	$(CXX) -o $@ $< $(CXXFLAGS)

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
