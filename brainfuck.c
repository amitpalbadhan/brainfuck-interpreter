// A brainfuck interpreter in C
// https://github.com/amitpalbadhan

#include <stdio.h>
#include <stdlib.h>


#define INPUT_SZ  (1 << 22)
char _i[INPUT_SZ];
int jump[INPUT_SZ];
int _i0;


char data[60000];
int dp = 30000;


int loop_stack[30000];
int loop_ptr = 0;


int main(int argc, char *argv[]) {
    FILE *fp;
    if ( argc == 1) fp = fopen("fibonacci.bf", "r");
    else fp = fopen(argv[1], "r");
    fread(_i, 1, INPUT_SZ, fp);
    fclose(fp);

    char c;
    
    while(c = _i[_i0]) {
        switch (c) {
        case '[':
            loop_stack[loop_ptr++] = _i0;
            break;
        case ']':
            jump[_i0] = loop_stack[--loop_ptr];
            jump[jump[_i0]] = _i0;
            break;
        }
        ++_i0;
    }

    _i0 = 0;

    while(c = _i[_i0]) {
        switch (c) {
        case '>':
            ++dp;
            break;
        case '<':
            --dp;
            break;
        case '+':
            ++data[dp];
            break;
        case '-':
            --data[dp];
            break;
        case ',':
            data[dp] = getchar();
            break;
        case '.':
            putchar(data[dp]);
            break;
        case '[':
            if (!data[dp]) _i0 = jump[_i0] - 1;
            break;
        case ']':
            if (data[dp])
                _i0 = jump[_i0] - 1;
            break;
        }
        ++_i0;
    }
    
    putchar('\n');

    return 0;
}
