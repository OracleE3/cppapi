#include <sstream>

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp> 

#include "transport/DataPublisher.h"
#include "transport/DataSubscriber.h"

using namespace sttp;
using namespace sttp::data;
using namespace sttp::transport;
using namespace sttp::filterexpressions;

class PyDataRow;
class PyDataColumn;
class PyDataTable;
class PyDataSet;
class PyDataPublisher;

template <typename T>
class SharedPtrWrapper {
protected:
    SharedPtr<T> ref;
    
public:
    SharedPtr<T>& as_shared() { return this->ref; }
    const SharedPtr<T>& as_const_shared() const { return this->ref; }
};

class PyDataRow : public SharedPtrWrapper<DataRow> {
public:
    explicit PyDataRow(SharedPtr<DataRow> row);
    ~PyDataRow() = default;

    // PyDataTable parent();
    
    std::string to_string();
    bool is_null(int32_t columnIndex);
    bool is_null(const std::string& columnName);
    void set_null_value(int32_t columnIndex);
    void set_null_value(const std::string& columnName);

    sttp::Nullable<std::string> value_as_string(int32_t columnIndex);
    sttp::Nullable<std::string> value_as_string(const std::string& columnName);
    void set_string_value(int32_t columnIndex, const sttp::Nullable<std::string>& value);
    void set_string_value(const std::string& columnName, const sttp::Nullable<std::string>& value);

    sttp::Nullable<bool> value_as_boolean(int32_t columnIndex);
    sttp::Nullable<bool> value_as_boolean(const std::string& columnName);
    void set_boolean_value(int32_t columnIndex, const sttp::Nullable<bool>& value);
    void set_boolean_value(const std::string& columnName, const sttp::Nullable<bool>& value);

    sttp::Nullable<sttp::datetime_t> value_as_date_time(int32_t columnIndex);
    sttp::Nullable<sttp::datetime_t> value_as_date_time(const std::string& columnName);
    void set_date_time_value(int32_t columnIndex, const sttp::Nullable<sttp::datetime_t>& value);
    void set_date_time_value(const std::string& columnName, const sttp::Nullable<sttp::datetime_t>& value);

    sttp::Nullable<sttp::float32_t> value_as_single(int32_t columnIndex);
    sttp::Nullable<sttp::float32_t> value_as_single(const std::string& columnName);
    void set_single_value(int32_t columnIndex, const sttp::Nullable<sttp::float32_t>& value);
    void set_single_value(const std::string& columnName, const sttp::Nullable<sttp::float32_t>& value);

    sttp::Nullable<sttp::float64_t> value_as_double(int32_t columnIndex);
    sttp::Nullable<sttp::float64_t> value_as_double(const std::string& columnName);
    void set_double_value(int32_t columnIndex, const sttp::Nullable<sttp::float64_t>& value);
    void set_double_value(const std::string& columnName, const sttp::Nullable<sttp::float64_t>& value);

    sttp::Nullable<sttp::decimal_t> value_as_decimal(int32_t columnIndex);
    sttp::Nullable<sttp::decimal_t> value_as_decimal(const std::string& columnName);
    void set_decimal_value(int32_t columnIndex, const sttp::Nullable<sttp::decimal_t>& value);
    void set_decimal_value(const std::string& columnName, const sttp::Nullable<sttp::decimal_t>& value);

    sttp::Nullable<sttp::Guid> value_as_guid(int32_t columnIndex);
    sttp::Nullable<sttp::Guid> value_as_guid(const std::string& columnName);
    void set_guid_value(int32_t columnIndex, const sttp::Nullable<sttp::Guid>& value);
    void set_guid_value(const std::string& columnName, const sttp::Nullable<sttp::Guid>& value);

    sttp::Nullable<int8_t> value_as_int8(int32_t columnIndex);
    sttp::Nullable<int8_t> value_as_int8(const std::string& columnName);
    void set_int8_value(int32_t columnIndex, const sttp::Nullable<int8_t>& value);
    void set_int8_value(const std::string& columnName, const sttp::Nullable<int8_t>& value);

    sttp::Nullable<int16_t> value_as_int16(int32_t columnIndex);
    sttp::Nullable<int16_t> value_as_int16(const std::string& columnName);
    void set_int16_value(int32_t columnIndex, const sttp::Nullable<int16_t>& value);
    void set_int16_value(const std::string& columnName, const sttp::Nullable<int16_t>& value);

    sttp::Nullable<int32_t> value_as_int32(int32_t columnIndex);
    sttp::Nullable<int32_t> value_as_int32(const std::string& columnName);
    void set_int32_value(int32_t columnIndex, const sttp::Nullable<int32_t>& value);
    void set_int32_value(const std::string& columnName, const sttp::Nullable<int32_t>& value);

    sttp::Nullable<int64_t> value_as_int64(int32_t columnIndex);
    sttp::Nullable<int64_t> value_as_int64(const std::string& columnName);
    void set_int64_value(int32_t columnIndex, const sttp::Nullable<int64_t>& value);
    void set_int64_value(const std::string& columnName, const sttp::Nullable<int64_t>& value);

    sttp::Nullable<uint8_t> value_as_u_int8(int32_t columnIndex);
    sttp::Nullable<uint8_t> value_as_u_int8(const std::string& columnName);
    void set_u_int8_value(int32_t columnIndex, const sttp::Nullable<uint8_t>& value);
    void set_u_int8_value(const std::string& columnName, const sttp::Nullable<uint8_t>& value);

    sttp::Nullable<uint16_t> value_as_u_int16(int32_t columnIndex);
    sttp::Nullable<uint16_t> value_as_u_int16(const std::string& columnName);
    void set_u_int16_value(int32_t columnIndex, const sttp::Nullable<uint16_t>& value);
    void set_u_int16_value(const std::string& columnName, const sttp::Nullable<uint16_t>& value);

    sttp::Nullable<uint32_t> value_as_u_int32(int32_t columnIndex);
    sttp::Nullable<uint32_t> value_as_u_int32(const std::string& columnName);
    void set_u_int32_value(int32_t columnIndex, const sttp::Nullable<uint32_t>& value);
    void set_u_int32_value(const std::string& columnName, const sttp::Nullable<uint32_t>& value);

    sttp::Nullable<uint64_t> value_as_u_int64(int32_t columnIndex);
    sttp::Nullable<uint64_t> value_as_u_int64(const std::string& columnName);
    void set_u_int64_value(int32_t columnIndex, const sttp::Nullable<uint64_t>& value);
    void set_u_int64_value(const std::string& columnName, const sttp::Nullable<uint64_t>& value);
};

class PyDataColumn : public SharedPtrWrapper<DataColumn> {
public:
    explicit PyDataColumn(SharedPtr<DataColumn> column);
    ~PyDataColumn() = default;

    std::string to_string();
    PyDataTable parent();
    const std::string& name();
    DataType type();
    const std::string& expression();
    bool computed();
    int32_t index();
};

class PyDataTable : public SharedPtrWrapper<DataTable> {
public:
    explicit PyDataTable(SharedPtr<DataTable> table);
    ~PyDataTable() = default;

    std::string to_string();
    PyDataSet parent();
    const std::string& name();
    void add_column(PyDataColumn column);
    PyDataColumn column(const std::string& columnName);
    PyDataColumn column(int32_t index);
    PyDataColumn operator[](const std::string& columnName);
    PyDataColumn operator[](int32_t index);
    PyDataColumn create_column(const std::string& name, DataType type, std::string expression = std::string{});
    PyDataColumn clone_column(const PyDataColumn& source);
    int32_t column_count();
    PyDataRow row(int32_t index);
    void add_row(PyDataRow row);
    PyDataRow create_row();
    PyDataRow clone_row(const PyDataRow& source);
    int32_t row_count();
};

class PyDataSet : public SharedPtrWrapper<DataSet> {
public:
    explicit PyDataSet();
    explicit PyDataSet(SharedPtr<DataSet> data_set);
    ~PyDataSet() = default;

    std::string to_string();
    PyDataTable table(const std::string& tableName);
    PyDataTable operator[](const std::string& tableName);
    // PyDataTable create_table(const std::string& name);
    int32_t table_count();
    std::vector<std::string> table_names();
    std::vector<PyDataTable> tables();
    bool add_or_update_table(PyDataTable table);
    bool remove_table(const std::string& tableName);
    void read_xml(const std::string& fileName);
    void read_xml(const std::vector<uint8_t>& buffer);
    // void read_xml(const uint8_t* buffer, uint32_t length);
    // void read_xml(const pugi::xml_document& document);
    void write_xml(const std::string& fileName, const std::string& dataSetName = "DataSet");
    void write_xml(std::vector<uint8_t>& buffer, const std::string& dataSetName = "DataSet");
    // void write_xml(pugi::xml_document& document, const std::string& dataSetName = "DataSet");
    static PyDataSet from_xml(const std::string& fileName);
    static PyDataSet from_xml(const std::vector<uint8_t>& buffer);
    // static PyDataSet from_xml(const uint8_t* buffer, uint32_t length);
    // static PyDataSet from_xml(const pugi::xml_document& document);
};

class PyDataPublisher : public SharedPtrWrapper<DataPublisher> {
public:
    PyDataPublisher();

    ~PyDataPublisher() = default;

    void start(const uint16_t port, const bool ipV6 = false);
    void start(const std::string& ip, const uint16_t port);
    void stop();
    void connect(const std::string& hostname, uint16_t port);
    
    bool is_started();

    uint16_t get_port();
    bool is_ipv6();

    std::string get_node_id();

    void set_node_id(const std::string& value);
};
