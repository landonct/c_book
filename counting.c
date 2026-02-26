#include <stdio.h>

int main()
{
    /*Count tabs, newline, blanks*/
    // int count = 0, nc;
    // while((nc = getchar()) != EOF) {
    //     if(nc == '\n' || nc == '\t' || nc == ' ') {
    //         ++count;
    //     }
    // }
    // printf("Count: %d\n", count);
    // return 0;

    /*Copy input to output and replace all blanks with only 1*/
    // int nc;
    // int was_space = 0;
    // while ((nc = getchar()) != EOF)
    // {
    //     if (nc != ' ')
    //     {
    //         putchar(nc);
    //         if (was_space)
    //         {
    //             was_space = 0;
    //         }
    //     }
    //     else if (nc == ' ' && !was_space)
    //     {
    //         putchar(nc);
    //         was_space = 1;
    //     }
    // }

    /*Make tabs, backspace, and \ visible in output*/
    // int nc;
    // while((nc = getchar()) != EOF)
    // {
    //     if(nc == '\t') 
    //     {
    //         putchar('\\');
    //         putchar('t');
    //     } else if(nc == '\b')
    //     {
    //         putchar('\\');
    //         putchar('b');
    //     } else if(nc == '\\')
    //     {
    //         putchar('\\');
    //         putchar('\\');
    //     } else
    //     {
    //         putchar(nc);
    //     }
    // }

    /*Print input with one word on each line*/
    // int c;
    // while((c = getchar()) != EOF)
    // {
    //     if(c == ' ' || c == '\t')
    //     {
    //         putchar('\n');
    //     } else
    //     {
    //         putchar(c);
    //     }
    // }

    /*Print histogram of word lengths (horz then vertical)*/
    int bars[10] = {0}, c, nc = 0;
    while((c = getchar()) != EOF)
    {
        if(c != ' ' && c != '\n')
        {
            nc++;
        } else if(c == ' ')
        {
            if(nc >= 10)
            {
                bars[9]++;
            } else
            {
                bars[nc]++;
            }
            nc = 0;
        } else {
            if(nc >= 10)
            {
              bars[9]++;
            } else
            {
                bars[nc]++;
            }
        }
    }

    for(int i = 0; i < 10; i++)
    {
        printf("%d | ", i);
        for(int j = 0; j < bars[i]; j++)
        {
            printf("=");
        }
        if(bars[i] > 0)
            printf(" %d", bars[i]);
        printf("\n");
    }

    /*Make histogram of different frequencies of input*/

    return 0;
}
