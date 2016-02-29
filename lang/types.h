#include <boost/variant.hpp>
#include <cassert>
#include <iostream>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

class TypeInstance;
typedef boost::variant< int32_t, uint32_t, float, double, std::string > ValueType;

class Type;
class TypeInstance
{
    std::string name_;
    std::unordered_map<std::string, ValueType> fields_;
public:
    TypeInstance(const std::string& name);
    
    ~TypeInstance() = default;
    TypeInstance(const TypeInstance&) = default;
    TypeInstance& operator=(const TypeInstance& rhs) = default;

    bool operator==(const TypeInstance& rhs);
    ValueType get_field(const std::string& name) const;
    ValueType& get_field(const std::string& name);
    void debug(void) const;

private:
    void add_field(const std::string& string, ValueType type);
    
    friend class Type;
};

class Type
{
public:
    Type(const std::string& name);
    
    typedef std::shared_ptr<TypeInstance> InstancePtr;
    
    struct FieldInfo
    {
        FieldInfo(std::string n, ValueType d)
            : name(n)
            , default_value(d)
            {}
            
        std::string name;
        ValueType default_value;
    };

    void add_field(const FieldInfo& info);
    Type::InstancePtr create_instance();
    
private:
    std::string name_;
    std::vector<FieldInfo> fields_;
};
