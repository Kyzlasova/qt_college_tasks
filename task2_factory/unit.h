#pragma once

#include <memory>
#include <stdexcept>
#include <string>

class Unit
{
public:
    using Flags = unsigned int;
public:
    virtual ~Unit() = default;

    virtual void add(std::shared_ptr<Unit>, Flags = 0)
    {
        throw std::runtime_error("Not supported");
    }

    virtual std::string compile(unsigned int level = 0) const = 0;

protected:
    virtual std::string generateShift(unsigned level = 0) const
    {
        static const char DEFAULT_SHIFT = '\t';
        std::string result;
        for(unsigned i = 0; i < level; ++i)
            result += DEFAULT_SHIFT;
        return result;
    }
};
