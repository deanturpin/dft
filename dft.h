#ifndef DFT_H
#define DFT_H

#include <algorithm>
#include <complex>
#include <numeric>
#include <vector>

// DFT is a header-only discrete Fourier transform implementation written in
// C++14. Libraries often use optimisations that restrict dimensions of the
// sample array (power of two) but without these limitations we can explore the
// algorithm and apply it where we couldn't use a "fast" implementation. It was
// originally written to study the characteristic spectral response of my
// various musical instruments but it can be applied in other domains. The
// calculate() routine takes a pair of STL container iterators and returns the
// Fourier transform as a vector of bins. We could consider parallelising the
// matrix calculation but I've elected to keep the library simple
// (single-threaded) and delegated the multi-core utilisation to the makefile:
// the build process generates multiple images in parallel.
//
// https://en.wikipedia.org/wiki/Discrete_Fourier_transform
// https://jackschaedler.github.io/circles-sines-signals

namespace dft {

template <class T> constexpr T pi = T(3.1415926535897932385);

template <typename Iterator>
auto calculate(const Iterator begin, const Iterator end) {

  // For each Fourier bin we need to iterate over each sample - O(n^2) - but we
  // will return only half as many bins as samples. The upper half is a mirror
  // image of the lower.
  const double total_samples = std::distance(begin, end);

  // This routine will return the results as a container of frequency bins.
  std::vector<double> dft;
  dft.reserve(total_samples / 2);

  // The "twiddle matrix" is usually generated up front but as we're performing
  // a one-shot calculation it can be refactored into a single loop. Normally
  // you would expect to see integer array indices but here a floating-point
  // counter is used to avoid a cast in the subsequent calculation.
  for (double k = 0.0; k < total_samples / 2; ++k) {

    // Definition of our Fourier function. Note the sample index (n) is
    // incremented during the calculation.
    const auto sinusoidal = [&total_samples, n = 0.0,
                             &k](const auto &sample) mutable {
      using namespace std::complex_literals;
      return exp(2i * pi<double> * k * n++ / total_samples) * double(sample);
    };

    // Iterate over all samples passed to this routine, calculate the response
    // and store the result. See the Wikipedia link above for the details of
    // the algorithm.
    std::vector<std::complex<double>> fou;
    std::transform(begin, end, std::back_inserter(fou), sinusoidal);

    // Store the absolute sum of all responses for this frequency bin and scale
    // it by the window size (number of samples).
    dft.emplace_back(std::abs(std::accumulate(std::cbegin(fou), std::cend(fou),
                                              std::complex<double>{}) /
                              total_samples));
  }

  return dft;
}
} // namespace dft
#endif
