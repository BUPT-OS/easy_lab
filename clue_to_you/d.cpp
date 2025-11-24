#include <iostream>
using namespace std;
int main()
{
    // Can the buffer of cout be reused among multiple cout calls?
    char *a = (char *)malloc(32);
    cout << "address of a is:" << (void *)a << endl;
    char *b = (char *)malloc(32);
    cout << "address of b is:" << (void *)b << endl;
    char *c = (char *)malloc(32);
    cout << "address of c is:" << (void *)c << endl;
    cout << "b - a = " << (long long int)(b - a) << endl;
    cout << "c - b = " << (long long int)(c - b) << endl;
    free(a);
    free(b);
    free(c);
}