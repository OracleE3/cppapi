#include <nanobind/nanobind.h>

#include "../lib/transport/DataPublisher.h"
#include "../lib/transport/DataSubscriber.h"

namespace nb = nanobind;

using namespace sttp;
using namespace sttp::data;
using namespace sttp::transport;
using namespace sttp::filterexpressions;

int add(int a, int b) { return a + b; }

NB_MODULE(py_sttp, m) {
    m.def("add", &add);
    nb::class_<DataPublisher>(m, "DataPublisher")
        .def(nb::init<>());
}