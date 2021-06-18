#pragma once

#include "unit.h"

#include <vector>
#include <list>

class ClassUnit: public Unit
{
public:
    enum AccessModifier
    {
        PUBLIC,
        PROTECTED,
        PRIVATE,
        INTERNAL,
        PROTECTEDINTERNAL,
        PRIVATEPROTECTED
    };
    static const std::vector<std::string> ACCESS_MODIFIERS;

public:
    explicit ClassUnit(const std::string& name): m_name(name) {}

    virtual void add(std::shared_ptr<Unit> unit, Flags flags) = 0;

    virtual std::string compile(unsigned int level = 0) const = 0;

    virtual ~ClassUnit() {}

protected:
    std::string m_name;
    using Fields = std::list<std::shared_ptr<Unit>>;
    std::vector<Fields> m_fields;
};

const std::vector<std::string> ClassUnit::ACCESS_MODIFIERS = {"public", "protected", "private", "internal", "protected internal", "private protected"};

