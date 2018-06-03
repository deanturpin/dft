#include <complex>
#include <fstream>
#include <iostream>
#include <vector>

int main() {

  // Structure of a WAV header, we're not actually reading any of the fields but
  // comments left for reference
  struct wav_header {
    using word = unsigned long;
    word : 32; // riff_id
    word : 32; // riff_size
    word : 32; // wave_tag
    word : 32; // format_id
    word : 32; // format_size
    word : 16; // format_tag
    word : 16; // channels
    word : 32; // sample_rate
    word : 32; // bytes_per_second
    word : 16; // block_align
    word : 16; // bit_depth
    word : 32; // data_id
    word : 32; // data_size
  } header;

  // Check audio file is good
  std::ifstream audio("recording.wav");
  if (audio.good()) {

    // Initialise twiddle container
    const unsigned long bins = 1000;
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

    std::vector<double> fourier(bins / 4);
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
    }

    // Dump samples for plotting
    std::ofstream out1("samples.csv");
    if (out1.good())
      for (const auto &samp : samples)
        out1 << static_cast<long>(samp) << '\n';

    // Dump Fourier bins for plotting
    std::ofstream out2("fourier.csv");
    if (out2.good())
      for (const auto &bin : fourier)
        out2 << static_cast<long>(bin) << '\n';
  }
}