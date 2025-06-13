#include <iostream>
using namespace std;

int add(int a, int b) { cout << "wtf"; return a + b; }
float add(float a, float b) { return 1.0 + a + b; }

int main() {
    cout << add(1, (float)1.0) << endl;  // Calls float version
    return 0;
}
