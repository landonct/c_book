#include <stdio.h>

float to_cel(float fahr);

int main() {
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

    float cel, fahr = 212;
    cel = to_cel(fahr);
    printf("%.1f\n", cel);
}

float to_cel(float fahr) {
    return 5.0 / 9.0 * (fahr - 32);
}
