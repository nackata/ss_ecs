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
    using vector_type = std::vector<T>;
    template<class T>
    using iterator = typename vector_type<T>::iterator;
    template<class T>
    using const_iterator = typename vector_type<T>::const_iterator;

    template<class T>
    class Iter_range
    {
    public:
        ComponentManager & man;

        iterator<T> begin() noexcept {return man.begin<T>();}
        iterator<T> end() noexcept {return man.end<T>();}
        const_iterator<T> cbegin() const noexcept {return man.cbegin<T>();}
        const_iterator<T> cend() const noexcept {return man.cend<T>();}
    };


    // use for range based for    for (auto & a : manager.range<T>()) {}
    template<class T>
    Iter_range<T> range() noexcept { return Iter_range<T>{*this}; }


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
    iterator<T> begin() noexcept
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

        return vec->begin();
    }

    template<class T>
    iterator<T> end() noexcept
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

        return vec->end();
    }

    template<class T>
    const_iterator<T> cbegin() const noexcept
    {
        size_t typeId = TypeCounter::get<T>();
        auto vec_iter = m_components.find(typeId);

        std::vector<T> * vec = nullptr;
        if (vec_iter == m_components.end())
        {
            return nullptr;
        }
        else
            vec = static_cast<std::vector<T>*>((*vec_iter).second);

        return vec->cbegin();
    }

    template<class T>
    const_iterator<T> cend() const noexcept
    {
        size_t typeId = TypeCounter::get<T>();
        auto vec_iter = m_components.find(typeId);

        std::vector<T> * vec = nullptr;
        if (vec_iter == m_components.end())
        {
            return nullptr;
        }
        else
            vec = static_cast<std::vector<T>*>((*vec_iter).second);

        return vec->cend();
    }

    // deprecated : do not use if you want to be compatible with future updates
    // use generic iterators
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
