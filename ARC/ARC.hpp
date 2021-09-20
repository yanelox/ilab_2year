#include "ARC.h"

template <typename T>
int ARC <T>::push (T n)
{
    auto stat = map.find(n);
    
    bool inT1 = 0, inT2 = 0, inB1 = 0, inB2 = 0;

    if (stat != map.end())
        switch (stat->second.source)
        {
        case source_list::T1:
            inT1 = 1;
            break;

        case source_list::T2:
            inT2 = 1;
            break;

        case source_list::B1:
            inB1 = 1;
            break;

        case source_list::B2:
            inB2 = 1;
            break;

        default:
            break;
        }

    if (inT1 or inT2)
        case1 (stat->second, inT1);
    
    else if (inB1)
        case2 (stat->second, inB2);

    else if (inB2)
        case3 (stat->second, inB2);

    else
    {
        if (T1.size() + B1.size() == c_size)
            case4_1 (inB2);

        else if ((T1.size() + B1.size() < c_size) and 
                (T1.size() + B1.size() + T2.size() + B2.size() >= c_size))
            case4_2 (inB2);

        T1.push_front(n);
        map.insert({n, {T1.begin(), source_list::T1}});
    }

    return 0;
}

template <typename T>
int ARC <T>::case1 (my_iterator_ <T> n, bool inT1)
{
    T page = *(n.pointer);

    if (inT1)
        T1.erase(n.pointer);

    else
        T2.erase(n.pointer);

    T2.push_front(page);
    
    map[page] = {T2.begin(), source_list::T2};

    return 0;
}

template <typename T>
int ARC <T>::case2 (my_iterator_ <T> n, bool inB2)
{
    T page = *(n.pointer);

    p_size = min (c_size, p_size + max (B2.size() / B1.size(),  1ul));

    replace(inB2);

    B1.erase(n.pointer);

    T2.push_front(page);

    map[page] = {T2.begin(), source_list::T2};

    return 0;
}

template <typename T>
int ARC <T>::case3 (my_iterator_ <T> n, bool inB2)
{
    T page = *(n.pointer);

    p_size = max (0ul, p_size - max (B1.size() / B2.size(), 1ul));

    replace(inB2);

    B2.erase(n.pointer);

    T2.push_front(page);

    map[page] = {T2.begin(), source_list::T2};

    return 0;
}

template <typename T>
int ARC <T>::case4_1 (bool inB2)
{
    T page;

    if (T1.size() < c_size)
    {
        page = B1.back();

        B1.pop_back();

        replace(inB2);
    }

    else
    {
        page = T1.back();

        T1.pop_back();
    }

    map.erase(page);

    return 0;
}

template <typename T>
int ARC <T>::case4_2 (bool inB2)
{
    T page;

    if (T1.size() + B1.size() + T2.size() + B2.size() == 2 * c_size)
    {
        page = B2.back();

        B2.pop_back();

        map.erase(page);
    }

    replace(inB2);

    return 0;
}

template <typename T>
int ARC <T>::replace (bool inB2)
{
    long int swap_var = 0;

    if (T1.size() >= 1 and ((inB2 and T1.size() == p_size) or 
        T1.size() > p_size))
    {
        swap_var = T1.back();

        T1.pop_back();

        B1.push_front(swap_var);

        map[swap_var] = {B1.begin(), source_list::B1};
    }

    else
    {
        swap_var = T2.back();

        T2.pop_back();

        B2.push_front(swap_var);

        map[swap_var] = {B2.begin(), source_list::B1};
    }

    return 0;
}

template <typename T>
int ARC <T>::print ()
{
    my_print(T1);
    my_print(T2);
    my_print(B1);
    my_print(B2);

    return 0;
}