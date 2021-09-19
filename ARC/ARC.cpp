#include "ARC.h"

int ARC::push (long int n)
{
    auto res1 = find (T1.begin(), T1.end(), n);
    auto res2 = find (T2.begin(), T2.end(), n);
    auto res3 = find (B1.begin(), B1.end(), n);
    auto res4 = find (B2.begin(), B2.end(), n);

    bool inT1 = (res1 != T1.end());
    bool inT2 = (res2 != T2.end());
    bool inB1 = (res3 != B1.end());
    bool inB2 = (res4 != B2.end());

    if (inT1 or inT2)
        case1 (n, inT1);
    
    else if (inB1)
        case2 (n, inB2);

    else if (inB2)
        case3 (n, inB2);

    else
    {
        if (T1.size() + B1.size() == c_size)
            case4_1 (n, inB2);

        else if ((T1.size() + B1.size() < c_size) and 
                (T1.size() + B1.size() + T2.size() + B2.size() >= c_size))
            case4_2 (n, inB2);

        T1.push_front(n);
    }

    return 0;
}

int ARC::case1 (long int n, bool inT1)
{
    if (inT1)
        T1.remove(n);

    else
        T2.remove(n);

    T2.push_front(n);

    return 0;
}

int ARC::case2 (long int n, bool inB2)
{
    p_size = min (c_size, p_size + max (B2.size() / B1.size(),  1ul));

    replace(inB2);

    B1.remove(n);

    T2.push_front(n);

    return 0;
}

int ARC::case3 (long int n, bool inB2)
{
    p_size = max (0ul, p_size - max (B1.size() / B2.size(), 1ul));

    replace(inB2);

    B2.remove(n);

    T2.push_front(n);

    return 0;
}

int ARC::case4_1 (long int n, bool inB2)
{
    if (T1.size() < c_size)
    {
        B1.pop_back();  

        replace(inB2);
    }

    else
        T1.pop_back();

    return 0;
}

int ARC::case4_2 (long int n, bool inB2)
{
    if (T1.size() + B1.size() + T2.size() + B2.size() == 2 * c_size)
        B2.pop_back();

    replace(inB2);

    return 0;
}

int ARC::replace (bool inB2)
{
    long int swap_var = 0;

    if (T1.size() >= 1 and ((inB2 and T1.size() == p_size) or 
        T1.size() > p_size))
    {
        swap_var = T1.back();

        T1.pop_back();

        B1.push_front(swap_var);
    }

    else
    {
        swap_var = T2.back();

        T2.pop_back();

        B2.push_front(swap_var);
    }

    return 0;
}

int ARC::print ()
{
    my_print(T1);
    my_print(T2);
    my_print(B1);
    my_print(B2);

    return 0;
}