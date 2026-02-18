#include <pybind11/pybind11.h>
#include <TZBot/TZBot.h>
#include <TZBot/TZFlags.h>
namespace py = pybind11;

void initData(py::module_&);
void initRequest(py::module_&);
void initExceptions(py::module_&);

PYBIND11_MODULE(_core, m) {
    initData(m);
    initRequest(m);
    initExceptions(m);

    py::class_<TZBot>(m, "TZBot")
        .def(py::init<const std::string&, uint16_t, const std::string&, const std::string&>(), py::arg("ip_address"), py::arg("port"), py::arg("api_key"), py::arg("encryption_key"))
        .def("set_flags", [](TZBot& bot, const py::args& args) {
            std::set<TZFlags> flagsVec;
            for (py::handle item : args) {
                flagsVec.emplace(item.cast<TZFlags>());
            }

            bot.setFlags(flagsVec);
        })
        .def("make_request", [](const TZBot& bot, TZRequest& req) {
            py::object loop = py::module_::import("asyncio").attr("get_running_loop")();
            auto cppFuture = std::make_shared<std::future<TZResponse>>(bot.enqueue(std::move(req)));

            auto waitFunc = [cppFuture]() {
                return cppFuture->get();
            };

            return loop.attr("run_in_executor")(py::none(), py::cpp_function(waitFunc));
        }, py::arg("request"));

    py::enum_<TZFlags>(m, "TZFlags", py::arithmetic())
        .value("AES", TZFlags::AES)
        .value("CHACHA20", TZFlags::CHACHA20)
        .value("GZIP", TZFlags::GZIP)
        .value("MSGPACK", TZFlags::MSGPACK)
        .export_values();
}
