#include <algorithm>
#include <array>
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

template <typename Iterator>
std::vector<double> calculate_dft(Iterator begin, Iterator end,
                                  const unsigned long zoom = 2ul) {
  std::vector<double> dft;

  // We're going to return half as many bins as samples, the upper half is just
  // a mirror image of lower
  const unsigned long bins = std::distance(begin, end) / (zoom > 1 ? zoom : 1);

  // For each Fourier bin we need to iterate over each sample, which is O(n^2)
  for (auto k = 0ul; k < bins; ++k) {

    // Loop over every sample for each result bin and store the result
    std::vector<std::complex<double>> responses;
    std::for_each(begin, end, [&responses, &bins, &k, &begin,
                               n = 0.0 ](const auto &sample) mutable {

      using namespace std::complex_literals;
      responses.push_back(exp(2i * M_PI * double(k) * n++ / double(bins)) *
                          double(sample));
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

  // Check audio file is good
  std::ifstream audio(audio_file);
  if (audio.good()) {

    // Read header and calculate bin resolution
    audio.read(reinterpret_cast<char *>(&header), sizeof header);

    // Bins in the complete Fourier transform
    const unsigned long bins = 8000;

    // Read a single block of samples to analyse
    std::array<short, bins> raw;
    audio.read(reinterpret_cast<char *>(raw.data()),
               raw.size() * sizeof(short));

    // Convert samples to decimal (from 2's comp)
    for (auto &samp : raw)
      samp = ~(samp - 1);

    // Analyse samples
    const auto &dft = calculate_dft(std::cbegin(raw), std::cend(raw), zoom);

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
