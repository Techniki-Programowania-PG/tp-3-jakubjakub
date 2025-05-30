#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

#include "generator.hpp"
#include "fourier.hpp"
#include "filter.hpp"

namespace py = pybind11;

PYBIND11_MODULE(signal_processing, m) {
    m.def("hello", []() { return "Hello from C++ via pybind11!"; });

    m.def("plot_line", &signal::plot_line,
        py::arg("type"),
        py::arg("frequency"),
        py::arg("sample_rate"),
        py::arg("duration"),
        "Generate and plot a signal of specified type using matplot++");

    m.def("generate_signal", &signal::generate_signal,
        py::arg("type"),
        py::arg("frequency"),
        py::arg("sample_rate"),
        py::arg("duration"),
        py::arg("amplitude") = 1.0,
        py::arg("phase_rad") = 0.0,
        "Generate signal with optional amplitude and phase (default 1.0, 0.0)");

    m.def("plot_signal", &signal::plot_signal,
        py::arg("signal"),
        py::arg("title") = "Signal plot",
        "Plot a 1D signal using matplot++");

    m.def("dft", &signal::dft,
        py::arg("signal"),
        "Compute the Discrete Fourier Transform of a signal");

    m.def("idft", &signal::idft,
        py::arg("spectrum"),
        "Compute the inverse Discrete Fourier Transform");

    m.def("plot_dft", &signal::plot_dft,
        py::arg("signal"),
        "Compute DFT and plot its magnitude spectrum");

    m.def("convolve_1d", &signal::convolve_1d,
        py::arg("signal"),
        py::arg("kernel"),
        "Perform 1D convolution of signal with kernel");

    m.def("low_pass_filter", &signal::low_pass_filter,
        py::arg("signal"),
        "Apply simple low-pass filter (3-point moving average) to the signal");

    m.def("convolve_2d", &signal::convolve_2d,
        py::arg("image"),
        py::arg("kernel"),
        "Apply 2D convolution with given kernel");

    m.def("low_pass_filter_2d", &signal::low_pass_filter_2d,
        py::arg("image"),
        "Apply simple 3x3 low-pass filter to 2D image");

    m.def("plot_image", &signal::plot_image,
        py::arg("image"),
        py::arg("title") = "Image",
        "Display 2D image using matplot++");

    py::enum_<signal::SignalType>(m, "SignalType")
        .value("SINE", signal::SignalType::SINE)
        .value("COSINE", signal::SignalType::COSINE)
        .value("SQUARE", signal::SignalType::SQUARE)
        .value("SAWTOOTH", signal::SignalType::SAWTOOTH)
        .export_values();
}
