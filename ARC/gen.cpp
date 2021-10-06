#include <iostream>

// argv[1] - how much tests you want to generate

int main (int argc, char* argv[])
{
    srand (time(NULL));

    int n = atoi (argv[1]);

    for (int i = 0; i < n; i++)
    {
        char file[50];

        sprintf (file, "test/%d.test", i + 1);

        FILE* f = fopen (file, "w");

        fprintf (f, "100\n100000\n");

        for (int j = 0; j < 100000; ++j)
            fprintf (f, "%d\n", rand() % 2000 - 1000);

        fclose (f);
    }
}