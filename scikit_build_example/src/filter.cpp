#include "filter.hpp"
#include <stdexcept>
#include <matplot/matplot.h>

using namespace matplot;


namespace signal {

std::vector<double> convolve_1d(const std::vector<double>& signal, const std::vector<double>& kernel) {
    int n = static_cast<int>(signal.size());
    int k = static_cast<int>(kernel.size());
    int half_k = k / 2;

    if (k == 0) throw std::invalid_argument("Kernel size cannot be zero");

    std::vector<double> result(n, 0.0);

    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        for (int j = 0; j < k; ++j) {
            int idx = i + j - half_k;
            if (idx >= 0 && idx < n) {
                sum += signal[idx] * kernel[j];
            }
        }
        result[i] = sum;
    }
    return result;
}

std::vector<double> low_pass_filter(const std::vector<double>& signal) {
    std::vector<double> kernel = {1.0/3, 1.0/3, 1.0/3};
    return convolve_1d(signal, kernel);
}

std::vector<std::vector<double>> convolve_2d(const std::vector<std::vector<double>>& image,
                                             const std::vector<std::vector<double>>& kernel) {
    int height = static_cast<int>(image.size());
    int width = static_cast<int>(image[0].size());
    int kh = static_cast<int>(kernel.size());
    int kw = static_cast<int>(kernel[0].size());
    int kh2 = kh / 2;
    int kw2 = kw / 2;

    std::vector<std::vector<double>> result(height, std::vector<double>(width, 0.0));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double sum = 0.0;
            for (int j = 0; j < kh; ++j) {
                for (int i = 0; i < kw; ++i) {
                    int yy = y + j - kh2;
                    int xx = x + i - kw2;
                    if (yy >= 0 && yy < height && xx >= 0 && xx < width) {
                        sum += image[yy][xx] * kernel[j][i];
                    }
                }
            }
            result[y][x] = sum;
        }
    }
    return result;
}

std::vector<std::vector<double>> low_pass_filter_2d(const std::vector<std::vector<double>>& image) {
    std::vector<std::vector<double>> kernel = {
        {1.0/9, 1.0/9, 1.0/9},
        {1.0/9, 1.0/9, 1.0/9},
        {1.0/9, 1.0/9, 1.0/9}
    };
    return convolve_2d(image, kernel);
}

void plot_image(const std::vector<std::vector<double>>& image, const std::string& title_str) {
    figure();
    imagesc(image);
    colorbar();
    title(title_str);
    show();
}


}
