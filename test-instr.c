#include <stdio.h>

void win(void)
{
    printf("win\n");
}

void lose(void)
{
    return;
}

int main(int argc, char** argv)
{
    if (argc < 10) {
        if (argc == 2) {
            void (*fn)(void);
            if (argv[1][0] == '0') fn = win;
            else fn = lose;
            fn();
        }
    } 
}
