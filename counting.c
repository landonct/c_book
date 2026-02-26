#include <stdio.h>

int main()
{
    // int count = 0, nc;

    // /*Count tabs, newline, blanks*/
    // while((nc = getchar()) != EOF) {
    //     if(nc == '\n' || nc == '\t' || nc == ' ') {
    //         ++count;
    //     }
    // }
    // printf("Count: %d\n", count);
    // return 0;

    /*Copy input to output and replace all blanks with only 1*/
    int nc;
    int was_space = 0;
    while ((nc = getchar()) != EOF)
    {
        if (nc != ' ')
        {
            putchar(nc);
            if (was_space)
            {
                was_space = 0;
            }
        }
        else if (nc == ' ' && !was_space)
        {
            putchar(nc);
            was_space = 1;
        }
    }
}