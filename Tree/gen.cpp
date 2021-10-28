#include <algorithm>
#include <iterator>
#include <set>
#include <cstdlib>
#include <cstdio>
#include <time.h>
#include <iostream>

int main ()
{
    srand (time (NULL));

    for (int k = 1; k <= 10; ++k)
    {   
        int file_number = k;
        int tmp = 0;

        char file1[100], file2[100];
        
        file1[0] = '\0';
        file2[0] = '\0';

        sprintf (file1, "tests/%d.test", file_number);
        sprintf (file2, "answ/%d.answ", file_number);

        FILE* f1 = fopen (file1, "w");
        FILE* f2 = fopen (file2, "w");

        size_t size = 1000;
        std::set <int> n;

        for (; n.size() < size;)
        {
            tmp = rand () % (3 * size) - 3 * size / 2;

            n.insert(tmp);
        }

        for (size_t i = 0; i < size;)
        {
            auto iter = n.begin();

            tmp = rand() % 3;

            if (tmp == 0)
            {
                std::advance (iter, i);

                fprintf (f1, "k %d ", *iter);
                ++i;

                iter = n.begin();
            }
            
            else if (tmp == 1 and i != 0)
            {
                int tmp1 = rand () % i;

                std::advance (iter, tmp1);

                fprintf (f1, "m %d ", tmp1 + 1);

                fprintf (f2, "%d ", *iter);

                iter = n.begin();
            }

            else if (tmp == 2)
            {
                int tmp1 = rand () % 200 - 100;

                int k = 0;

                while (k < i and *iter < tmp1)
                {
                    ++iter;
                    ++k;
                }

                fprintf (f1, "n %d ", tmp1);
                fprintf (f2, "%d ", k);

                iter = n.begin();
            }
        }

        fprintf (f1, "\n");
        fprintf (f2, "\n");

        fclose (f1);
        fclose (f2);
    }
}