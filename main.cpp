#include "OrderBook.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
namespace py = pybind11;

PYBIND11_MODULE(orderbook, m) {
    m.doc() = "pybind11 orderbook";
    py::class_<OrderBook>(m, "OrderBook")
        .def(py::init<bool>(), py::arg("verbose"))
        .def("printBook", &OrderBook::printBook, py::call_guard<py::scoped_ostream_redirect,
                     py::scoped_estream_redirect>())
        .def("addOrder", &OrderBook::addOrder, py::arg("uid"), py::arg("side"), py::arg("price"), py::arg("size"), py::call_guard<py::scoped_ostream_redirect,
                     py::scoped_estream_redirect>())
        .def("deleteOrder", &OrderBook::deleteOrder, py::arg("uid"), py::call_guard<py::scoped_ostream_redirect,
                     py::scoped_estream_redirect>())
        .def("updateOrder", &OrderBook::updateOrder, py::arg("uid"), py::arg("size"), py::call_guard<py::scoped_ostream_redirect,
                     py::scoped_estream_redirect>());
}