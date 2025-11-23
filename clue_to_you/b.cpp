#include <iostream>
#include <string.h>
using namespace std;
int main()
{
    // This program should fail !!!
    char *a = (char *)malloc(32);
    memset((void *)a, 0, 48);
    char *b = (char *)malloc(32);   // What if we change this line to "cout"?
    free(a);
    free(b);
}