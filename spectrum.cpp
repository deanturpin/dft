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

int main(int count, char *argv[]) {

  wav_header header;

  // Check if audio file passed as a param or use default
  const std::string audio_file =
      (count == 2 ? argv[1] : "wav/didgeridoo_big_tony.wav");

  // Check audio file is good
  std::ifstream audio(audio_file);
  if (audio.good()) {

    // Bins in our Fourier transform
    const unsigned long bins = 1000;

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

    // Read header and calculate bin resolution
    audio.read(reinterpret_cast<char *>(&header), sizeof header);
    const double fourier_bin_resolution = 1.0 * header.sample_rate / bins;

    // We're only interested in the lower end of the Fourier results
    std::vector<double> fourier(bins / 10);

    // Read complete blocks of samples until end of file
    std::vector<short> samples(bins);
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
      std::ofstream samples_file("samples.csv", std::fstream::app);
      if (samples_file.good())
        for (const auto &samp : samples)
          samples_file << samp << '\n';
    }

    // Dump Fourier bins for plotting
    // std::ofstream fourier_file("fourier.csv");
    // if (fourier_file.good())
    //   for (const auto &bin : fourier)
    // fourier_file << bin << '\n';
    for (const auto &bin : fourier)
      std::cout << bin << '\n';

    // std::cout << std::fixed << bins << " Fourier bins\n"
    //           << header.sample_rate << " Hz sample rate\n"
    //           << fourier_bin_resolution << " Hz bin resolution\n";
    // std::cout << "WAV header\n" << header << '\n';
  }
}
