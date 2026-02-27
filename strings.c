#include <stdio.h>
#define MAXLINE 1000
#define PRINTABLE 0

int get_line(char s[]);
void copy(char to[], char from[]);
void reverse(char out[], char in[]);

int main() {
    char line[MAXLINE], longest[MAXLINE];
    int len, max = 0;

    while((len = get_line(line)) > 0) {
        if(len > max) {
            max = len;
            reverse(longest, line);
        }
    }

    if(max > 0 && max > PRINTABLE) {
        printf("%d", max);
        printf("%s\n", longest);
    }

    return 0;
}

void copy(char to[], char from[]) {
    int i = 0;
    while(from[i] != '\0' && i < MAXLINE - 1) {
        to[i] = from[i];
        i++;
    }
    to[i] = '\0';
}

int get_line(char s[]) {
    int c;
    int i, k = 0;
    for(i = 0; (c = getchar()) != EOF && c != '\n'; i++) {
        if(k < MAXLINE - 1) {
            s[i] = c;
            k++;
        }
    }
    if(c == '\n' && i < MAXLINE - 1) {
        s[i] = c;
        i++;
        k++;
    }
    s[k] = '\0';

    return i;
}

void reverse(char out[], char in[]) {
    int len_in = 0;

    while(in[len_in] != '\0')
        len_in++;

    for(int i = 0; i < len_in; i++) {
        out[i] = in[len_in - i - 1];
    }
    out[len_in] = '\0';
}
