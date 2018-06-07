CXX = g++-6
CCFLAGS = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -pg -g --coverage -O3

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

svgs = $(addsuffix .svg, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file)))))

all: all_svgs readme.md

all_svgs:
	make --jobs $(shell nproc) $(svgs)

%.csv: wav/%.wav spectrum.o
	./spectrum.o $< > $@

gnuplot = $(addsuffix .gnuplot, $(basename $<))
%.gnuplot: %.csv
	echo set terminal svg size 1500,900 > $(gnuplot)
	echo set output \"$(basename $<).svg\" >> $(gnuplot)
	echo set format y \"\" >> $(gnuplot)
	echo set xtics 10 >> $(gnuplot)
	echo set xtics rotate >> $(gnuplot)
	echo set xlabel \"Hz\" >> $(gnuplot)
	echo set grid xtics ytics >> $(gnuplot)
	echo set tics font \"Helvetica,4\" >> $(gnuplot)
	echo plot \"$<\" notitle with impulses >> $(gnuplot)

%.svg: %.gnuplot %.csv
	gnuplot $<

readme.md: $(svgs)
	./create_readme.sh > $@

clean:
	rm -f *.o *.gcda *.gcno *.svg readme.md
