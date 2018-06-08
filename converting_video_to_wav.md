MP4 to WAV
```
ffmpeg -i in.mp4 out.wav
```

Downsample WAV
```
sox -t wav in.wav -r 8000 -c 1 out.wav
```

Trim WAV
```
sox in.wav out.wav trim 0 5

```

# Downsample and trim
```
sox -t in.wav -r 8000 -c 1 out.wav trim 0 10

```
