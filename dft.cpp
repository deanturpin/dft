#include <algorithm>
#include <complex>
#include <fstream>
// #include <iostream>
#include <numeric>
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

// Discrete Fourier transform calculation - third-party libraries generally use
// optimisations that restrict dimensions of the sample array (power of two) but
// without these limitations we can explore the beauty of the algorithm and
// apply it to problems where we couldn't use a "fast" implementation.
template <typename Iterator>
auto calculate_dft(Iterator begin, Iterator end,
                   const unsigned long zoom = 2ul) {

  // Return a container of bins
  std::vector<double> dft;

  // By default return only half as many bins as samples, the upper half is
  // a mirror image of the lower
  const double bins = std::distance(begin, end);
  const double results = bins / (zoom > 1 ? zoom : 1);

  // For each Fourier bin we need to iterate over each sample - O(n^2)
  for (double k = 0.0; k < results; ++k) {

    // Loop over every sample for each result bin and store the result
    std::vector<std::complex<double>> responses;
    std::for_each(begin, end, [&responses, &bins, &k, &begin,
                               n = 0.0 ](const auto &sample) mutable {

      // Calculate the response for this sample
      responses.push_back(exp(std::complex<double>{0.0, 2.0} *
                              3.14159265358979323846264338328 * k * n / bins) *
                          std::complex<double>{double(sample), 0.0});

      ++n;
    });

    // Store the absolute sum of the responses
    dft.push_back(std::abs(std::accumulate(
        std::cbegin(responses), std::cend(responses), std::complex<double>{})));
  }

  return dft;
}

int main(int count, char **argv) {

  wav_header header;

  // Check if audio file passed as a param or use default
  const std::string audio_file =
      (count > 1 ? argv[1] : "wav/didgeridoo_big_tony_drone.wav");

  const unsigned long default_zoom = 2;
  const unsigned long zoom = (count > 2 ? atoi(argv[2]) : default_zoom);

  // std::cerr << audio_file << '\n';
  // Check audio file is good
  std::ifstream audio(audio_file);
  if (audio.good()) {

    // Read header and calculate bin resolution
    audio.read(reinterpret_cast<char *>(&header), sizeof header);

    // Read a single block of samples to analyse
    std::vector<short> raw(8000);
    audio.read(reinterpret_cast<char *>(raw.data()),
               raw.size() * sizeof(short));

    // Convert samples to decimal (from 2's comp)
    for (auto &samp : raw)
      samp = ~(samp - 1);

    // Analyse samples
    const auto &dft = calculate_dft(std::cbegin(raw), std::cend(raw), zoom);

    // Construct a new filename for all output files
    const std::string basename{audio_file + "_zoom" + std::to_string(zoom)};

    // Dump Fourier bins for plotting
    std::ofstream csv_file(basename + ".csv");
    for (const auto &bin : dft)
      csv_file << bin << '\n';

    // Dump gnuplot config
    std::ofstream gnuplot_file(basename + ".gnuplot");
    gnuplot_file << "set terminal svg size 1500,900\n";
    gnuplot_file << "set title \"" << basename << "\"\n";
    gnuplot_file << "set output \"" << basename + ".svg"
                 << "\"\n";
    gnuplot_file << "set format y \"\"\n";
    gnuplot_file << "set xtics 10\n";
    gnuplot_file << "set xtics rotate\n";
    gnuplot_file << "set xlabel \"Hz\"\n";
    gnuplot_file << "set grid xtics ytics\n";
    gnuplot_file << "set tics font \"Helvetica,3\"\n";
    gnuplot_file << "stats \"" << basename + ".csv\"\n";
    gnuplot_file << "set logscale y\n";
    gnuplot_file << "plot \"" << basename + ".csv\" notitle with impulses\n";

    // Close files so they're flushed
    csv_file.close();
    gnuplot_file.close();

    const std::string command{"/usr/bin/gnuplot " + basename + ".gnuplot"};
    return system(command.c_str());
  }

  return 0;
}
