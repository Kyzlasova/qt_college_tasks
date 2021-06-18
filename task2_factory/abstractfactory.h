#pragma once

#include "unit.h"

#include <memory>
#include <string>

class ClassUnit;
class MethodUnit;
class PrintOperatorUnit;

class AbstractFactory
{
public:
    virtual std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name) const = 0;

    virtual std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name, const std::string& returnType, Unit::Flags flags) const = 0;

    virtual std::shared_ptr<PrintOperatorUnit> CreatePrintOperator(const std::string& text) const = 0;

    virtual ~AbstractFactory() {}
};
