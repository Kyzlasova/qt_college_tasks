#pragma once

#include "unit.h"
#include <list>

class MethodUnit: public Unit
{
public:
    enum Modifier
    {
        CONST= 1,
        STATIC= 2,
        VIRTUAL= 4,
        FINAL= 8,
        ABSTRACT= 16,
        SYNCHRONIZED= 32
    };
public:
     MethodUnit(const std::string& name, const std::string& returnType, Flags flags):
        m_name(name), m_returnType(returnType), m_flags(flags) {}

    virtual void add(std::shared_ptr<Unit> unit, Flags flags = 0) = 0;

    virtual std::string compile(unsigned int level = 0) const = 0;

    virtual ~MethodUnit() {}

protected:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;
    std::list<std::shared_ptr<Unit>> m_body;
};
