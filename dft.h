#ifndef DFT_H
#define DFT_H

#include <algorithm>
#include <complex>
#include <numeric>
#include <vector>

// Discrete Fourier transform calculation - third-party libraries generally use
// optimisations that restrict dimensions of the sample array (power of two) but
// without these limitations we can explore the beauty of the algorithm and
// apply it to problems where we couldn't use a "fast" implementation.

namespace dft {

template <typename Iterator> auto calculate(Iterator begin, Iterator end) {

  // We will return a container of frequency bins
  std::vector<double> dft;

  // For each Fourier bin we need to iterate over each sample - O(n^2) - but
  // return
  // only half as many bins as samples, the upper half is a mirror image of the
  // lower
  const double bins = std::distance(begin, end);
  for (double k = 0.0; k < bins / 2; ++k) {

    // Loop over every sample for each result bin and store the result
    std::vector<std::complex<double>> responses;
    std::transform(begin, end, std::back_inserter(responses),
                   [&bins, &k, n = 0.0 ](const auto &sample) mutable {

                     // Calculate the response for this sample
                     return exp(std::complex<double>{0.0, 2.0} *
                                3.14159265358979323846264338328 * k * n++ /
                                bins) *
                            double(sample);
                   });

    // Store the absolute sum of the responses scaled by the window size
    dft.push_back(
        std::abs(std::accumulate(std::cbegin(responses), std::cend(responses),
                                 std::complex<double>{}) /
                 bins));
  }

  return dft;
}
}
#endif