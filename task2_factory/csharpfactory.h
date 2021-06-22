#pragma once

#include "abstractfactory.h"
#include "csharpclassunit.h"
#include "csharpmethodunit.h"
#include "csharpprintoperatorunit.h"

class CsharpFactory: public AbstractFactory
{
public:
    std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name) const
    {
        return std::shared_ptr<ClassUnit>(new CsharpClassUnit(name));
    }

    std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name, const std::string& returnType, Unit::Flags flags) const
    {
        return std::shared_ptr<MethodUnit>(new CsharpMethodUnit(name, returnType, flags));
    }

    std::shared_ptr<PrintOperatorUnit> CreatePrintOperator(const std::string& text) const
    {
        return std::shared_ptr<PrintOperatorUnit>(new CsharpPrintOperatorUnit(text));
    }
};
