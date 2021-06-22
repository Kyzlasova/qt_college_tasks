#include "cppclassunit.h"

CppClassUnit::CppClassUnit(const std::string &name)
    : ClassUnit(name)
{
    m_fields.resize(3);
}

void CppClassUnit::add(std::shared_ptr<Unit> unit, Unit::Flags flags)
{
    int accessModifier = ClassUnit::PRIVATE;
    if(flags < 3)
        accessModifier = flags;

    m_fields[accessModifier].push_back(unit);
}

std::string CppClassUnit::compile(unsigned int level) const
{
    std::string result = generateShift(level) + "class " + m_name + " {\n";
    for(size_t i = 0; i < 3; ++i)
    {
        if(m_fields[i].empty())
        {
            continue;
        }
        result += ACCESS_MODIFIERS[i] + ":\n";

        for(const auto& f: m_fields[i])
        {
            result += f->compile(level + 1);
        }
        result += "\n";
    }
    result += generateShift(level) + "};\n";
    return result;
}
