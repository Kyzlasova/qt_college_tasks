#include "csharpmethodunit.h"

CsharpMethodUnit::CsharpMethodUnit(const std::string &name, const std::string &returnType, Unit::Flags flags)
    : MethodUnit(name, returnType, flags)
{}

void CsharpMethodUnit::add(std::shared_ptr<Unit> unit, Unit::Flags)
{
    m_body.push_back(unit);
}

std::string CsharpMethodUnit::compile(unsigned int level) const
{
    std::string result = "";

    if(m_flags & MethodUnit::Modifier::STATIC)
    {
        result += "static ";
    }

    if( m_flags & MethodUnit::Modifier::VIRTUAL)
    {
        result += "virtual ";
    }

    if(m_flags & MethodUnit::Modifier::ABSTRACT)
    {
        result += "abstract ";
    }


    result += m_returnType + " ";
    result += m_name + "()";

    result += " {\n";
    for(const auto& b: m_body) {
        result += b->compile(level + 1);
    }
    result += generateShift(level) + "}\n";

    return result;
}
