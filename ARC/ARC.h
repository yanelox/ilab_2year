#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

#define my_print(n)                     \
                                        \
    cout << "-\n" << #n << ": ";        \
                                        \
    for (auto i: n)                     \
        cout << i << " ";               \
                                        \
    cout << "\n-\n";        

struct ARC
{
    private:

    list <long int> T1 = {};
    list <long int> T2 = {};
    list <long int> B1 = {};
    list <long int> B2 = {};

    unsigned long c_size = 5; //max size of L1 and L2 (L1 = T1 + B1, L2 = T2 + B2)
    unsigned long p_size = 0;

    int case1   (long int n, bool inT1);
    int case2   (long int n, bool inB2);
    int case3   (long int n, bool inB2);
    int case4_1 (long int n, bool inB2);
    int case4_2 (long int n, bool inB2);

    int replace (bool inB2);

    public:

    int push (long int n);

    int print ();
};
