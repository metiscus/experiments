#include "types.h"

TypeInstance::TypeInstance(const std::string& name)
    : name_(name)
{

}

bool TypeInstance::operator==(const TypeInstance& rhs)
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

void TypeInstance::add_field(const std::string& string, ValueType type)
{
    assert(fields_.count(string) == 0);
    fields_.insert(std::make_pair(string, type));
}

ValueType TypeInstance::get_field(const std::string& name) const
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

ValueType& TypeInstance::get_field(const std::string& name)
{
    assert(fields_.count(name) != 0);
    return fields_[name];
}

void TypeInstance::debug(void) const
{
    std::cout<<"Type: "<<name_<<"\n";
    std::cout<<"Instance: "<<this<<"\n";
    std::cout<<"Members: "<<"\n";
    for(auto itr : fields_)
    {
        std::cout<<"\t"<<itr.first<<" : "<<itr.second<<"\n";
    }
}

Type::Type(const std::string& name)
    : name_(name)
{
}

void Type::add_field(const FieldInfo& info)
{
    fields_.push_back(info);
}

Type::InstancePtr Type::create_instance()
{
    Type::InstancePtr ptr = std::make_shared<TypeInstance>(name_);
    for(auto field : fields_)
    {
        ptr->add_field(field.name, field.default_value);
    }
    return ptr;
}
