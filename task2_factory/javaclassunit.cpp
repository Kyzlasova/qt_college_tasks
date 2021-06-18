#include "javaclassunit.h"

JavaClassUnit::JavaClassUnit(const std::string &name): ClassUnit(name)
{
    m_fields.resize(3);
}

void JavaClassUnit::add(std::shared_ptr<Unit> unit, Unit::Flags flags)
{
    int accessModifier = ClassUnit::PUBLIC;

    if(flags < 3)
    {
        accessModifier = flags;
    }
    m_fields[accessModifier].push_back(unit);
}

std::string JavaClassUnit::compile(unsigned int level) const
{
    std::string result = generateShift(level) + "private class " + m_name + " {\n";
    for(size_t i = 0; i < m_fields.size(); ++i)
    {
        if(m_fields[i].empty())
        {
            continue;
        }
        for(const auto& f: m_fields[i])
        {
            result += generateShift(level + 1) + ClassUnit::ACCESS_MODIFIERS[i] + ' ' + f->compile(level + 1);
        }
        result += "\n";
    }
    result += generateShift(level) + "};\n";
    return result;
}
