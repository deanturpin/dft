#include <algorithm>
#include <complex>
#include <fstream>
#include <iostream>
#include <vector>

int main() {

  struct wav_header {

    unsigned long riff_id;
    unsigned long riff_size;
    unsigned long wave_tag;
    unsigned long format_id;
    unsigned long format_size;
    unsigned long format_tag : 16;
    unsigned long channels : 16;
    unsigned long sample_rate;
    unsigned long bytes_per_second;
    unsigned long block_align : 16;
    unsigned long bit_depth : 16;
    unsigned long data_id;
    unsigned long data_size;
  } h;

  // Check audio file is good
  std::ifstream audio("recording.wav");
  if (!audio.good()) {
    std::cout << "failed to read audio\n";
    return 2;
  }

  // Read header
  audio.read(reinterpret_cast<char *>(&h), sizeof h);

  // Read block of samples
  std::vector<short> samples(1000);
  if (audio.good())
    audio.read(reinterpret_cast<char *>(samples.data()),
               samples.size() * sizeof(short));

  // Convert samples to decimal
  for (auto &s : samples)
    s = ~(s - 1);

  // Create and populate twiddle matrix - Euler's magic
  std::vector<std::complex<double>> twiddle;
  using namespace std::complex_literals;
  const unsigned long bins = 1000;
  twiddle.reserve(bins * bins);
  for (unsigned long k = 0; k < bins / 2; ++k)
    for (unsigned long n = 0; n < bins; ++n)
      twiddle.push_back(exp(2i * M_PI * double(k) * double(n) / double(bins)));

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
