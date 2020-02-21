#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include "component.h"
#include "TypeCounter.h"

class ComponentManager
{

    std::unordered_map< size_t, void* > m_components;

public:

    template<class T>
    void addComponent(T component)
    {
        size_t typeId = TypeCounter::get<T>();
        auto vec_iter = m_components.find(typeId);

        std::vector<T> * vec = nullptr;
        if (vec_iter == m_components.end())
        {
            vec = new std::vector<T>();
            m_components[typeId] = vec;
        }
        else
            vec = static_cast<std::vector<T>*>((*vec_iter).second);

        vec->push_back(component);
    }

    template<class T>
    std::vector<T> * getComponents()
    {
        size_t typeId = TypeCounter::get<T>();
        auto vec_iter = m_components.find(typeId);

        std::vector<T> * vec = nullptr;
        if (vec_iter == m_components.end())
        {
            vec = new std::vector<T>();
            m_components[typeId] = vec;
        }
        else
            vec = static_cast<std::vector<T>*>((*vec_iter).second);

        return vec;
    }

    template<class T>
    void printComponents()
    {
        auto vec_iter = m_components.find(TypeCounter::get<T>());

        if (vec_iter == m_components.end()) return;

        std::vector<T> * vec = static_cast<std::vector<T>*>((*vec_iter).second);

        std::cout << vec->size() << std::endl;
    }



    ComponentManager();

    ~ComponentManager();
};

#endif // COMPONENTMANAGER_H
