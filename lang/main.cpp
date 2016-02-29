#include "types.h"
#include <cstdio>
#include <string>

#if 0
[type:Human]
    [field:name:string:""]
    [field:age:int:0]
    
[human]
    [name:"steve"]
    [age:10]
#endif

int main(int argc, char** argv)
{
    Type human("human");
    human.add_field(Type::FieldInfo("name", ""));
    human.add_field(Type::FieldInfo("age", 0U));
    
    Type::InstancePtr steve = human.create_instance();
    steve->get_field("name") = "steve";
    steve->get_field("age") = 56U;
    steve->debug();
}
