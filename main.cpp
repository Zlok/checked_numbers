#include <iostream>
#include "checked_numbers.h"

using namespace std;

int main() {
    checked<unsigned> a(5), b(3);
    b = b - a;
    b.write();
    cout << endl;
    return 0;
}