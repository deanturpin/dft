[![Build Status](https://travis-ci.org/deanturpin/spectrum_analyser_gnuplot.svg?branch=master)](https://travis-ci.org/deanturpin/spectrum_analyser_gnuplot)
[![codecov](https://codecov.io/gh/deanturpin/spectrum_analyser_gnuplot/branch/master/graph/badge.svg)](https://codecov.io/gh/deanturpin/spectrum_analyser_gnuplot)

A discrete Fourier transform implementation using no third-party libraries.
Initially written to study the spectral response of my digeridoo. See
[Wikipedia](https://en.wikipedia.org/wiki/Discrete_Fourier_transform) for the
algorithm.

Samples recorded on my Ubuntu laptop with ```arecord```.
```bash
arecord -q -f S16_LE -c1 -r 8000 > recording.wav
```

For each sample two plots are rendered: all Fourier bins and a second zoomed
into the first section.

See the [pitch table](pitch.md) for concert pitch frequencies.

---

