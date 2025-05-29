#pragma once
#include <vector>
#include<string>

namespace signal {

std::vector<double> convolve_1d(const std::vector<double>& signal, const std::vector<double>& kernel);

std::vector<double> low_pass_filter(const std::vector<double>& signal);

std::vector<std::vector<double>> convolve_2d(const std::vector<std::vector<double>>& image,
                                             const std::vector<std::vector<double>>& kernel);

std::vector<std::vector<double>> low_pass_filter_2d(const std::vector<std::vector<double>>& image);
void plot_image(const std::vector<std::vector<double>>& image, const std::string& title = "Image");

} 
