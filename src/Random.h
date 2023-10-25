
#pragma once
#include <cstdint> //uint32_t



//Xorshift128 
class Random
{

public:
    Random();
    Random(uint32_t aX, uint32_t aY, uint32_t aZ, uint32_t aW);
    ~Random();

    uint32_t operator() (); //[0 - uint32_t max]
    uint32_t operator () (uint32_t max); //[0 - max)
    uint32_t operator() (uint32_t min, uint32_t max); //[min -> max]

    uint32_t Next();
    uint32_t Next(uint32_t max);
    uint32_t Next(uint32_t min, uint32_t max);




private:
    uint32_t x = 123456789;
    uint32_t y = 362436069;
    uint32_t z = 521288629;
    uint32_t w = 88675123;

};