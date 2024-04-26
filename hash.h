#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(!debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        unsigned long long w[5] = { 0, 0, 0, 0, 0 };
        size_t l = k.size();
        for (size_t i = 0; i<(k.size()+5)/6; i++)
        {
            unsigned long long p=1;
            for (size_t j = 0; j<6; j++)
            {
                int idx = l - 6*i - j - 1;
                if (idx < 0) break;
                w[4-i] += letterDigitToNumber(k[idx]) * p;
                p *= 36;
            }
        }
        unsigned long long h = 0;
        for (size_t i = 0; i<5; i++)
        {
            h += rValues[i] * w[i];
        }
        return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        if(letter >= 'A' && letter <= 'Z')
        {
            return letter - 'A';
        }
        else if(letter >= 'a' && letter <= 'z')
        {
            return letter - 'a';
        }
        else if(letter >= '0' && letter <= '9')
        {
            return letter - '0' + 26;
        }
        else
        {
            throw std::invalid_argument("Invalid character");
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
