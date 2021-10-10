#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <unordered_map>

namespace ARC
{
#define my_print(n)                     \
                                        \
    std::cout << "-\n" << #n << ": ";   \
                                        \
    for (auto i: n)                     \
        std::cout << i << " ";          \
                                        \
    std::cout << "\n-\n";        


enum source_list
{
    error = 0,
    T1 = 11, 
    T2 = 12,
    B1 = 21,
    B2 = 22
};

template <typename T>
struct my_iterator_
{
    private:

    using list_it = typename std::list <T>::iterator;

    public:

    list_it pointer;

    source_list source = error;
};


template <typename T> 
class Cache
{
    public:

    std::list <T> T1 = {};
    std::list <T> T2 = {};
    std::list <T> B1 = {};
    std::list <T> B2 = {};

    std::unordered_map <T, my_iterator_ <T>> map = {};

    unsigned long c_size = 5; //max size of L1 and L2 (L1 = T1 + B1, L2 = T2 + B2)
    unsigned long p_size = 0;

    int case1   (my_iterator_ <T> n, bool inT1);
    int case2   (my_iterator_ <T> n, bool inB2);
    int case3   (my_iterator_ <T> n, bool inB2);
    int case4_1 (bool inB2);
    int case4_2 (bool inB2);

    int replace (bool inB2);

    public:

    Cache (unsigned long C): c_size(C) {};

    int push (T n);

    int print ();
};
}
