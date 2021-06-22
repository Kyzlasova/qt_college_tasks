#pragma once

#include "classunit.h"

class JavaClassUnit: public ClassUnit
{
public:
    JavaClassUnit(const std::string& name);

    void add(std::shared_ptr<Unit> unit, Unit::Flags flags);

    std::string compile(unsigned int level = 0) const;
};
