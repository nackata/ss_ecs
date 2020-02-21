#ifndef TYPECOUNTER_H
#define TYPECOUNTER_H

#include <iostream>

class TypeCounter
{
    static size_t counter;

public:

    template<class C>
    static size_t get()
    {
        static const size_t id = counter++;
        return id;
    }

    static size_t get()
    {
        return counter;
    }
};

#endif // TYPECOUNTER_H
