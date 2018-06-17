#ifndef DFT_H
#define DFT_H

#include <algorithm>
#include <complex>
#include <numeric>
#include <vector>

// DFT is a header-only discrete Fourier transform implementation written in
// C++14. Libraries often use optimisations that restrict dimensions of the
// sample array (power of two) but without these limitations we can explore the
// the algorithm and apply where we couldn't use a "fast" implementation. It was
// originally written to study the characteristic spectral response of my
// various musical instruments but can be applied in other domains. The
// calculate() routine takes a pair of STL container iterators and returns the
// Fourier transform as a vector of bins. We could consider parallelising the
// matrix calculation but I've elected to keep the library simple
// (single-threaded) and delegated the multi-core utilisation to the makefile:
// the build process generates multiple images in parallel.
//
// https://en.wikipedia.org/wiki/Discrete_Fourier_transform
// https://jackschaedler.github.io/circles-sines-signals

namespace dft {

template <typename Iterator> auto calculate(Iterator begin, Iterator end) {

  // This routine will return a container of frequency bins.
  std::vector<double> dft;

  // For each Fourier bin we need to iterate over each sample - O(n^2) - but
  // return only half as many bins as samples, the upper half is a mirror
  // image of the lower.
  const double bins = std::distance(begin, end);

  // The twiddle matrix is usually generated up front but as we're performing a
  // one-shot calculation it can be refactored into a single loop. Normally you
  // would expect integer array indices but here a floating-point counter is
  // used to avoid a cast in the subsequent calculation.
  for (double k = 0.0; k < bins / 2; ++k) {

    // Iterate over all samples for the current bin index (k), calculate the
    // response and store the result. Note the sample index (n) is incremented
    // during the calculation.
    std::vector<std::complex<double>> fou;
    std::transform(begin, end, std::back_inserter(fou),
                   [ n = 0.0, &bins, &k ](const auto &sample) mutable {
                     return exp(std::complex<double>{0.0, 2.0} *
                                3.14159265358979323846264338328 * k * n++ /
                                bins) *
                            double(sample);
                   });

    // Store the absolute sum of all responses for this frequency bin and scale
    // it by the window size (number of samples).
    dft.push_back(std::abs(std::accumulate(std::cbegin(fou), std::cend(fou),
                                           std::complex<double>{}) /
                           bins));
  }

  return dft;
}
}
#endif
