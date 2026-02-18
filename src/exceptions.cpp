#include <TZBot/Exceptions.h>

#include <pybind11/pybind11.h>
namespace py = pybind11;

static py::exception<QueueAbortException> pyQueueAbortException;
static py::exception<PacketParseException> pyPacketParseException;
static py::exception<SocketReadException> pySocketReadException;

void initExceptions(py::module_& m) {
    pyQueueAbortException = py::register_exception<QueueAbortException>(m, "QueueAbortException");
    pyPacketParseException = py::register_exception<PacketParseException>(m, "PacketParseException");
    pySocketReadException = py::register_exception<SocketReadException>(m, "SocketReadException");

    py::register_exception_translator([](std::exception_ptr ptr) {
        try {
            if (ptr) std::rethrow_exception(ptr);
        } catch (QueueAbortException& e) {
            py::set_error(pyQueueAbortException, e.what());
        } catch (PacketParseException& e) {
            py::set_error(pyPacketParseException, e.what());
        } catch (SocketReadException& e) {
            py::set_error(pySocketReadException, e.what());
        } catch (std::exception& e) {
            throw;
        }
    });
}