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
        .def(py::init<const std::string&, uint16_t, const std::string&, const std::array<uint8_t, 32>*>(), py::arg("ip_address"), py::arg("port"), py::arg("api_key"), py::arg("encryption_key"))
        .def("set_flags", [](TZBot& bot, const py::args& args) {
            uint8_t flags = 0;
            for (py::handle item : args) {
                if (!py::isinstance<TZFlags>(item) && !py::isinstance<py::int_>(item)) throw py::type_error("set_flags expects TZFlags or integers");

                flags |= static_cast<uint8_t>(item.cast<unsigned int>());
            }

            bot.setFlags(flags);
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
        .value("MSGPACK", TZFlags::MSGPACK)
        .export_values();
}
