#include "javamethodunit.h"

JavaMethodUnit::JavaMethodUnit(const std::string& name, const std::string& returnType, Unit::Flags flags)
    : MethodUnit(name, returnType, flags)
{}

void JavaMethodUnit::add(std::shared_ptr<Unit> unit, Unit::Flags)
{
    m_body.push_back(unit);
}

std::string JavaMethodUnit::compile(unsigned int level) const
{
    std::string result = "";

    if(m_flags & MethodUnit::Modifier::STATIC)
    {
        result += "static ";
    }

    if (m_flags & MethodUnit::Modifier::FINAL)
    {
        result += "final ";
    }

    if(m_flags & MethodUnit::Modifier::SYNCHRONIZED)
    {
        result += "synchronized ";
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
