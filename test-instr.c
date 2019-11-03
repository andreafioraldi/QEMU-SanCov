#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc < 10) {
        if (argc == 2) {
            if (argv[1][0] == '0') printf("lol\n");
        }
    } 
}
