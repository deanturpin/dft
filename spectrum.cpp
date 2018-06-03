#include <algorithm>
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

    // Read header
    audio.read(reinterpret_cast<char *>(&header), sizeof header);

    // Read block of samples
    std::vector<short> samples(1000);
    if (audio.good())
      audio.read(reinterpret_cast<char *>(samples.data()),
                 samples.size() * sizeof(short));

    // Convert samples to decimal
    for (auto &s : samples)
      s = ~(s - 1);

    // Create and populate twiddle matrix
    std::vector<std::complex<double>> twiddle;
    using namespace std::complex_literals;
    const unsigned long bins = 1000;
    twiddle.reserve(bins * bins);
    for (unsigned long k = 0; k < bins / 2; ++k)
      for (unsigned long n = 0; n < bins; ++n)
        twiddle.push_back(
            exp(2i * M_PI * double(k) * double(n) / double(bins)));

    // const auto &fou = fourier(samples);
    std::vector<double> fou(bins / 2);
    generate(fou.begin(), fou.end(),
             [&twiddle, &samples, &bins, k = 0ul ]() mutable {
               std::complex<double> sum;
               for (unsigned long n = 0; n < bins; ++n)
                 sum += twiddle[(k * bins) + n] *
                        std::complex<double>(samples.at(n), 0);

               ++k;
               return abs(sum);
             });

    std::cout << fou.size() << " fourier bins\n";

    // Dump samples for plotting
    std::ofstream out1("samples.csv");
    if (out1.good())
      for (const auto &s : samples)
        out1 << static_cast<long>(s) << '\n';

    // Dump Fourier bins for plotting
    std::ofstream out2("fourier.csv");
    if (out2.good())
      for (const auto &s : fou)
        out2 << static_cast<long>(s) << '\n';
  }
}
