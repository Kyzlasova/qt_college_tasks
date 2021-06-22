#pragma once

#include "methodunit.h"

class CppMethodUnit: public MethodUnit
{
public:
    explicit CppMethodUnit(const std::string& name, const std::string& returnType, Flags flags);

    void add(std::shared_ptr<Unit> unit, Flags = 0);

    std::string compile(unsigned int level = 0) const;
};

