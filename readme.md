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

Fri  8 Jun 20:00:44 BST 2018

# didgeridoo_big_tony_drone.wav

Listen to the [audio](wav/didgeridoo_big_tony_drone.wav).
[![](didgeridoo_big_tony_drone_full.svg)](didgeridoo_big_tony_drone_full.svg)

# didgeridoo_big_tony_drone.wav

Listen to the [audio](wav/didgeridoo_big_tony_drone.wav).
[![](didgeridoo_big_tony_drone_zoom.svg)](didgeridoo_big_tony_drone_zoom.svg)

# didgeridoo_big_tony_toot.wav

Listen to the [audio](wav/didgeridoo_big_tony_toot.wav).
[![](didgeridoo_big_tony_toot_full.svg)](didgeridoo_big_tony_toot_full.svg)

# didgeridoo_big_tony_toot.wav

Listen to the [audio](wav/didgeridoo_big_tony_toot.wav).
[![](didgeridoo_big_tony_toot_zoom.svg)](didgeridoo_big_tony_toot_zoom.svg)

# guitar_open_a.wav

Listen to the [audio](wav/guitar_open_a.wav).
[![](guitar_open_a_full.svg)](guitar_open_a_full.svg)

# guitar_open_a.wav

Listen to the [audio](wav/guitar_open_a.wav).
[![](guitar_open_a_zoom.svg)](guitar_open_a_zoom.svg)

# guitar_open_e.wav

Listen to the [audio](wav/guitar_open_e.wav).
[![](guitar_open_e_full.svg)](guitar_open_e_full.svg)

# guitar_open_e.wav

Listen to the [audio](wav/guitar_open_e.wav).
[![](guitar_open_e_zoom.svg)](guitar_open_e_zoom.svg)

# JF_fibreglass_slide.wav
Peaks at: 81, 162, 243, 324 Hz.

A strong fundamental at 81 Hz, just flat of E2. Textbook first octave followed
by a near perfect 5th (B3) and a strong second octave. High frequency sparkle
extends out as far as 1940 Hz.

Listen to the [audio](wav/JF_fibreglass_slide.wav).
[![](JF_fibreglass_slide_full.svg)](JF_fibreglass_slide_full.svg)

# JF_fibreglass_slide.wav
Peaks at: 81, 162, 243, 324 Hz.

A strong fundamental at 81 Hz, just flat of E2. Textbook first octave followed
by a near perfect 5th (B3) and a strong second octave. High frequency sparkle
extends out as far as 1940 Hz.

Listen to the [audio](wav/JF_fibreglass_slide.wav).
[![](JF_fibreglass_slide_zoom.svg)](JF_fibreglass_slide_zoom.svg)

# KP_guest.wav
Starting on the left: it's just shy of concert pitch E, with two E octaves and a
B 5th. There's also a faint whiff of G on the right.

Listen to the [audio](wav/KP_guest.wav).
[![](KP_guest_full.svg)](KP_guest_full.svg)

# KP_guest.wav
Starting on the left: it's just shy of concert pitch E, with two E octaves and a
B 5th. There's also a faint whiff of G on the right.

Listen to the [audio](wav/KP_guest.wav).
[![](KP_guest_zoom.svg)](KP_guest_zoom.svg)

# major7_fractional_freqs.wav

Listen to the [audio](wav/major7_fractional_freqs.wav).
[![](major7_fractional_freqs_full.svg)](major7_fractional_freqs_full.svg)

# major7_fractional_freqs.wav

Listen to the [audio](wav/major7_fractional_freqs.wav).
[![](major7_fractional_freqs_zoom.svg)](major7_fractional_freqs_zoom.svg)

# major7_precise_freqs.wav

Listen to the [audio](wav/major7_precise_freqs.wav).
[![](major7_precise_freqs_full.svg)](major7_precise_freqs_full.svg)

# major7_precise_freqs.wav

Listen to the [audio](wav/major7_precise_freqs.wav).
[![](major7_precise_freqs_zoom.svg)](major7_precise_freqs_zoom.svg)

# piano2.wav

Listen to the [audio](wav/piano2.wav).
[![](piano2_full.svg)](piano2_full.svg)

# piano2.wav

Listen to the [audio](wav/piano2.wav).
[![](piano2_zoom.svg)](piano2_zoom.svg)

# piano.wav

Listen to the [audio](wav/piano.wav).
[![](piano_full.svg)](piano_full.svg)

# piano.wav

Listen to the [audio](wav/piano.wav).
[![](piano_zoom.svg)](piano_zoom.svg)

