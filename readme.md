[![Build Status](https://travis-ci.org/deanturpin/dft.svg?branch=master)](https://travis-ci.org/deanturpin/dft)
[![codecov](https://codecov.io/gh/deanturpin/dft/branch/master/graph/badge.svg)](https://codecov.io/gh/deanturpin/dft)
Sat 16 Jun 10:04:34 BST 2018
```cpp
#ifndef DFT_H
#define DFT_H

#include <algorithm>
#include <complex>
#include <numeric>
#include <vector>

// DFT is a discrete Fourier transform implementation using no third-party
// libraries. Libraries generally use optimisations that restrict dimensions of
// the sample array (power of two) but without these limitations we can explore
// the beauty of the algorithm and apply it to problems where we couldn't use a
// "fast" implementation. It was initially written to study the spectral
// response of my digeridoo. See
// https://en.wikipedia.org/wiki/Discrete_Fourier_transform for the algorithm.

namespace dft {

template <typename Iterator> auto calculate(Iterator begin, Iterator end) {

  // We will return a container of frequency bins
  std::vector<double> dft;

  // For each Fourier bin we need to iterate over each sample - O(n^2) - but
  // return only half as many bins as samples, the upper half is a mirror
  // image of the lower
  const double bins = std::distance(begin, end);
  for (double k = 0.0; k < bins / 2; ++k) {

    // Loop over every sample for each result bin and store the result, note
    // sample index (n) is incremented in the calculation
    std::vector<std::complex<double>> responses;
    std::transform(begin, end, std::back_inserter(responses),
                   [ n = 0.0, &bins, &k ](const auto &sample) mutable {

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
```
# wav/bamboo_drone.wav
[![](wav/bamboo_drone.wav.svg)](wav/bamboo_drone.wav.svg)
Peaks at: 72, 143, 215, 286 and 357 Hz.

A cheap bamboo didge with a Sugru mouthpiece. Fundamental of 72 Hz, slightly
flat of D2, with a full compliment of harmonics across the whole frequency
range. Not a refined sound and quite difficult to play but very responsive.

```
73.42	D2
146.83	D3
220.00	A3
293.66	D4
369.99	F#4
```
Listen to the [audio](wav/bamboo_drone.wav).
# wav/didgeridoo_big_tony_drone.wav
[![](wav/didgeridoo_big_tony_drone.wav.svg)](wav/didgeridoo_big_tony_drone.wav.svg)
Peaks: 57, 172, 285, 398 Hz.

Fundamental of 57 Hz, slightly flat of concert Bb1. Next loudest peak is 398 Hz
(G4), which is a sixth interval in Bb Major. See [the
scale](https://en.wikipedia.org/wiki/B-flat_major) on Wikipedia.

This didgeridoo was liberated from the dump and is probably Eucalyptus:
woolybutt, bloodwood and stringybark have been discussed.

```
58.27	A#1
174.61	F3
293.66	D4
392.00	G4
```
Listen to the [audio](wav/didgeridoo_big_tony_drone.wav).
# wav/didgeridoo_big_tony_toot.wav
[![](wav/didgeridoo_big_tony_toot.wav.svg)](wav/didgeridoo_big_tony_toot.wav.svg)
The toot has a fundamental of 178 Hz (F3) which is a fifth above the drone.
There's also lots of activity in the higher frequencies at least up to 4 KHz.
Listen to the [audio](wav/didgeridoo_big_tony_toot.wav).
# wav/JF_fibreglass_slide.wav
[![](wav/JF_fibreglass_slide.wav.svg)](wav/JF_fibreglass_slide.wav.svg)
Peaks at: 81, 162, 243, 324 Hz.

A fundamental of 81 Hz, just flat of E2. Equal presence of first octave, fifth
(B3) and second octave. High frequency sparkle extends out as far as 1940 Hz.
Very pure harmonics.

```
82.41	E2
164.81	E3
246.94	B3
329.63	E4
```
Listen to the [audio](wav/JF_fibreglass_slide.wav).
# wav/KP_guest.wav
[![](wav/KP_guest.wav.svg)](wav/KP_guest.wav.svg)
Fundamental of 82 Hz (E2) with two octaves and a fifth (B). There's also a
hint of 403 Hz (a slightly sharp G4): a minor third. See [the
scale](https://en.wikipedia.org/wiki/E_minor) on Wikipedia.

```
82.41	E2
164.81	E3
246.94	B3
329.63	E4
392.00	G4
```
Listen to the [audio](wav/KP_guest.wav).
# wav/pianoBb1.wav
[![](wav/pianoBb1.wav.svg)](wav/pianoBb1.wav.svg)
Listen to the [audio](wav/pianoBb1.wav).
# wav/pianoBb2.wav
[![](wav/pianoBb2.wav.svg)](wav/pianoBb2.wav.svg)
Listen to the [audio](wav/pianoBb2.wav).
# wav/singing_bowl1.wav
[![](wav/singing_bowl1.wav.svg)](wav/singing_bowl1.wav.svg)
Fundamental of 468 Hz (close to A#4) and first octave of 936 Hz. The only bowl
with a pronounced octave. (Note that the second peak is off the right-hand side
of the second plot.)

```
466.16	A#4
932.33	A#5
```
Listen to the [audio](wav/singing_bowl1.wav).
# wav/singing_bowl2.wav
[![](wav/singing_bowl2.wav.svg)](wav/singing_bowl2.wav.svg)
Fundamental of 89 Hz, close to F2. Significant peaks at 259 Hz and 517 Hz
(fifths). Very complex response, I suspect this is a hand-made metal bowl. (I
recorded the bowls in the dark so I'm not sure which video was which.)

```
87.31	F2
261.63	C4
523.25	C5
```
Listen to the [audio](wav/singing_bowl2.wav).
# wav/singing_bowl3.wav
[![](wav/singing_bowl3.wav.svg)](wav/singing_bowl3.wav.svg)
Fundamental exactly 260 Hz (close to C4). Very pure, little harmonic noise.

```
261.63	C4
```
Listen to the [audio](wav/singing_bowl3.wav).
# wav/singing_bowl5.wav
[![](wav/singing_bowl5.wav.svg)](wav/singing_bowl5.wav.svg)
Extremely pure fundamental of 297 Hz. Halfway between D4 and D#4.

```
293.66	D4
311.13	D#4
```
Listen to the [audio](wav/singing_bowl5.wav).
# wav/synthesised_chord.wav
[![](wav/synthesised_chord.wav.svg)](wav/synthesised_chord.wav.svg)
Listen to the [audio](wav/synthesised_chord.wav).
# wav/synthesised_chord_whole_freqs.wav
[![](wav/synthesised_chord_whole_freqs.wav.svg)](wav/synthesised_chord_whole_freqs.wav.svg)
Listen to the [audio](wav/synthesised_chord_whole_freqs.wav).
