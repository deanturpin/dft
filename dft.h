#ifndef DFT_H
#define DFT_H

#include <algorithm>
#include <complex>
#include <numeric>
#include <vector>

// DFT is a discrete Fourier transform implementation that uses no third-party
// libraries. Libraries often use optimisations that restrict dimensions of the
// sample array (power of two) but without these limitations we can explore the
// beauty of the algorithm and apply it to problems where we couldn't use a
// "fast" implementation. It was initially written to study the characteristic
// spectral response of my various instruments.
//
// https://en.wikipedia.org/wiki/Discrete_Fourier_transform
// https://jackschaedler.github.io/circles-sines-signals

namespace dft {

template <typename Iterator> auto calculate(Iterator begin, Iterator end) {

  // We will return a container of frequency bins
  std::vector<double> dft;

  // For each Fourier bin we need to iterate over each sample - O(n^2) - but
  // return only half as many bins as samples, the upper half is a mirror
  // image of the lower.
  const double bins = std::distance(begin, end);

  // The twiddle matrix is usually generated up front but as we're doing a
  // one-shot calculation it can be refactored into a single loop. Ordinarily
  // integers are used in for-loops but here a floating-point counter is used to
  // avoid a cast in the main calculation.
  for (double k = 0.0; k < bins / 2; ++k) {

    // Loop over every sample for each frequency bin and store the result.
    std::vector<std::complex<double>> fou;
    std::transform(begin, end, std::back_inserter(fou),
                   [ n = 0.0, &bins, &k ](const auto &sample) mutable {

                     // Calculate the response for this sample, note the sample
                     // index (n) is incremented in the calculation.
                     return exp(std::complex<double>{0.0, 2.0} *
                                3.14159265358979323846264338328 * k * n++ /
                                bins) *
                            double(sample);
                   });

    // Store the absolute sum of the responses scaled by the window size.
    dft.push_back(std::abs(std::accumulate(std::cbegin(fou), std::cend(fou),
                                           std::complex<double>{}) /
                           bins));
  }

  return dft;
}
}
#endif
