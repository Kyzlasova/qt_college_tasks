#pragma once

#include "printoperatorunit.h"

class CsharpPrintOperatorUnit: public PrintOperatorUnit
{
public:
    explicit CsharpPrintOperatorUnit(const std::string& text): PrintOperatorUnit(text) {}

    std::string compile(unsigned int level = 0) const
    {
        return generateShift(level) + "System.Console.WriteLine( \"" + m_text + "\" );\n";
    }
};
