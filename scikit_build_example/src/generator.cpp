#include "generator.hpp"
#include <cmath>
#include <matplot/matplot.h>
#include <stdexcept>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace matplot;

namespace signal {

std::vector<double> generate_signal(SignalType type, double frequency, double sample_rate, double duration, double amplitude, double phase_rad) {
    size_t N = static_cast<size_t>(sample_rate * duration);
    std::vector<double> y(N);

    for (size_t i = 0; i < N; ++i) {
        double t = static_cast<double>(i) / sample_rate;
        switch (type) {
            case SignalType::SINE:
                y[i] = amplitude * std::sin(2 * M_PI * frequency * t + phase_rad);
                break;
            case SignalType::COSINE:
                y[i] = amplitude * std::cos(2 * M_PI * frequency * t + phase_rad);
                break;
            case SignalType::SQUARE:
                y[i] = amplitude * ((std::sin(2 * M_PI * frequency * t + phase_rad) >= 0) ? 1.0 : -1.0);
                break;
            case SignalType::SAWTOOTH:
                y[i] = amplitude * (2.0 * (t * frequency - std::floor(0.5 + t * frequency)));
                break;
            default:
                throw std::invalid_argument("Unknown signal type");
        }
    }
    return y;
}


void plot_line(SignalType type, double frequency, double sample_rate, double duration) {
    auto y = generate_signal(type, frequency, sample_rate, duration);
    size_t N = y.size();
    std::vector<double> t(N);
    for (size_t i = 0; i < N; ++i) {
        t[i] = static_cast<double>(i) / sample_rate;
    }

    plot(t, y);
    title("Signal plot");
    xlabel("Time [s]");
    ylabel("Amplitude");
    show();
}

void plot_signal(const std::vector<double>& signal, const std::string& title_str) {
    using namespace matplot;
    plot(signal);
    title(title_str);
    xlabel("Sample index");
    ylabel("Amplitude");
    show();
}

} 
