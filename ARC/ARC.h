#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <unordered_map>

using namespace std;

#define my_print(n)                     \
                                        \
    cout << "-\n" << #n << ": ";        \
                                        \
    for (auto i: n)                     \
        cout << i << " ";               \
                                        \
    cout << "\n-\n";        

template <typename T> 
class ARC
{
    private:

    list <T> T1 = {};
    list <T> T2 = {};
    list <T> B1 = {};
    list <T> B2 = {};

    using list_it = typename list <T>::iterator;
    unordered_map <T, list_it> map = {};

    unsigned long c_size = 5; //max size of L1 and L2 (L1 = T1 + B1, L2 = T2 + B2)
    unsigned long p_size = 0;

    int case1   (T n, bool inT1);
    int case2   (T n, bool inB2);
    int case3   (T n, bool inB2);
    int case4_1 (T n, bool inB2);
    int case4_2 (T n, bool inB2);

    int replace (bool inB2);

    public:

    int push (T n);

    int print ();
};
