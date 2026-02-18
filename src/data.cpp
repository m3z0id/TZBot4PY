#include <pybind11/pybind11.h>
#include <pybind11_json/pybind11_json.hpp>
#include <TZBot/TZData.h>

namespace py = pybind11;

class PyITZData : public ITZData, public pybind11::trampoline_self_life_support {
public:
    using ITZData::ITZData;
    [[nodiscard]] uint8_t getByteRepr() const override { PYBIND11_OVERRIDE_PURE(uint8_t, ITZData, get_byte_representation); }
    [[nodiscard]] bool isAPIKeyNeeded() const override { PYBIND11_OVERRIDE_PURE(bool, ITZData, is_api_key_needed); }
    [[nodiscard]] nlohmann::json toJson() const override { PYBIND11_OVERRIDE_PURE(nlohmann::json, ITZData, to_json); }
};

void initData(py::module_& m) {
    py::class_<ITZData, PyITZData, py::smart_holder>(m, "ITZData")
        .def(py::init<>())
        .def("get_byte_representation", &ITZData::getByteRepr)
        .def("is_api_key_needed", &ITZData::isAPIKeyNeeded)
        .def("to_json", &ITZData::toJson);

    py::class_<PingData, ITZData, py::smart_holder>(m, "PingData")
        .def(py::init<>())
        .def("get_byte_representation", &PingData::getByteRepr)
        .def("is_api_key_needed", &PingData::isAPIKeyNeeded)
        .def("to_json", &PingData::toJson);

    py::class_<TimezoneFromUserIDData, ITZData, py::smart_holder>(m, "TimezoneFromUserIDData")
        .def(py::init<uint64_t>(), py::arg("user_id"))
        .def("get_byte_representation", &TimezoneFromUserIDData::getByteRepr)
        .def("is_api_key_needed", &TimezoneFromUserIDData::isAPIKeyNeeded)
        .def("to_json", &TimezoneFromUserIDData::toJson);

    py::class_<TimezoneFromIPData, ITZData, py::smart_holder>(m, "TimezoneFromIPData")
        .def(py::init<const std::string&>(), py::arg("ip_address"))
        .def("get_byte_representation", &TimezoneFromIPData::getByteRepr)
        .def("is_api_key_needed", &TimezoneFromIPData::isAPIKeyNeeded)
        .def("to_json", &TimezoneFromIPData::toJson);

    py::class_<UserIDUUIDLinkData, ITZData, py::smart_holder>(m, "UserIDUUIDLinkData")
        .def(py::init<uint64_t, const std::string&>(), py::arg("user_id"), py::arg("uuid"))
        .def("get_byte_representation", &UserIDUUIDLinkData::getByteRepr)
        .def("is_api_key_needed", &UserIDUUIDLinkData::isAPIKeyNeeded)
        .def("to_json", &UserIDUUIDLinkData::toJson);

    py::class_<TimezoneFromUUIDData, ITZData, py::smart_holder>(m, "TimezoneFromUUIDData")
        .def(py::init<const std::string&>(), py::arg("uuid"))
        .def("get_byte_representation", &TimezoneFromUUIDData::getByteRepr)
        .def("is_api_key_needed", &TimezoneFromUUIDData::isAPIKeyNeeded)
        .def("to_json", &TimezoneFromUUIDData::toJson);

    py::class_<IsLinkedData, ITZData, py::smart_holder>(m, "IsLinkedData")
        .def(py::init<const std::string>(), py::arg("uuid"))
        .def("get_byte_representation", &IsLinkedData::getByteRepr)
        .def("is_api_key_needed", &IsLinkedData::isAPIKeyNeeded)
        .def("to_json", &IsLinkedData::toJson);

    py::class_<UserIdFromUUIDData, ITZData, py::smart_holder>(m, "UserIdFromUUIDData")
        .def(py::init<const std::string&>(), py::arg("uuid"))
        .def("get_byte_representation", &UserIdFromUUIDData::getByteRepr)
        .def("is_api_key_needed", &UserIdFromUUIDData::isAPIKeyNeeded)
        .def("to_json", &UserIdFromUUIDData::toJson);

    py::class_<UUIDFromUserIDData, ITZData, py::smart_holder>(m, "UUIDFromUserIDData")
        .def(py::init<uint64_t>(), py::arg("user_id"))
        .def("get_byte_representation", &UUIDFromUserIDData::getByteRepr)
        .def("is_api_key_needed", &UUIDFromUserIDData::isAPIKeyNeeded)
        .def("to_json", &UUIDFromUserIDData::toJson);

    py::class_<UpdateTimezoneData, ITZData, py::smart_holder>(m, "UpdateTimezoneData")
        .def(py::init<const std::string&, const std::string&>(), py::arg("uuid"), py::arg("timezone"))
        .def("get_byte_representation", &UpdateTimezoneData::getByteRepr)
        .def("is_api_key_needed", &UpdateTimezoneData::isAPIKeyNeeded)
        .def("to_json", &UpdateTimezoneData::toJson);
}