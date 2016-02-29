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
    TypeInstance(const std::string& name)
        : name_(name)
    {

    }
    
    ~TypeInstance() = default;
    TypeInstance(const TypeInstance&) = default;
    TypeInstance& operator=(const TypeInstance& rhs) = default;

    bool operator==(const TypeInstance& rhs)
    {
        // not same type
        if(name_ != rhs.name_) return false;
        for(auto itr : rhs.fields_)
        {
            auto field = fields_.find(itr.first);
            if(field == fields_.end()) return false;
            if(field->second != itr.second) return false;
        }
        return true;
    }

    void add_field(const std::string& string, ValueType type)
    {
        assert(fields_.count(string) == 0);
        fields_.insert(std::make_pair(string, type));
    }
    
    ValueType get_field(const std::string& name) const
    {
        auto itr = fields_.find(name);
        if(itr == fields_.end())
        {
            return ValueType("");
        }
        else
        {
            return itr->second;
        }
    }
    
    ValueType& get_field(const std::string& name)
    {
        assert(fields_.count(name) != 0);
        return fields_[name];
    }
    
    void debug(void) const
    {
        std::cout<<"Type: "<<name_<<"\n";
        std::cout<<"Instance: "<<this<<"\n";
        std::cout<<"Members: "<<"\n";
        for(auto itr : fields_)
        {
            std::cout<<"\t"<<itr.first<<" : "<<itr.second<<"\n";
        }
    }
};

class Type
{
public:
    Type(const std::string& name)
        : name_(name)
    {
    }
    
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

    void add_field(const FieldInfo& info)
    {
        fields_.push_back(info);
    }
    
    Type::InstancePtr create_instance()
    {
        Type::InstancePtr ptr = std::make_shared<TypeInstance>(name_);
        for(auto field : fields_)
        {
            ptr->add_field(field.name, field.default_value);
        }
        return ptr;
    }
    
private:
    std::string name_;
    std::vector<FieldInfo> fields_;
};
