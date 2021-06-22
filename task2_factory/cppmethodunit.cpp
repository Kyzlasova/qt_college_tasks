#include "cppmethodunit.h"

CppMethodUnit::CppMethodUnit(const std::string &name, const std::string &returnType, Unit::Flags flags)
    : MethodUnit(name, returnType, flags)
{}

void CppMethodUnit::add(std::shared_ptr<Unit> unit, Unit::Flags)
{
    m_body.push_back(unit);
}

std::string CppMethodUnit::compile(unsigned int level) const
{
    std::string result = generateShift(level);

    if(m_flags & MethodUnit::Modifier::STATIC)
    {
        result += "static ";
    }
    else if(m_flags & MethodUnit::Modifier::VIRTUAL)
    {
        result += "virtual ";
    }
    result += m_returnType + " ";
    result += m_name + "()";
    if(m_flags & MethodUnit::Modifier::CONST)
    {
        result += " const";
    }

    result += " {\n";
    for(const auto& b: m_body) {
        result += b->compile(level + 1);
    }
    result += generateShift(level) + "}\n";

    return result;
}
