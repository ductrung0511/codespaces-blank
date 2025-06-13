#include <iostream>
using namespace std;
#include<cmath>

class Complex {
private:
    double real;
    double imag;
public:
    Complex(): real(0), imag(0){}
    Complex(double r, double i): real(r), imag(i){}
    double modulus() const { // Mark all member functions const if they don't modify the object.
        return sqrt(pow(real,2) + pow(imag,2));
    }
    bool operator>(const Complex& c){
        return this->modulus() > c.modulus();
    }
    Complex& operator=(const Complex& c){
        real = c.real;
        imag = c.imag;
        return *this;
    }
};

int main(){
    cout << "------------------------" << endl;
    cout << "Complex number example" << endl;
    Complex c1(3, 4); // 5
    Complex c2(1, 1); // sqrt(2)
    if(c1 > c2){
        cout << "c1 is greater than c2" << endl;
    }
    else{
        cout << "c1 is not greater than c2" << endl;
    }

    Complex c3 = c1; // Assignment operator
    cout << "c3.modulus(): " << c3.modulus() << endl; // Should print 5
    cout << "------------------------" << endl;
    cout << "Reading complex numbers" << endl;
    double reals[10] ={
        1.0, 2.0, 3.0, 4.0, 5.0,
        6.0, 7.0, 8.0, 9.0, 10.0
    };
    double imags[10] ={
        1.0, 2.0, 3.0, 4.0, 5.0,
        6.0, 7.0, 8.0, 9.0, 10.0
    };
    Complex c[10];
    for(int i=0; i<10; i++){
        c[i] = Complex(reals[i], imags[i]);
        cout << "c[" << i << "].modulus(): " << c[i].modulus() << endl;
    }

    cout << "------------------------" << endl;
    cout << "Sorting complex numbers in decreasing order!" << endl;


    for(int i=0; i<10; i++){
        int min = i;
        for(int j=i; j<10; j++){
            if( c[j] > c[min]){
                min = j;
            }
        }
        Complex temp = c[i];
        c[i] = c[min];
        c[min] = temp;
    }
    for(int i=0; i<10; i++){
        cout << "c[" << i << "].modulus(): " << c[i].modulus() << endl;
    }
    return 0;
}