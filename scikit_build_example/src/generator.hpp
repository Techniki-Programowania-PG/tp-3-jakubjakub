#pragma once

#include <vector>
#include <string>

namespace signal {

enum class SignalType {
    SINE,
    COSINE,
    SQUARE,
    SAWTOOTH
};

std::vector<double> generate_signal(SignalType type, double frequency,double sample_rate,double duration,double amplitude = 1.0,double phase_rad = 0.0);

void plot_line(SignalType type, double frequency, double sample_rate, double duration);

void plot_signal(const std::vector<double>& signal, const std::string& title_str = "Signal plot");

} 
