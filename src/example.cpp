#include <pybind11/embed.h>
namespace py = pybind11;

int main() {
    py::scoped_interpreter guard{};

    py::module_ hashlib = py::module_::import("hashlib");
    py::object sha256 = hashlib.sha256()
    sha256.update(password)
    //print(sha256.hexdigest().encode())

}