#include "fourier.hpp"
#include <cmath>
#include <matplot/matplot.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace signal {

std::vector<std::complex<double>> dft(const std::vector<double>& signal) {
    size_t N = signal.size();
    std::vector<std::complex<double>> X(N);

    for (size_t k = 0; k < N; ++k) {
        std::complex<double> sum(0, 0);
        for (size_t n = 0; n < N; ++n) {
            double angle = -2 * M_PI * k * n / N;
            sum += signal[n] * std::polar(1.0, angle);
        }
        X[k] = sum;
    }
    return X;
}

std::vector<double> idft(const std::vector<std::complex<double>>& spectrum) {
    size_t N = spectrum.size();
    std::vector<double> signal(N);

    for (size_t n = 0; n < N; ++n) {
        std::complex<double> sum(0, 0);
        for (size_t k = 0; k < N; ++k) {
            double angle = 2 * M_PI * k * n / N;
            sum += spectrum[k] * std::polar(1.0, angle);
        }
        signal[n] = sum.real() / static_cast<double>(N);
    }
    return signal;
}

void plot_dft(const std::vector<double>& signal) {
    auto X = dft(signal);
    std::vector<double> magnitude;
    magnitude.reserve(X.size());
    for (const auto& c : X) {
        magnitude.push_back(std::abs(c));
    }

    using namespace matplot;
    plot(magnitude);
    title("DFT Magnitude Spectrum");
    xlabel("Frequency bin");
    ylabel("Magnitude");
    show();
}

} 
