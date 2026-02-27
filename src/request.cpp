#include <pybind11/pybind11.h>
#include <pybind11_json/pybind11_json.hpp>
#include <pybind11/stl.h>
#include <TZBot/TZRequest.h>
#include <TZBot/TZResponse.h>

namespace py = pybind11;

void initRequest(py::module_& m) {
    py::class_<TZRequest>(m, "TZRequest")
        .def(py::init<std::unique_ptr<ITZData>>(), py::arg("data"))
        .def("to_json", &TZRequest::toJson)
        .def("get_request_type", &TZRequest::getRequestType);

    py::class_<TZResponse>(m, "TZResponse")
        .def("to_json", &TZResponse::toJson)
        .def("is_successful", &TZResponse::isSuccessful)
        .def("get_code", &TZResponse::getCode)
        .def("get_response_str", &TZResponse::getResponseAsString)
        .def("get_response_int", [](const TZResponse& resp) -> std::optional<uint64_t> {
            if (auto longVal = resp.getResponseAsLong()) return *longVal;
            if (auto intVal = resp.getResponseAsInt()) return *intVal;
            return std::nullopt;
        });
}