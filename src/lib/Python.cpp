#include <boost/date_time/posix_time/time_formatters.hpp>

#include "Python.hpp"

PyDataRow::PyDataRow(SharedPtr<DataRow> row) { this->ref = row; }

// PyDataTable PyDataRow::parent() { return PyDataTable(this->ref->Parent()); }
std::string PyDataRow::to_string() {
    std::stringstream ss;
    ss << "[";
    for (int32_t i = 0; i < this->ref->Parent()->ColumnCount(); ++i) {
        if (i > 0) ss << ", ";
        DataType col_type = this->ref->Parent()->Column(i)->Type();
        datetime_t dt;
        switch (col_type) {
            case DataType::String:
                ss << "\"" << this->ref->ValueAsString(i).GetValueOrDefault("") << "\"";
                break;
            case DataType::Boolean:
                ss << this->ref->ValueAsBoolean(i).GetValueOrDefault(false);
                break;
            case DataType::DateTime:
                dt = this->ref->ValueAsDateTime(i).GetValueOrDefault(dt);
                ss << to_iso_string(dt);
                break;
            case DataType::Single:
                ss << this->ref->ValueAsSingle(i).GetValueOrDefault(0);
                break;
            case DataType::Double:
                ss << this->ref->ValueAsDouble(i).GetValueOrDefault(0);
                break;
            case DataType::Decimal:
                ss << this->ref->ValueAsDecimal(i).GetValueOrDefault(0);
                break;
            case DataType::Guid:
                ss << boost::uuids::to_string(this->ref->ValueAsGuid(i).GetValueOrDefault(NewGuid()));
                break;
            case DataType::Int8:
                ss << this->ref->ValueAsInt8(i).GetValueOrDefault(0);
                break;
            case DataType::Int16:
                ss << this->ref->ValueAsInt16(i).GetValueOrDefault(0);
                break;
            case DataType::Int32:
                ss << this->ref->ValueAsInt32(i).GetValueOrDefault(0);
                break;
            case DataType::Int64:
                ss << this->ref->ValueAsInt64(i).GetValueOrDefault(0);
                break;
            case DataType::UInt8:
                ss << this->ref->ValueAsUInt8(i).GetValueOrDefault(0);
                break;
            case DataType::UInt16:
                ss << this->ref->ValueAsUInt16(i).GetValueOrDefault(0);
                break;
            case DataType::UInt32:
                ss << this->ref->ValueAsUInt32(i).GetValueOrDefault(0);
                break;
            case DataType::UInt64:
                ss << this->ref->ValueAsUInt64(i).GetValueOrDefault(0);
                break;
        };
    }
    ss << "]";
    return ss.str();
}
bool PyDataRow::is_null(int32_t columnIndex) { return this->ref->IsNull(columnIndex); }
bool PyDataRow::is_null(const std::string& columnName) { return this->ref->IsNull(columnName); }
void PyDataRow::set_null_value(int32_t columnIndex) { return this->ref->SetNullValue(columnIndex); }
void PyDataRow::set_null_value(const std::string& columnName) { return this->ref->SetNullValue(columnName); }

sttp::Nullable<std::string> PyDataRow::value_as_string(int32_t columnIndex) { return this->ref->ValueAsString(columnIndex); }
sttp::Nullable<std::string> PyDataRow::value_as_string(const std::string& columnName) { return this->ref->ValueAsString(columnName); }
void PyDataRow::set_string_value(int32_t columnIndex, const sttp::Nullable<std::string>& value) { this->ref->SetStringValue(columnIndex, value); }
void PyDataRow::set_string_value(const std::string& columnName, const sttp::Nullable<std::string>& value) { this->ref->SetStringValue(columnName, value); }

sttp::Nullable<bool> PyDataRow::value_as_boolean(int32_t columnIndex) { return this->ref->ValueAsBoolean(columnIndex); }
sttp::Nullable<bool> PyDataRow::value_as_boolean(const std::string& columnName) { return this->ref->ValueAsBoolean(columnName); }
void PyDataRow::set_boolean_value(int32_t columnIndex, const sttp::Nullable<bool>& value) { this->ref->SetBooleanValue(columnIndex, value); }
void PyDataRow::set_boolean_value(const std::string& columnName, const sttp::Nullable<bool>& value) { this->ref->SetBooleanValue(columnName, value); }

sttp::Nullable<sttp::datetime_t> PyDataRow::value_as_date_time(int32_t columnIndex) { return this->ref->ValueAsDateTime(columnIndex); }
sttp::Nullable<sttp::datetime_t> PyDataRow::value_as_date_time(const std::string& columnName) { return this->ref->ValueAsDateTime(columnName); }
void PyDataRow::set_date_time_value(int32_t columnIndex, const sttp::Nullable<sttp::datetime_t>& value) { this->ref->SetDateTimeValue(columnIndex, value); }
void PyDataRow::set_date_time_value(const std::string& columnName, const sttp::Nullable<sttp::datetime_t>& value) { this->ref->SetDateTimeValue(columnName, value); }

sttp::Nullable<sttp::float32_t> PyDataRow::value_as_single(int32_t columnIndex) { return this->ref->ValueAsSingle(columnIndex); }
sttp::Nullable<sttp::float32_t> PyDataRow::value_as_single(const std::string& columnName) { return this->ref->ValueAsSingle(columnName); }
void PyDataRow::set_single_value(int32_t columnIndex, const sttp::Nullable<sttp::float32_t>& value) { this->ref->SetSingleValue(columnIndex, value); }
void PyDataRow::set_single_value(const std::string& columnName, const sttp::Nullable<sttp::float32_t>& value) { this->ref->SetSingleValue(columnName, value); }

sttp::Nullable<sttp::float64_t> PyDataRow::value_as_double(int32_t columnIndex) { return this->ref->ValueAsDouble(columnIndex); }
sttp::Nullable<sttp::float64_t> PyDataRow::value_as_double(const std::string& columnName) { return this->ref->ValueAsDouble(columnName); }
void PyDataRow::set_double_value(int32_t columnIndex, const sttp::Nullable<sttp::float64_t>& value) { this->ref->SetDoubleValue(columnIndex, value); }
void PyDataRow::set_double_value(const std::string& columnName, const sttp::Nullable<sttp::float64_t>& value) { this->ref->SetDoubleValue(columnName, value); }

sttp::Nullable<sttp::decimal_t> PyDataRow::value_as_decimal(int32_t columnIndex) { return this->ref->ValueAsDecimal(columnIndex); }
sttp::Nullable<sttp::decimal_t> PyDataRow::value_as_decimal(const std::string& columnName) { return this->ref->ValueAsDecimal(columnName); }
void PyDataRow::set_decimal_value(int32_t columnIndex, const sttp::Nullable<sttp::decimal_t>& value) { this->ref->SetDecimalValue(columnIndex, value); }
void PyDataRow::set_decimal_value(const std::string& columnName, const sttp::Nullable<sttp::decimal_t>& value) { this->ref->SetDecimalValue(columnName, value); }

sttp::Nullable<sttp::Guid> PyDataRow::value_as_guid(int32_t columnIndex) { return this->ref->ValueAsGuid(columnIndex); }
sttp::Nullable<sttp::Guid> PyDataRow::value_as_guid(const std::string& columnName) { return this->ref->ValueAsGuid(columnName); }
void PyDataRow::set_guid_value(int32_t columnIndex, const sttp::Nullable<sttp::Guid>& value) { this->ref->SetGuidValue(columnIndex, value); }
void PyDataRow::set_guid_value(const std::string& columnName, const sttp::Nullable<sttp::Guid>& value) { this->ref->SetGuidValue(columnName, value); }

sttp::Nullable<int8_t> PyDataRow::value_as_int8(int32_t columnIndex) { return this->ref->ValueAsInt8(columnIndex); }
sttp::Nullable<int8_t> PyDataRow::value_as_int8(const std::string& columnName) { return this->ref->ValueAsInt8(columnName); }
void PyDataRow::set_int8_value(int32_t columnIndex, const sttp::Nullable<int8_t>& value) { this->ref->SetInt8Value(columnIndex, value); }
void PyDataRow::set_int8_value(const std::string& columnName, const sttp::Nullable<int8_t>& value) { this->ref->SetInt8Value(columnName, value); }

sttp::Nullable<int16_t> PyDataRow::value_as_int16(int32_t columnIndex) { return this->ref->ValueAsInt16(columnIndex); }
sttp::Nullable<int16_t> PyDataRow::value_as_int16(const std::string& columnName) { return this->ref->ValueAsInt16(columnName); }
void PyDataRow::set_int16_value(int32_t columnIndex, const sttp::Nullable<int16_t>& value) { this->ref->SetInt16Value(columnIndex, value); }
void PyDataRow::set_int16_value(const std::string& columnName, const sttp::Nullable<int16_t>& value) { this->ref->SetInt16Value(columnName, value); }

sttp::Nullable<int32_t> PyDataRow::value_as_int32(int32_t columnIndex) { return this->ref->ValueAsInt32(columnIndex); }
sttp::Nullable<int32_t> PyDataRow::value_as_int32(const std::string& columnName) { return this->ref->ValueAsInt32(columnName); }
void PyDataRow::set_int32_value(int32_t columnIndex, const sttp::Nullable<int32_t>& value) { this->ref->SetInt32Value(columnIndex, value); }
void PyDataRow::set_int32_value(const std::string& columnName, const sttp::Nullable<int32_t>& value) { this->ref->SetInt32Value(columnName, value); }

sttp::Nullable<int64_t> PyDataRow::value_as_int64(int32_t columnIndex) { return this->ref->ValueAsInt64(columnIndex); }
sttp::Nullable<int64_t> PyDataRow::value_as_int64(const std::string& columnName) { return this->ref->ValueAsInt64(columnName); }
void PyDataRow::set_int64_value(int32_t columnIndex, const sttp::Nullable<int64_t>& value) { this->ref->SetInt64Value(columnIndex, value); }
void PyDataRow::set_int64_value(const std::string& columnName, const sttp::Nullable<int64_t>& value) { this->ref->SetInt64Value(columnName, value); }

sttp::Nullable<uint8_t> PyDataRow::value_as_u_int8(int32_t columnIndex) { return this->ref->ValueAsUInt8(columnIndex); }
sttp::Nullable<uint8_t> PyDataRow::value_as_u_int8(const std::string& columnName) { return this->ref->ValueAsUInt8(columnName); }
void PyDataRow::set_u_int8_value(int32_t columnIndex, const sttp::Nullable<uint8_t>& value) { this->ref->SetUInt8Value(columnIndex, value); }
void PyDataRow::set_u_int8_value(const std::string& columnName, const sttp::Nullable<uint8_t>& value) { this->ref->SetUInt8Value(columnName, value); }

sttp::Nullable<uint16_t> PyDataRow::value_as_u_int16(int32_t columnIndex) { return this->ref->ValueAsUInt16(columnIndex); }
sttp::Nullable<uint16_t> PyDataRow::value_as_u_int16(const std::string& columnName) { return this->ref->ValueAsUInt16(columnName); }
void PyDataRow::set_u_int16_value(int32_t columnIndex, const sttp::Nullable<uint16_t>& value) { this->ref->SetUInt16Value(columnIndex, value); }
void PyDataRow::set_u_int16_value(const std::string& columnName, const sttp::Nullable<uint16_t>& value) { this->ref->SetUInt16Value(columnName, value); }

sttp::Nullable<uint32_t> PyDataRow::value_as_u_int32(int32_t columnIndex) { return this->ref->ValueAsUInt32(columnIndex); }
sttp::Nullable<uint32_t> PyDataRow::value_as_u_int32(const std::string& columnName) { return this->ref->ValueAsUInt32(columnName); }
void PyDataRow::set_u_int32_value(int32_t columnIndex, const sttp::Nullable<uint32_t>& value) { this->ref->SetUInt32Value(columnIndex, value); }
void PyDataRow::set_u_int32_value(const std::string& columnName, const sttp::Nullable<uint32_t>& value) { this->ref->SetUInt32Value(columnName, value); }

sttp::Nullable<uint64_t> PyDataRow::value_as_u_int64(int32_t columnIndex) { return this->ref->ValueAsUInt64(columnIndex); }
sttp::Nullable<uint64_t> PyDataRow::value_as_u_int64(const std::string& columnName) { return this->ref->ValueAsUInt64(columnName); }
void PyDataRow::set_u_int64_value(int32_t columnIndex, const sttp::Nullable<uint64_t>& value) { this->ref->SetUInt64Value(columnIndex, value); }
void PyDataRow::set_u_int64_value(const std::string& columnName, const sttp::Nullable<uint64_t>& value) { this->ref->SetUInt64Value(columnName, value); }

PyDataColumn::PyDataColumn(SharedPtr<DataColumn> column) { this->ref = column; }
// PyDataTable parent() { return PyDataTable(this->ref->Parent()); }
std::string PyDataColumn::to_string() {
    std::stringstream ss;
    ss << this->ref->Name() << " (";
    if (this->ref->Computed()) ss << "Computed ";
    switch (this->ref->Type()) {
        case DataType::String:
            ss << "String";
            break;
        case DataType::Boolean:
            ss << "Boolean";
            break;
        case DataType::DateTime:
            ss << "DateTime";
            break;
        case DataType::Single:
            ss << "Single";
            break;
        case DataType::Double:
            ss << "Double";
            break;
        case DataType::Decimal:
            ss << "Decimal";
            break;
        case DataType::Guid:
            ss << "Guid";
            break;
        case DataType::Int8:
            ss << "Int8";
            break;
        case DataType::Int16:
            ss << "Int16";
            break;
        case DataType::Int32:
            ss << "Int32";
            break;
        case DataType::Int64:
            ss << "Int64";
            break;
        case DataType::UInt8:
            ss << "UInt8";
            break;
        case DataType::UInt16:
            ss << "UInt16";
            break;
        case DataType::UInt32:
            ss << "UInt32";
            break;
        case DataType::UInt64:
            ss << "UInt6";
            break;
    };
    ss << ")";
    return ss.str();
}
const std::string& PyDataColumn::name() { return this->ref->Name(); }
DataType PyDataColumn::type() { return this->ref->Type(); }
const std::string& PyDataColumn::expression() { return this->ref->Expression(); }
bool PyDataColumn::computed() { return this->ref->Computed(); }
int32_t PyDataColumn::index() { return this->ref->Index(); }


PyDataTable::PyDataTable(SharedPtr<DataTable> table) { this->ref = table; }
std::string PyDataTable::to_string() {
    std::stringstream ss;
    ss << "[";
    for (int32_t i = 0; i < this->ref->ColumnCount(); ++i) {
        if (i > 0) ss << ", ";
        ss << PyDataColumn(this->ref->Column(i)).to_string();
    }
    ss << "] x " << this->ref->RowCount() << " rows";
    return ss.str();
}
PyDataSet PyDataTable::parent() { return PyDataSet(this->ref->Parent()); }
const std::string& PyDataTable::name() { return this->ref->Name(); }
void PyDataTable::add_column(PyDataColumn column) { this->ref->AddColumn(column.as_shared()); }
PyDataColumn PyDataTable::column(const std::string& columnName) { return PyDataColumn(this->ref->Column(columnName)); }
PyDataColumn PyDataTable::column(int32_t index) { return PyDataColumn(this->ref->Column(index)); }
PyDataColumn PyDataTable::operator[](const std::string& columnName) { return PyDataColumn((*this->ref)[columnName]); }
PyDataColumn PyDataTable::operator[](int32_t index) { return PyDataColumn((*this->ref)[index]); }
PyDataColumn PyDataTable::create_column(const std::string& name, DataType type, std::string expression) { return PyDataColumn(this->ref->CreateColumn(name, type, expression)); }
PyDataColumn PyDataTable::clone_column(const PyDataColumn& source) { return PyDataColumn(this->ref->CloneColumn(source.as_const_shared())); }
int32_t PyDataTable::column_count() { return this->ref->ColumnCount(); }
PyDataRow PyDataTable::row(int32_t index) { return PyDataRow(this->ref->Row(index)); }
void PyDataTable::add_row(PyDataRow row) { this->ref->AddRow(row.as_shared()); }
PyDataRow PyDataTable::create_row() { return PyDataRow(this->ref->CreateRow()); }
PyDataRow PyDataTable::clone_row(const PyDataRow& source) { return PyDataRow(this->ref->CloneRow(source.as_const_shared())); }
int32_t PyDataTable::row_count() { return this->ref->RowCount(); }


PyDataSet::PyDataSet() { this->ref = NewSharedPtr<DataSet>(); }
PyDataSet::PyDataSet(SharedPtr<DataSet> data_set) { this->ref = data_set; }

std::string PyDataSet::to_string() {
    std::stringstream ss;
    ss << "[";
    int i = 0;
    for (const std::string& table_name : this->ref->TableNames()) {
        if (i > 0) ss << ", ";
        ss << table_name;
        ss << " (" << (*this->ref)[table_name]->Name() << ")";
        i += 1;
    }
    ss << "]";
    return ss.str();
}
PyDataTable PyDataSet::table(const std::string& tableName) { return PyDataTable(this->ref->Table(tableName)); }
PyDataTable PyDataSet::operator[](const std::string& tableName) { return PyDataTable((*this->ref)[tableName]); }
// PyDataTable create_table(const std::string& name) { return PyDataTable(); }
int32_t PyDataSet::table_count() { return this->ref->TableCount(); }
std::vector<std::string> PyDataSet::table_names() { return this->ref->TableNames(); }
std::vector<PyDataTable> PyDataSet::tables() {
    std::vector<PyDataTable> tables;
    for (DataTablePtr table_ptr : this->ref->Tables()) {
        tables.emplace_back(table_ptr);
    }
    return tables;
}
bool PyDataSet::add_or_update_table(PyDataTable table) { return this->ref->AddOrUpdateTable(table.as_shared()); }
bool PyDataSet::remove_table(const std::string& tableName) { return this->ref->RemoveTable(tableName); }
void PyDataSet::read_xml(const std::string& fileName) { this->ref->ReadXml(fileName); }
void PyDataSet::read_xml(const std::vector<uint8_t>& buffer) { this->ref->ReadXml(buffer); }
// void PyDataSet::read_xml(const uint8_t* buffer, uint32_t length) { this->ref->ReadXml(buffer, length); }
// void PyDataSet::read_xml(const pugi::xml_document& document) { this->ref->ReadXml(document); }
void PyDataSet::write_xml(const std::string& fileName, const std::string& dataSetName) { this->ref->WriteXml(fileName, dataSetName); }
void PyDataSet::write_xml(std::vector<uint8_t>& buffer, const std::string& dataSetName) { this->ref->WriteXml(buffer, dataSetName); }
// void PyDataSet::write_xml(pugi::xml_document& document, const std::string& dataSetName) { this->ref->WriteXml(document, dataSetName); }
PyDataSet PyDataSet::from_xml(const std::string& fileName) { return PyDataSet(DataSet::FromXml(fileName)); }
PyDataSet PyDataSet::from_xml(const std::vector<uint8_t>& buffer) { return PyDataSet(DataSet::FromXml(buffer)); }
// PyDataSet from_xml(const uint8_t* buffer, uint32_t length) { return PyDataSet(DataSet::FromXml(buffer, length)); }
// PyDataSet from_xml(const pugi::xml_document& document) { return PyDataSet(DataSet::FromXml(document)); }


PyDataPublisher::PyDataPublisher() { this->ref = NewSharedPtr<DataPublisher>(); }

void PyDataPublisher::start(const uint16_t port, const bool ipV6) { this->ref->Start(port, ipV6); }
void PyDataPublisher::start(const std::string& ip, const uint16_t port) { this->ref->Start(ip, port); }
void PyDataPublisher::stop() { this->ref->Stop(); }
void PyDataPublisher::connect(const std::string& hostname, uint16_t port) { this->ref->Connect(hostname, port); }

bool PyDataPublisher::is_started() { return this->ref->IsStarted(); }

uint16_t PyDataPublisher::get_port() { return this->ref->GetPort(); }
bool PyDataPublisher::is_ipv6() { return this->ref->IsIPv6(); }

std::string PyDataPublisher::get_node_id() { return boost::uuids::to_string(this->ref->GetNodeID()); }

void PyDataPublisher::set_node_id(const std::string& value) {
    boost::uuids::string_generator gen;
    Guid guid = gen(value);
    this->ref->SetNodeID(guid);
}
