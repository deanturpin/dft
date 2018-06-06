CXX = g++-6
CCFLAGS = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -pg -g --coverage -O3

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

svgs = $(addprefix svg/, $(addsuffix .svg, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file))))))

all: $(svgs)

%.csv: wav/%.wav spectrum.o
	@echo $< to $@
	./spectrum.o > $@
	touch $@

svg/%.svg: %.csv
	@echo $< to $@

# all: spectrum.o
# 	time ./$<
# 	gnuplot fourier.config

clean:
	rm -f *.o *.gcda *.gcno *.csv
