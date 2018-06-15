# Improvements
```cpp
      samples.reserve(bins);
```
```cpp
```
Using complex literals is slower than a complex constructor
```cpp
2i
std::complex<double>(0.0, 2.0) 
```
```cpp
```

Reserve is slower than just pushing back
```cpp
 dft.reserve(results);
```

Arrays are slower than vectors
```cpp
```
Calculating this constant is quicker inline than a const.
```cpp
2i * M_PI
```

push_back quicker
```cpp
        samples.emplace_back(std::complex<double>(s, 0));
        samples.push_back(std::complex<double>(s, 0));
```
