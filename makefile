CXX = g++-6
CCFLAGS = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -pg -g --coverage -O3

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

svgs = $(addprefix svg/, $(addsuffix .svg, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file))))))

gnuplots = $(addsuffix .gnuplot, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file)))))

all: $(svgs)

%.csv: wav/%.wav spectrum.o
	@echo $< to $@
	./spectrum.o > $@

# gnuplot = $(addsuffix .gnuplot, $(basename $<))
%.gnuplot: %.csv
	@echo $< to $(basename $@).gnuplot

# @echo set terminal svg size 1024,640 > $(gnuplot)
# set output "fourier.svg" > $(gnuplot)
# set xtics 10 > $(gnuplot)
# set xtics rotate > $(gnuplot)
# set xlabel "Hz" > $(gnuplot)
# set grid xtics ytics > $(gnuplot)
# set tics font "Helvetica,8" > $(gnuplot)
# plot "fourier.csv" notitle with impulses > $(gnuplot)

svg/%.svg: %.csv %.gnuplot
	@echo $< to $@

# all: spectrum.o
# 	time ./$<
# 	gnuplot fourier.config

clean:
	rm -f *.o *.gcda *.gcno *.csv *.svg *.gnuplot
