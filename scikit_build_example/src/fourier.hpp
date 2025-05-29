#pragma once
#include <vector>
#include <complex>

namespace signal {

std::vector<std::complex<double>> dft(const std::vector<double>& signal);

std::vector<double> idft(const std::vector<std::complex<double>>& spectrum);

void plot_dft(const std::vector<double>& signal);

} 
