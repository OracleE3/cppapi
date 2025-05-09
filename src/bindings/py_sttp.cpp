#include <iostream>

#include <nanobind/nanobind.h>
#include <nanobind/stl/shared_ptr.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include "../lib/Python.hpp"

namespace nb = nanobind;
using namespace nb::literals;

int add(int a, int b) { return a + b; }

void process_string(const std::string& input_string) {
    // Process the string
    std::cout << "Got string '" << input_string << "'" << std::endl;
}

NB_MODULE(py_sttp, m) {
    m.def("add", &add, "a"_a, "b"_a = 1,
          "This function adds two numbers and increments if only one is provided.");
    m.def("process_string", &process_string);
    nb::class_<PyDataTable>(m, "DataTable")
        // .def(nb::init<>())
        .def("__repr__", &PyDataTable::to_string, "Get table as string")
        .def("__len__", &PyDataTable::row_count, "Allow len() to get the number of rows")
        .def("name", &PyDataTable::name, "Get the table name string")
        .def(
            "column",
            nb::overload_cast<const std::string&>(&PyDataTable::column),
            "Get a column by string name"
        )
        .def(
            "column",
            nb::overload_cast<int32_t>(&PyDataTable::column),
            "Get a column by index"
        )
        .def("row", &PyDataTable::row, "Get a column by index")
        .def("column_count", &PyDataTable::column_count, "Get number of columns")
        .def("row_count", &PyDataTable::row_count, "Get number of rows")
    ;
    nb::class_<PyDataRow>(m, "DataRow")
        // .def(nb::init<>())
        .def("__repr__", &PyDataRow::to_string, "Get the row as a string")
        // .def("__len__", [](const PyDataRow& self) { return self.})
    ;
    nb::class_<PyDataColumn>(m, "DataColumn")
        // .def(nb::init<>())
        .def("__repr__", &PyDataColumn::to_string, "Get the column as a string")
        .def("name", [](PyDataColumn& self) { return self.name(); }, "Get the column name")
        .def("type", [](PyDataColumn& self) { return self.type(); }, "Get the column type")
        .def("expression", [](PyDataColumn& self) { return self.expression(); }, "Get the column expression")
        .def("computed", [](PyDataColumn& self) { return self.computed(); }, "Check whether the column was computed or not")
        .def("index", [](PyDataColumn& self) { return self.index(); }, "Get the column index")
    ;
    nb::class_<PyDataSet>(m, "DataSet")
        .def(nb::init<>())
        .def("__repr__", &PyDataSet::to_string, "Print dataset as string")
        .def("table", &PyDataSet::table, "Get a table by name")
        .def("tables", &PyDataSet::tables, "Get a list of all tables")
        .def("table_count", &PyDataSet::table_count, "List the number of tables in the data set")
        .def("table_names", &PyDataSet::table_names, "Get a table by name")
        .def(
            "read_xml",
            nb::overload_cast<const std::string&>(&PyDataSet::read_xml),
            "Populate object from an XML file"
        )
        // .def_static("from_xml", &PyDataSet::from_xml, "Create a DataSet from an XML file")
    ;
    nb::class_<PyDataPublisher>(m, "DataPublisher")
        .def(nb::init<>())
        .def(
            "start",
            nb::overload_cast<uint16_t, bool>(&PyDataPublisher::start),
            "Starts the ref with just a TCP port"
        )
        .def(
            "start",
            nb::overload_cast<const std::string&, uint16_t>(&PyDataPublisher::start),
            "Starts the ref with hostname and port"
        )
        .def("stop", &PyDataPublisher::stop, "Stops the ref")
        .def("connect", &PyDataPublisher::connect, "Reverse connect to DataSubscriber")
        .def("is_started", &PyDataPublisher::is_started, "Check if ref has been started")
        .def("get_port", &PyDataPublisher::get_port, "Gets the TCP port")
        .def("is_ipv6", &PyDataPublisher::is_ipv6, "Check if address is IPV6")
        .def("get_node_id", &PyDataPublisher::get_node_id, "Gets the node ID")
    ;
}