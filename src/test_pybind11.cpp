#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int a, int b) {
    return a + b;
}

PYBIND11_MODULE(test_pybind11, m) {
    m.doc() = "A simple example module"; // 可选模块文档
    m.def("add", &add, "A function that adds two numbers");
}

