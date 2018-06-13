CXX = g++-6
CCFLAGS = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -g --coverage -O3

.PRECIOUS: dft.o

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

all:
	$(MAKE) --jobs $(shell nproc) $(svg_full) $(svg_zoom)
	$(MAKE) readme.md

svg_full = $(addsuffix _full.svg, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file)))))

svg_zoom = $(addsuffix _zoom.svg, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file)))))


# Full resolution rules
%.csv: wav/%.wav dft.o
	./dft.o $< > $@

%_full.svg: %_full.gnuplot
	gnuplot $<

%_full.gnuplot: %_full.csv
	./create_gnuplot_config.sh $(basename $<) > $@

%_full.csv: wav/%.wav dft.o
	./dft.o $< > $@

# Zoom rules
%_zoom.svg: %_zoom.gnuplot
	gnuplot $<

%_zoom.gnuplot: %_zoom.csv
	./create_gnuplot_config.sh $(basename $<) > $@

%_zoom.csv: wav/%.wav dft.o
	./dft.o $< 10 > $@

readme.md:
	./create_readme.sh > $@

clean:
	rm -f *.o *.gcda *.gcno *.svg readme.md
