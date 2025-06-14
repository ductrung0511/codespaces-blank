#include <iostream>
using namespace std;

class Aclass {
public:
    int value;
    Aclass(int v) : value(v) {}

// Prefix increment: returns reference to updated object
    Aclass& operator++() {
        value++;
        return *this;
    }
// Postfix increment: returns a copy of the object before increment
    Aclass operator++(int) {
        Aclass temp = *this;  // Copy before change
        operator++();         // Use prefix increment
        return temp;          // Return old copy
    }

    // Prefix decrement: returns reference to updated object
    Aclass& operator--() {
        value--;
        return *this;
    }

    // Postfix decrement: returns a copy of the object before decrement
    Aclass operator--(int) {
        Aclass temp = *this;
        operator--();
        return temp;
    }

    // ❌  '+' should return by value, not reference to local object
    // Binary addition: returns a new Aclass object with summed values
    Aclass operator+(const Aclass& b) const {
        return Aclass(value + b.value);  // Return by value — safe
    }
    Aclass operator-(const Aclass& b) const {
        return Aclass(value - b.value);
    }
    Aclass& operator=(const Aclass& b){
        if(this != &b){ // Using Pointer to check for selfallignment
            value = b.value;
        }
        return *this;
    }
    Aclass(const Aclass&b) {  // Copy constructor
        value = b.value;
    }

    // Getter for value (read-only)
    int getValue() const {
        return value;
    }
};

int main() {
    Aclass a(1);
    Aclass b(2);
    Aclass c(3);
    cout << (a + b - c).getValue() << endl;
    return 0;
}

