#pragma once

#include "abstractfactory.h"
#include "javaclassunit.h"
#include "javamethodunit.h"
#include "javaprintoperatorunit.h"

class JavaFactory: public AbstractFactory
{
public:
    std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name) const
    {
        return std::shared_ptr<ClassUnit>(new JavaClassUnit(name));
    }

    std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name, const std::string& returnType, Unit::Flags flags) const
    {
        return std::shared_ptr<MethodUnit>(new JavaMethodUnit(name, returnType, flags));
    }

    std::shared_ptr<PrintOperatorUnit> CreatePrintOperator(const std::string& text) const
    {
        return std::shared_ptr<PrintOperatorUnit>(new JavaPrintOperatorUnit(text));
    }
};
