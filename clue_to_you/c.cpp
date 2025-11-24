#include <iostream>
using namespace std;
int main()
{
    // What is the size of cout's buffer size?
    char *a = (char *)malloc(32);
    cout << "address of a is:" << (void *)a << endl;
    char *b = (char *)malloc(32);
    cout << "address of b is:" << (void *)b << endl;
    cout << "b - a = " << (long long int)(b - a) << endl;
    free(a);
    free(b);
}