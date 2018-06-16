#include "dft.h"
#include <fstream>
#include <string>
#include <vector>

// Structure of a WAV header
struct wav_header {
  using word = unsigned int;
  word riff_id;
  word riff_size;
  word wave_tag;
  word format_id;
  word format_size;
  word format_tag : 16;
  word channels : 16;
  word sample_rate;
  word bytes_per_second;
  word block_align : 16;
  word bit_depth : 16;
  word data_id;
  word data_size;
};

int main(int argc, char **argv) {

  wav_header header;

  // Check if audio file passed as a param or use default
  const std::string audio_file =
      (argc > 1 ? argv[1] : "wav/didgeridoo_big_tony_drone.wav");

  // Check audio file is good
  std::puts(audio_file.c_str());
  std::ifstream audio(audio_file);
  if (audio.good()) {

    // Read WAV header
    audio.read(reinterpret_cast<char *>(&header), sizeof header);

    // Read a block of samples to analyse
    std::vector<short> samples(8000);
    audio.read(reinterpret_cast<char *>(samples.data()),
               samples.size() * sizeof(short));

    // Analyse samples
    const auto &dft = dft::calculate(std::cbegin(samples), std::cend(samples));

    // Construct a new base filename for all output files
    const std::string basename{audio_file};

    // Dump DFT results for plotting
    std::ofstream csv_file(basename + ".csv");
    for (const auto &bin : dft)
      csv_file << bin << '\n';

    // Dump gnuplot config
    std::ofstream gnuplot_file(basename + ".gnuplot");
    gnuplot_file << "set terminal svg size 1500,900\n"
                 << "set title \"" << basename << "\"\n"
                 << "set output \"" << basename + ".svg"
                 << "\"\n"
                 << "set format y \"\"\n"
                 << "set xtics 10\n"
                 << "set xtics rotate\n"
                 << "set xlabel \"Hz\"\n"
                 << "set grid xtics ytics\n"
                 << "set tics font \"Helvetica,3\"\n"
                 << "stats \"" << basename + ".csv\"\n"
                 << "set logscale y\n"
                 << "plot \"" << basename + ".csv\" notitle with impulses\n";

    // Close (and flush) files
    csv_file.close();
    gnuplot_file.close();

    // Call plotter
    const std::string command{"/usr/bin/gnuplot " + basename + ".gnuplot"};
    return system(command.c_str());
  }

  return 0;
}
