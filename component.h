#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include "TypeCounter.h"

template <class T>
class Component
{
public:

    static const size_t TypeID;
    const size_t objectID;


    Component(size_t id) : objectID(id) {}

    Component() = delete;

    operator int() const = delete;
};

template <class T>
const size_t Component<T>::TypeID = TypeCounter::get<T>();

#endif // COMPONENT_H
