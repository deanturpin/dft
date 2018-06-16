#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "dft.h"

int main(int argc, char **argv) {

  // Check if audio file passed as a param or use default
  const std::string file = (argc > 1 ? argv[1] : "btc.csv");

  // Read in all the prices
  std::ifstream in(file);
  std::vector<double> prices{std::istream_iterator<double>(in),
                             std::istream_iterator<double>()};

  std::cout << prices.size() << " prices\n";

  const auto &dft = dft::calculate(std::cbegin(prices), std::cend(prices));
  std::cout << dft.size() << " bins\n";

  // Dump DFT results for plotting
  std::ofstream csv_file(file + ".csv");
  for (const auto &bin : dft)
    csv_file << bin << '\n';

  // Dump gnuplot config
  std::ofstream gnuplot_file(file + ".gnuplot");
  gnuplot_file << "set terminal svg size 1500,900\n"
               << "set title \"" << file << "\"\n"
               << "set output \"" << file + ".svg"
               << "\"\n"
               << "set format y \"\"\n"
               << "set xtics 10\n"
               << "set xtics rotate\n"
               << "set xlabel \"Hz\"\n"
               << "set grid xtics ytics\n"
               << "set tics font \"Helvetica,3\"\n"
               << "stats \"" << file + ".csv\"\n"
               << "set logscale y\n"
               << "plot \"" << file + ".csv\" notitle with impulses\n";

  // Close (and flush) files
  csv_file.close();
  gnuplot_file.close();

  // Call plotter
  const std::string command{"/usr/bin/gnuplot " + file + ".gnuplot"};
  return system(command.c_str());
}