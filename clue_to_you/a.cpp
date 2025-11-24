#include <iostream>
using namespace std;
int main()
{
    // What is the size of meta-data?
    char *a = (char *)malloc(32);
    char *b = (char *)malloc(32);
    cout << "b - a = " << (long long int)(b - a) << endl;
    free(a);
    free(b);
}