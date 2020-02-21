#include <iostream>
#include <vector>
#include "component.h"
#include "entity.h"
#include "componentmanager.h"
#include <chrono>
#include <random>
#include <thread>

namespace MyRandom
{
    // Initialize our mersenne twister with a random seed based on the clock (once at system startup)
    std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
}

int getRandomNumber(int min, int max)
{
    std::uniform_int_distribution die{ min, max }; // we can create a distribution in any function that needs it
    return die(MyRandom::mersenne); // and then generate a random number from our global generator
}

float getRandomRealNumber(float min, float max)
{
    std::uniform_real_distribution die{ min, max }; // we can create a distribution in any function that needs it
    return die(MyRandom::mersenne); // and then generate a random number from our global generator
}

class Timer
{
private:
    // Type aliases to make accessing nested type easier
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer() : m_beg(clock_t::now())
    {
    }

    void reset()
    {
        m_beg = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};

class IntComponent : public Component<IntComponent>
{
public:
    int a;
    int b;
    int c;
    int d;

    IntComponent(size_t TypeID) : Component(TypeID) {}
};

class FloatComponent : public Component<FloatComponent>
{
public:
    float x;
    float y;
    float z;
    float w;

    FloatComponent(size_t TypeID) : Component(TypeID) {}
};

class VersComponent : public Component<VersComponent>
{
public:

    double max;
    int res;
    bool boo;
    bool boo1;


    VersComponent(size_t TypeID) : Component(TypeID) {}
};

class ExeEntity : public Entity<ExeEntity, 3>
{
public:

    ComponentManager & m_man;

    ExeEntity(ComponentManager & man) : m_man(man)
    {
        IntComponent c(TypeID);
        FloatComponent f(TypeID);
        VersComponent v(TypeID);

        c.a = getRandomNumber(1, 101);
        c.b = getRandomNumber(1, 103);
        c.c = getRandomNumber(1, 102);
        c.d = getRandomNumber(1, 100);

        f.x = getRandomRealNumber(1.f, 100.f);
        f.y = getRandomRealNumber(1.f, 100.f);
        f.z = getRandomRealNumber(1.f, 100.f);
        f.w = getRandomRealNumber(1.f, 100.f);

        v.boo = getRandomNumber(0, 1);
        v.max = getRandomRealNumber(0.f, 100.f);
        v.res = getRandomNumber(0, 100);
        v.boo1 = getRandomNumber(0, 1);

        m_man.addComponent(c);
        m_man.addComponent(f);
        m_man.addComponent(v);
    }
};

template <>
const std::array<size_t, 3> Entity<ExeEntity, 3>::types = {
    TypeCounter::get<VersComponent>(),
    TypeCounter::get<IntComponent>(),
    TypeCounter::get<FloatComponent>()
};

void intSystem(IntComponent & a)
{
    int res = a.a + a.b + a.c + a.d;
    a.a = res;
    a.b = res * 2;
    a.c = res / 4;
}

void intSystem(ComponentManager & man)
{
    for (auto & a : man.range<IntComponent>())
    {
        intSystem(a);
    }
}

void floatSystem(FloatComponent & a)
{
    float len = sqrt(a.w + a.x + a.y + a.z);
    a.w /= len;
    a.x /= len;
    a.y /= len;
    a.z /= len;
}

void floatSystem(ComponentManager & man)
{
    for (auto & a : man.range<FloatComponent>())
    {
        floatSystem(a);
    }
}

void versSystem(VersComponent & a)
{
    if (a.boo && a.boo1)
    {
        a.max = static_cast<double>(a.res * 2);
    }
    else if (a.boo)
    {
        a.max = a.res;
    }
    else if (a.boo1)
    {
        a.res = static_cast<int>(a.max);
    }
    else
    {
        a.res++;
        a.max += 10.;
    }
}

void versSystem(ComponentManager & man)
{
    for (auto & a : man.range<VersComponent>())
    {
        versSystem(a);
    }
}

class RobustObj
{
public:

    int a;
    int b;
    int c;
    int d;
    std::array<double, 20> ar{0};
    float x;
    float y;
    float z;
    float w;
    bool boo;
    bool boo1;
    int res;
    double max;

    RobustObj()
    {
        a = getRandomNumber(1, 101);
        b = getRandomNumber(1, 103);
        c = getRandomNumber(1, 102);
        d = getRandomNumber(1, 100);

        x = getRandomRealNumber(1.f, 100.f);
        y = getRandomRealNumber(1.f, 100.f);
        z = getRandomRealNumber(1.f, 100.f);
        w = getRandomRealNumber(1.f, 100.f);

        boo = getRandomNumber(0, 1);
        max = getRandomRealNumber(0.f, 100.f);
        res = getRandomNumber(0, 100);
        boo1 = getRandomNumber(0, 1);
    }
};

void robObSystem(std::vector<RobustObj> & vec)
{
    for (auto & a : vec)
    {
        int res = a.a + a.b + a.c + a.d;
        a.a = res;
        a.b = res * 2;
        a.c = res / 4;
    }
    for (auto & a : vec)
    {
        float len = a.w + a.x + a.y + a.z;
        a.w /= len;
        a.x /= len;
        a.y /= len;
        a.z /= len;

    }
    for (auto & a : vec)
    {
        if (a.boo && a.boo1)
        {
            a.max = static_cast<double>(a.res * 2);
        }
        else if (a.boo)
        {
            a.max = a.res;
        }
        else if (a.boo1)
        {
            a.res = static_cast<int>(a.max);
        }
        else
        {
            a.res++;
            a.max += 10.;
        }
    }
}

void robint(std::vector<RobustObj> & vec)
{
    for (auto & a : vec)
    {
        int res = a.a + a.b + a.c + a.d;
        a.a = res;
        a.b = res * 2;
        a.c = res / 4;
    }
}

void robfloat(std::vector<RobustObj> & vec)
{
    for (auto & a : vec)
    {
        float len = sqrt(a.w + a.x + a.y + a.z);
        a.w /= len;
        a.x /= len;
        a.y /= len;
        a.z /= len;
    }
}

void robfloat(std::vector<RobustObj*> & vec)
{
    for (auto & a : vec)
    {
        float len = sqrt(a->w + a->x + a->y + a->z);
        a->w /= len;
        a->x /= len;
        a->y /= len;
        a->z /= len;
    }
}

void robvers(std::vector<RobustObj> & vec)
{
    for (auto & a : vec)
    {
        if (a.boo && a.boo1)
        {
            a.max = static_cast<double>(a.res * 2);
        }
        else if (a.boo)
        {
            a.max = a.res;
        }
        else if (a.boo1)
        {
            a.res = static_cast<int>(a.max);
        }
        else
        {
            a.res++;
            a.max += 10.;
        }
    }
}

void lol() {std::cout << "lolol" << std::endl;}

int main()
{
    ComponentManager man;
    std::vector<RobustObj> vec;
    int count = 3000;
    long updCount = 5000;

    Timer timer;

    for (int i = 0; i < count; ++i)
    {
        ExeEntity e(man);
    }

    std::cout << "component init :" << timer.elapsed() << std::endl;

    timer.reset();

    for (long i = 0; i < count; ++i)
    {
        vec.emplace_back();
    }

    std::cout << "robust init :" << timer.elapsed() << std::endl;

    timer.reset();

    for (long i = 0; i < updCount; ++i)
    {
        intSystem(man);
        floatSystem(man);
        versSystem(man);
    }


    std::cout << "component update :" << timer.elapsed() << std::endl;

    timer.reset();

    for (long i = 0; i < updCount; ++i)
    {
        robint(vec);
        robfloat(vec);
        robvers(vec);
    }

    std::cout << "robust object update :" << timer.elapsed() << std::endl;


    int a;
    std::cin >> a;

    std::cout << vec.at(a).w << std::endl;

    return 0;
}
