#include "printoperatorunit.h"

class CppPrintOperatorUnit: public PrintOperatorUnit
{
public:
    explicit CppPrintOperatorUnit(const std::string& text): PrintOperatorUnit(text) {}

    std::string compile(unsigned int level = 0) const
    {
        return generateShift(level) + "printf( \"" + m_text + "\" );\n";
    }
};
