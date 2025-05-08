#include <iostream>

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include "../lib/transport/DataPublisher.h"
#include "../lib/transport/DataSubscriber.h"

namespace nb = nanobind;
using namespace nb::literals;

using namespace sttp;
using namespace sttp::data;
using namespace sttp::transport;
using namespace sttp::filterexpressions;

class PyDataPublisher {
private:
    SharedPtr<DataPublisher> publisher;

public:
    PyDataPublisher() { this->publisher = NewSharedPtr<DataPublisher>(); }

    ~PyDataPublisher() = default;

    void start(const uint16_t port, const bool ipV6 = false) { this->publisher->Start(port, ipV6); }
    void start(const std::string& ip, const uint16_t port) { this->publisher->Start(ip, port); }
    void stop() { this->publisher->Stop(); }
    void connect(const std::string& hostname, uint16_t port) { this->publisher->Connect(hostname, port); }
    
    bool is_started() { return this->publisher->IsStarted(); }

    uint16_t get_port() { return this->publisher->GetPort(); }
    bool is_ipv6() { return this->publisher->IsIPv6(); }

    const Guid& get_node_id() { return this->publisher->GetNodeID(); }
    void set_node_id(const Guid& value) { this->publisher->SetNodeID(value); }
};

int add(int a, int b) { return a + b; }

void process_string(const std::string& input_string) {
    // Process the string
    std::cout << "Got string '" << input_string << "'" << std::endl;
}

NB_MODULE(py_sttp, m) {
    m.def("add", &add, "a"_a, "b"_a = 1,
          "This function adds two numbers and increments if only one is provided.");
    m.def("process_string", &process_string);
    nb::class_<PyDataPublisher>(m, "DataPublisher")
        .def(nb::init<>())
        .def(
            "start",
            nb::overload_cast<uint16_t, bool>(&PyDataPublisher::start),
            "Starts the publisher with just a TCP port"
        )
        .def(
            "start",
            nb::overload_cast<const std::string&, uint16_t>(&PyDataPublisher::start),
            "Starts the publisher with hostname and port"
        )
        .def("stop", &PyDataPublisher::stop, "Stops the publisher")
        .def("connect", &PyDataPublisher::connect, "Reverse connect to DataSubscriber")
        .def("is_started", &PyDataPublisher::is_started, "Check if publisher has been started")
        .def("get_port", &PyDataPublisher::get_port, "Gets the TCP port")
        .def("is_ipv6", &PyDataPublisher::is_ipv6, "Check if address is IPV6")
        .def("get_node_id", &PyDataPublisher::get_node_id, "Gets the node ID")
    ;
}