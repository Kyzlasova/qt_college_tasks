#pragma once

#include "classunit.h"

class CsharpClassUnit: public ClassUnit
{
public:
    CsharpClassUnit(const std::string& name);

    void add(std::shared_ptr<Unit> unit, Unit::Flags flags);

    std::string compile(unsigned int level = 0) const;
};
