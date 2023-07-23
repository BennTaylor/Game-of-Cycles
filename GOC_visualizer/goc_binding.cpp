#include <pybind11/pybind11.h>
#include "../src/goc_game_tree.h"

namespace py = pybind11;

/*
 * Instructions for pybind11 module compilation:
 *  - cd build
 *  - cmake ..
 *  - make
 *  - cd ..
 */

PYBIND11_MODULE(game_of_cycles, handle) {
    handle.doc() = "Game of Cycles Class.";

    py::class_<GOC>(handle, "pyGOC")
        .def(py::init<string&>())
        .def("name", &GOC::name);
}