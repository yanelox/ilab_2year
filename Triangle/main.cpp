#include "triangle.hpp"
#include <stdio.h>


int main ()
{
    int n;

    double* data;
    triangle_* t;

    cin >> n;

    data = new double [9];
    t = new triangle_ [n];

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 9; ++j)
            cin >> data[j];

        t[i] = {{data[0], data[1], data[2]},
                {data[3], data[4], data[5]},
                {data[6], data[7], data[8]}};
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            if (j != i and t[i].trl_intersect (t[j]))
            {   
                cout << i + 1 << endl;
                break;
            }
        }

    delete[] data;
    delete[] t;
}