CXX = g++-6
CCFLAGS = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -pg -g --coverage -O3

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

svgs = $(addprefix svg/, $(addsuffix .svg, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file))))))

# gnuplots = $(addsuffix .gnuplot, $(basename $(foreach file, $(wildcard wav/*.wav), $(notdir $(file)))))

all: $(svgs)

%.csv: wav/%.wav spectrum.o
	./spectrum.o > $@

gnuplot = $(addsuffix .gnuplot, $(basename $<))
%.gnuplot: %.csv
	# touch $@
	@echo set terminal svg size 1024,640 > $(gnuplot)
	@echo set output \"svg/$(basename $<).svg\" >> $(gnuplot)
	@echo set xtics 10 >> $(gnuplot)
	@echo set xtics rotate >> $(gnuplot)
	@echo set xlabel "Hz" >> $(gnuplot)
	@echo set grid xtics ytics >> $(gnuplot)
	@echo set tics font "Helvetica,8" >> $(gnuplot)
	@echo plot \"$<\" notitle with impulses >> $(gnuplot)
	cat $(gnuplot)

svg/%.svg: %.csv %.gnuplot
	@echo $^ to $@
	touch $@

# all: spectrum.o
# 	time ./$<
# 	gnuplot fourier.config

clean:
	rm -f *.o *.gcda *.gcno *.csv svg/*.svg *.gnuplot
