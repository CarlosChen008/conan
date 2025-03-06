#include "npy.hpp"
#include <vector>
#include <string>

int main() {
  const std::vector<double> data{1, 2, 3, 4, 5, 6};

  npy::npy_data_ptr<double> d;
  d.data_ptr = data.data();
  d.shape = {2, 3};
  d.fortran_order = false; // optional

  const std::string path{"../data/out.npy"};
  npy::write_npy(path, d);
}

