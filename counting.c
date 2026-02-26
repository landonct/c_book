#include <stdio.h>

int main() {
    int count = 0, nc;

    /*Count tabs, newline, blanks*/
    while((nc = getchar()) != EOF) {
        if(nc == '\n' || nc == '\t' || nc == ' ') {
            ++count;
        }
    }
    printf("Count: %d\n", count);
    return 0;
    /**/
}