#include <algorithm>
#include <complex>
#include <fstream>
#include <iostream>
#include <vector>

const unsigned long fourier_bins = 1000;
std::vector<std::complex<double>> twiddle;

void fourier_init() {

  using namespace std;

  const auto bins = fourier_bins;
  twiddle.reserve(bins * bins);

  // Populate twiddle matrix - Euler's magic
  for (unsigned int k = 0; k < bins / 2; ++k)
    for (unsigned int n = 0; n < bins; ++n)
      twiddle.push_back(exp(2i * M_PI * double(k) * double(n) / double(bins)));
}

std::vector<double> fourier(const std::vector<short> &samples) {

  using namespace std;

  const auto bins = fourier_bins;

  // The Fourier transform is the dot product of the twiddle matrix and the
  // original samples. Only run over the first half of the matrix as the other
  // half is a mirror image.
  vector<double> fou(bins / 2);
  generate(fou.begin(), fou.end(), [&samples, &bins, k = 0ul ]() mutable {

    complex<double> sum;
    for (unsigned int n = 0; n < bins; ++n)
      sum += twiddle[(k * bins) + n] * complex<double>(samples.at(n), 0);

    ++k;
    return abs(sum);
  });

  return fou;
}

int main() {

  struct wav_header {

    unsigned int riff_id;
    unsigned int riff_size;
    unsigned int wave_tag;
    unsigned int format_id;
    unsigned int format_size;
    unsigned int format_tag : 16;
    unsigned int channels : 16;
    unsigned int sample_rate;
    unsigned int bytes_per_second;
    unsigned int block_align : 16;
    unsigned int bit_depth : 16;
    unsigned int data_id;
    unsigned int data_size;
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

  fourier_init();
  const auto fou = fourier(samples);
  std::cout << fou.size() << " fourier bins\n";

  // Dump samples to a file for plotting
  std::ofstream out1("samples.csv");
  if (out1.good())
    for (const auto &s : samples)
      out1 << static_cast<long>(s) << '\n';

  std::ofstream out2("fourier.csv");
  if (out2.good())
    for (const auto &s : fou)
      out2 << static_cast<long>(s) << '\n';
}
