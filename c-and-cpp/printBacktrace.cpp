//GH_UP_CPP_5




//g++ -g $1 - -rdynamic



#include <stdio.h>
#include <stdlib.h>

/* Paste this on the file you want to debug. */
#include <stdio.h>
#include <execinfo.h>
void print_trace(void) {
    char **strings;
    size_t i, size;
    enum Constexpr { MAX_SIZE = 1024 };
    void *array[MAX_SIZE];
    size = backtrace(array, MAX_SIZE);
    strings = backtrace_symbols(array, size);
    for (i = 0; i < size; i++)
        printf("%s\n", strings[i]);
    puts("");
    free(strings);
}

void callme2()
{
    print_trace();

}

void callme()
{
    callme2();
}

int main()
{
    callme();
}
