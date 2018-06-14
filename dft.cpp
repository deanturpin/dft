#include <complex>
#include <fstream>
#include <iostream>
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

// Expect half as many bins returned as samples
template <typename Iterator>
std::vector<double> calculate_dft(Iterator begin, Iterator end) {
  std::vector<double> dft;
  const unsigned long bins = std::distance(begin, end) / 2;
  std::cerr << bins << " Fourier bins will be returned\n";

  for (auto k = 0ul; k < bins; ++k) {

    // For each Fourier bin loop over each sample - O(n^2)
    const auto bin_total =
        std::accumulate(begin, end, std::complex<double>{0.0, 0.0}, [
          &bins, &k, n = 0.0
        ](std::complex<double> sum, const auto &sample) mutable {

          using namespace std::complex_literals;
          return sum += exp(2i * M_PI * double{k} * n++ / double(bins)) *
                        double(sample);
        });

    dft.push_back(std::abs(bin_total));
  }

  return dft;
}

int main(int count, char **argv) {

  wav_header header;

  // Check if audio file passed as a param or use default
  const std::string audio_file =
      (count > 1 ? argv[1] : "wav/didgeridoo_big_tony_drone.wav");

  // const unsigned long default_zoom = 2;
  // const unsigned long zoom = (count > 2 ? atoi(argv[2]) : default_zoom);

  // Check audio file is good
  std::ifstream audio(audio_file);
  if (audio.good()) {

    // Read header and calculate bin resolution
    audio.read(reinterpret_cast<char *>(&header), sizeof header);

    // Bins in our complete Fourier transform
    const unsigned long bins = 8000;
    // const unsigned long result_bins = bins / (zoom < 1 ? default_zoom :
    // zoom);

    // Create large enough container for the numebr of bins we're interested in
    std::vector<double> fourier;
    // fourier.reserve(result_bins);

    // Read complete blocks of samples until end of file
    std::vector<short> raw(bins);
    if (audio.read(reinterpret_cast<char *>(raw.data()),
                   raw.size() * sizeof(short))) {

      // Convert samples to decimal (from 2's comp)
      for (auto &samp : raw)
        samp = ~(samp - 1);

      const auto &dft = calculate_dft(raw.cbegin(), raw.cend());

      // Dump Fourier bins for plotting
      std::cerr << raw.size() << " samples provided\n";
      std::cerr << dft.size() << " bins returned\n";
      for (const auto &bin : dft)
        puts(std::to_string(bin).c_str());

      /*
            // Convert raw samples to complex numbers
            std::vector<std::complex<double>> samples;
            samples.reserve(bins);
            for (const auto &s : raw)
              samples.push_back(std::complex<double>(s, 0));

            // Calculate Fourier transform for batch of samples
            using namespace std::complex_literals;

            for (double k = 0.0; k < result_bins; ++k) {

              const auto fsum = std::accumulate(
                  std::cbegin(samples), std::cend(samples),
                  std::complex<double>{0.0, 0.0},
                  [&bins, &k, n = 0.0 ](std::complex<double> sum,
                                        const auto &sample) mutable {

                    const auto _sum =
                        sum +
                        exp(2i * M_PI * k * n++ / static_cast<double>(bins)) *
         sample;

                    return _sum;
                  });

              fourier.push_back(std::abs(fsum));
            }
          }

          // Dump Fourier bins for plotting
          for (const auto &bin : fourier)
            puts(std::to_string(bin).c_str());
        */
    }
  }
}