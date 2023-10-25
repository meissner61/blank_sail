
#include <random>
#include "Random.h"

Random::Random()
{
    std::random_device rd;
    x = rd();
    y = 362436069;
    z = 521288629;
    w = 88575123;
}

Random::Random(uint32_t aX, uint32_t aY, uint32_t aZ, uint32_t aW)
    : x(aX)
    , y(aY)
    , z(aZ)
    , w(aW)
{

}

Random::~Random()
{

}

uint32_t Random::operator() ()
{
    return Next();
}

uint32_t Random::operator() (uint32_t max)
{
    return Next(max);
}

uint32_t Random::operator() (uint32_t min, uint32_t max)
{
    return Next(min, max);
}

uint32_t Random::Next()
{
    uint32_t t;
    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;

    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

uint32_t Random::Next(uint32_t max)
{
    return Next() % max;
}

uint32_t Random::Next(uint32_t min, uint32_t max)
{
    return min + Next() % (max - min + 1);
}