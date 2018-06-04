#include <complex>
#include <fstream>
#include <iostream>
#include <vector>

// Structure of a WAV header, we're not actually reading any of the fields but
// comments left for reference
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

  friend std::ostream &operator<<(std::ostream &os, const wav_header &header) {
    return os << std::hex << header.riff_id << "\triff_id\n"
              << header.riff_size << "\triff_size\n"
              << header.wave_tag << "\twave_tag\n"
              << std::dec << header.format_id << "\tformat_id\n"
              << header.format_size << "\t\tformat_size\n"
              << header.format_tag << "\t\tformat_tag\n"
              << header.channels << "\t\tchannels\n"
              << header.sample_rate << "\t\tHz sample_rate\n"
              << header.bytes_per_second << "\t\tbytes_per_second\n"
              << header.block_align << "\t\tblock_align\n"
              << header.bit_depth << "\t\tbit_depth\n"
              << std::hex << header.data_id << "\tdata_id\n"
              << header.data_size << "\tdata_size\n"
              << std::dec;
  };
};

int main() {

  wav_header header;

  // Bins in our Fourier transform
  const unsigned long bins = 1000;

  // Check audio file is good
  std::ifstream audio("recording.wav");
  if (audio.good()) {

    // Initialise twiddle container
    std::vector<std::complex<double>> twiddle;
    twiddle.reserve(bins * bins);

    // Create and populate twiddle matrix
    using namespace std::complex_literals;
    for (unsigned long k = 0; k < bins; ++k)
      for (unsigned long n = 0; n < bins; ++n)
        twiddle.push_back(exp(2i * M_PI * static_cast<double>(k) *
                              static_cast<double>(n) /
                              static_cast<double>(bins)));

    // Read header
    audio.read(reinterpret_cast<char *>(&header), sizeof header);

    std::vector<double> fourier(bins / 8);
    std::vector<short> samples(bins);

    // Read complete blocks of samples until end of file
    while (audio.read(reinterpret_cast<char *>(samples.data()),
                      samples.size() * sizeof(short))) {

      // Convert samples to decimal (from 2's comp)
      for (auto &samp : samples)
        samp = ~(samp - 1);

      // Calculate Fourier transform for batch of samples
      unsigned long k = 0;
      for (auto &f : fourier) {

        std::complex<double> sum;
        for (unsigned long n = 0; n < bins; ++n)
          sum +=
              twiddle[(k * bins) + n] * std::complex<double>(samples.at(n), 0);

        ++k;
        f += abs(sum);
      }

      // Dump samples for plotting (appended to previous iteration results)
      std::ofstream out1("samples.csv", std::fstream::app);
      if (out1.good())
        for (const auto &samp : samples)
          out1 << samp << '\n';
    }

    // Dump Fourier bins for plotting
    std::ofstream out2("fourier.csv");
    if (out2.good())
      for (const auto &bin : fourier)
        out2 << bin << '\n';

    for (const auto &bin : fourier)
      std::cout << bin << '\n';
  }

  const double fourier_bin_resolution = 1.0 * header.sample_rate / bins;
  std::cout << std::fixed << bins << " Fourier bins\n"
            << header.sample_rate << " sample rate\n"
            << fourier_bin_resolution << " Hz bin resolution\n";
  std::cout << "WAV header\n" << header << '\n';
}
