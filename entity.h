#ifndef ENTITY_H
#define ENTITY_H

#include "component.h"
#include "componentmanager.h"
#include "TypeCounter.h"
#include <array>

template<class T, size_t type_count>
class Entity
{
protected:

    // replace method to entityManager
    bool validateEntity() const
    {
        for (const auto & a : types)
        {
            // TODO: check if appropriate components exist in component manager
            //
        }

        return true;
    }

public:

    static const size_t TypeID;
    static const std::array<size_t, type_count> types;

};

template <class T, size_t type_count>
const size_t Entity<T, type_count>::TypeID = TypeCounter::get<T>();

#endif // ENTITY_H
