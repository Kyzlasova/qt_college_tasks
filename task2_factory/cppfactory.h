#pragma once

#include "abstractfactory.h"
#include "cppclassunit.h"
#include "cppmethodunit.h"
#include "cppprintoperatorunit.h"

class CppFactory: public AbstractFactory
{
public:
    std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name) const
    {
        return std::shared_ptr<ClassUnit>(new CppClassUnit(name));
    }

    std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name, const std::string& returnType, Unit::Flags flags) const
    {
        return std::shared_ptr<MethodUnit>(new CppMethodUnit(name, returnType, flags));
    }

    std::shared_ptr<PrintOperatorUnit> CreatePrintOperator(const std::string& text) const
    {
        return std::shared_ptr<PrintOperatorUnit>(new CppPrintOperatorUnit(text));
    }
};
