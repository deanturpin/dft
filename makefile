CXX = g++-6
CCFLAGS = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -pg -g --coverage -O3

.PRECIOUS: spectrum.o

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

# Full range SVGs
svgs = $(addsuffix .svg, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file)))))

csv = $(addsuffix .csv, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file)))))
csv_zoom = $(addsuffix _zoom.csv, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file)))))
gnuplot = $(patsubst %.csv, %.gnuplot, $(wildcard *.csv))
svg = $(patsubst %.gnuplot, %.svg, $(wildcard *.gnuplot))

JOBS := --jobs $(shell nproc)

all:
	$(MAKE) $(JOBS) $(csv) $(csv_zoom)
	$(MAKE) $(gnuplot)
	$(MAKE) $(svg)
	# $(MAKE) readme.md

%.csv: wav/%.wav spectrum.o
	./spectrum.o $< > $@

#######
%_full.svg: %_full.gnuplot
	gnuplot $<

%_full.gnuplot: %_full.csv
	./create_gnuplot_config.sh $(basename $<) > $@

%_full.csv: wav/%.wav spectrum.o
	./spectrum.o $< > $@

%_zoom.svg: %_zoom.gnuplot
	gnuplot $<

%_zoom.gnuplot: %_zoom.csv
	./create_gnuplot_config.sh $(basename $<) > $@

%_zoom.csv: wav/%.wav spectrum.o
	./spectrum.o $< 16 > $@

#######

# %_zoom.csv: wav/%.wav spectrum.o
# 	./spectrum.o $< 16 > $@
# 
# %.gnuplot: %.csv
# 	./create_gnuplot_config.sh $(basename $<) > $@
# 
# %.svg: %.gnuplot %.csv
# 	gnuplot $<

readme.md:
	./create_readme.sh > $@

clean:
	rm -f *.o *.gcda *.gcno *.svg *.csv readme.md *.gnuplot
