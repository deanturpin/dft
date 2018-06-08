CXX = g++-6
CCFLAGS = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -pg -g --coverage -O3

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

# Full range SVGs
svgs = $(addsuffix .svg, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file)))))

csv = $(addsuffix .csv, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file)))))
csv += $(addsuffix _zoom.csv, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file)))))

svgs = $(addsuffix .svg, $(basename $(foreach file, $(wildcard *.gnuplot), $(notdir $(file)))))

gnuplots = $(addsuffix .gnuplot, $(basename $(foreach file, $(wildcard *.csv), $(notdir $(file)))))

all_csv:
	$(MAKE) --jobs $(shell nproc) $(csv)

all: $(csv)
	# $(MAKE) --jobs $(shell nproc) $(gnuplots)
	# $(MAKE) --jobs $(shell nproc) $(svgs)

all_csvs: $(CSVs)

%.csv: wav/%.wav spectrum.o
	./spectrum.o $< > $@
	./spectrum.o $< 16 > $(basename $@)_zoom.csv

gnuplot = $(addsuffix .gnuplot, $(basename $<))
%.gnuplot: %.csv
	echo set terminal svg size 1500,900 > $(gnuplot)
	echo set output \"$(basename $<).svg\" >> $(gnuplot)
	echo set format y \"\" >> $(gnuplot)
	echo set xtics 10 >> $(gnuplot)
	echo set xtics rotate >> $(gnuplot)
	echo set xlabel \"Hz\" >> $(gnuplot)
	echo set grid xtics ytics >> $(gnuplot)
	echo set tics font \"Helvetica,10\" >> $(gnuplot)
	echo plot \"$<\" notitle with impulses >> $(gnuplot)

%.svg: %.gnuplot %.csv
	gnuplot $<

readme.md: $(svgs)
	./create_readme.sh > $@

clean:
	rm -f *.o *.gcda *.gcno *.svg *.csv readme.md
