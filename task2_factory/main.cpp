#include <QCoreApplication>
#include <iostream>

#include "cppfactory.h"

namespace  {
std::string generateProgram()
{
    std::string result;
    AbstractFactory* factory;

    for (int i = 0; i < 3; i++)
    {
        switch (i)
        {
        case 0:
            factory = new CppFactory(); break;
        default:
            continue;
        }
        std::shared_ptr<ClassUnit> myClass(factory->CreateClassUnit("MyClass"));

        myClass->add(factory->CreateMethodUnit("testFunc1", "void", 0), ClassUnit::PUBLIC);

        myClass->add(factory->CreateMethodUnit("testFunc2", "void", MethodUnit::STATIC), ClassUnit::PRIVATE);

        myClass->add(factory->CreateMethodUnit("testFunc3", "void", MethodUnit::VIRTUAL | MethodUnit::CONST), ClassUnit::PUBLIC);

        std::shared_ptr<MethodUnit> method = factory->CreateMethodUnit("testFunc4", "void", MethodUnit::STATIC);

        method->add(factory->CreatePrintOperator(R"(Hello, world!\n)"));

        myClass->add(method, ClassUnit::PROTECTED);

        result += myClass->compile() + '\n';

        delete factory;
    }
    return result;
}


}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << generateProgram() << std::endl;

    return a.exec();
}
