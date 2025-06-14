#include <iostream>
#include <string>

using namespace std;



class Rational {
private:
    int numerator;
    int denominator;

public:
    // Constructor with two parameters (reduces fraction)
    Rational(int a, int b) {
        if (b > 0) {  // Ensure denominator > 0
            int divider = gcd(a, b);
            if (divider != 1) {  // Reduce fraction if gcd > 1
                numerator = a / divider;
                denominator = b / divider;
            } else {
                numerator = a;
                denominator = b;
            }
        } else {
            cout << "Wrong input for denominator (>0)" << endl;
            numerator = a;
            denominator = 1;
        }
    }

    Rational(){
        denominator=1;
        numerator = 1;
    }
    Rational(int a){
        denominator = 1;
        numerator = a;
    }
    
    // Getter methods
    int getNumerator() { return numerator; }
    int getDenominator() { return denominator; }
    static int gcd(int a, int b) {
        while (b != a) {
            if (a > b) {
                a = a - b;
            } else {
                b = b - a;
            }
        }
        return a;
    }
};

int main(){
    Rational num(12,20); 
    cout << num.getNumerator() << "/" << num.getDenominator();
}