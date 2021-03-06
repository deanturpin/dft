#include "dft.h"
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char **argv) {

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
  } header;

  // Check if audio file passed as a param or use default
  const std::string audio_file{argc > 1 ? argv[1]
                                        : "wav/didgeridoo_big_tony_drone.wav"};

  // Check audio file is good
  if (std::ifstream audio{audio_file}; audio.good()) {

    // Read WAV header
    audio.read(reinterpret_cast<char *>(&header), sizeof header);

    // Read a block of samples to analyse
    std::vector<short> samples(8000);
    const long data_size =
        static_cast<long>(samples.size()) *
        static_cast<long>(sizeof(decltype(samples)::value_type));
    audio.read(reinterpret_cast<char *>(samples.data()), data_size);

    // Analyse samples
    const auto &dft = dft::calculate(samples.cbegin(), samples.cend());

    // Construct a new base filename for all output files
    const std::string basename{audio_file.substr(0, audio_file.find('.'))};

    // Dump the DFT results for plotting
    if (std::ofstream csv_file{basename + ".csv"}; csv_file.good())
      std::copy(dft.cbegin(), dft.cend(),
                std::ostream_iterator<double>(csv_file, "\n"));

    // Dump gnuplot config
    const std::string output_filetype{"png"};
    if (std::ofstream gnuplot_file{basename + ".gnuplot"}; gnuplot_file.good())
      gnuplot_file << "set terminal " << output_filetype << " size 2000,1500\n"
                   << "set title \"" << basename << "\"\n"
                   << "set output \"" << basename + "." + output_filetype
                   << "\"\n"
                   << "set format y \"\"\n"
                   << "set xtics 10\n"
                   << "set xtics rotate\n"
                   << "set xlabel \"Hz\"\n"
                   << "set grid xtics ytics\n"
                   << "set tics font \"Helvetica,3\"\n"
                   << "set logscale y\n"
                   << "plot \"" << basename + ".csv\" notitle\n";

    // Report index of highest peak and current input file name
    
    std::cout << std::distance(dft.cbegin(),
                                 (std::max_element(dft.cbegin(), dft.cend()))) +
                   1 << " Hz\t" + audio_file + '\n';

    // Call plotter
    return system(("/usr/bin/gnuplot " + basename + ".gnuplot").c_str());
  }

  return 0;
}
