#pragma once

#include "unit.h"

class PrintOperatorUnit: public Unit
{
public:
    explicit PrintOperatorUnit(const std::string& text): m_text(text) {}

    virtual std::string compile(unsigned int level = 0) const = 0;

    virtual ~PrintOperatorUnit() {}

protected:
    std::string m_text;
};
