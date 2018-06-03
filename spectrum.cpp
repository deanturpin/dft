// #include "fourier.h"
// #include "notes.h"
// #include "riff.h"
// #include <algorithm>
// #include <cmath>
// #include <iostream>
// #include <unistd.h>
#include <fstream>
#include <iostream>
#include <vector>

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
  std::cout << "read header\n";
  audio.read(reinterpret_cast<char *>(&h), sizeof h);

  // Read block of samples
  std::cout << "read samples\n";
  std::vector<short> samples(30);
  if (audio.good()) {
    std::cout << "audio is good\n";
    audio.read(reinterpret_cast<char *>(samples.data()),
               samples.size() * sizeof(short));
  } else
    std::cout << "audio bad\n";

  // Convert samples to decimal
  for (auto &s : samples)
    s = ~(s - 1);

  std::cout << "samples\n";
  for (const auto &s : samples)
    std::cout << static_cast<long>(s) << '\n';
  /*
    try {

      using namespace std;

      const auto header = read_wav_header();
      fourier_init();

      std::vector<short> samples;
      while (read_samples(samples) > 0) {

        // Do fourier analysis and create a copy of the results to display them
        auto fou = fourier(samples);
        // Find the max element so we know how much to scale the results
        // const double max_bin = *max_element(display.cbegin(),
    display.cend());
        const double max_bin = *max_element(fou.cbegin(), fou.cend());

        // Print the Fourier transform as an ASCII art histogram. Each bin is
        // converted into a bar.
        static vector<unsigned long> display(fou.size());
        for (unsigned long i = 0; i < fou.size(); ++i) {

          // Normalise the results and scale to make the graph fit nicely into
          // the terminal
          const auto full_bar = 130.0;
          const auto bar_length =
              static_cast<unsigned long>(floor(full_bar * fou.at(i) / max_bin));

          // Display the largest value and decay if necessary
          const auto decay = 5ul;
          display.at(i) = max(display.at(i), bar_length);
          display.at(i) = display.at(i) > decay ? display.at(i) - decay : 0;
        }

        const double bin_resolution = 1.0 * header.sample_rate / fourier_bins;
        for_each(display.crbegin(), display.crend(),
                 [&bin_resolution](const auto &i) {

                   const auto red = "\033[41m";
                   const auto white = "\033[0m";
                   const auto bin_freq = bin_resolution * (&i - display.data());
                   const auto note = notes.lower_bound(bin_freq);

                   cout << bin_freq << "\t" << string(i, '-') << red << "|"
                        << white << " " << note->second << endl;
                 });

        cout << "Bins " << fou.size() << endl;
        cout << "Resolution " << bin_resolution << endl;
        cout << "Sample rate " << header.sample_rate << " Hz" << endl;
      }
    } catch (const std::exception &e) {
      std::cout << "Caught " << e.what() << std::endl;
    }

    return 0;

    */
}
