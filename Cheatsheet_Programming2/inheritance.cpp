#include<iostream>
using namespace std;

class Mother {
    public:
    virtual void display() = 0;
    void speak() {
        cout << "Mother speaks" << endl;
    }
};

class Daughter : public Mother {
    public:
    void display() override {
        cout << "Daughter's display" << endl;
    }
    void speak() {
        cout << "Daughter speaks " << endl;
    }
};





class C {
 protected: int x = 10;
 public: void f(){cout << "hello from C" << endl;};
 };


 class C2: public C1 {
 public: int x2;
 };
 
 class C1: public C {
 protected: int x1;
 public: void h(C *obj){
    // cout << obj -> x << endl;  not possible to access another instance of C 
    C2 obj2;
    // C3 obj3;
    obj2.x2 = 99; 
    cout << obj2.x2;
    // obj3.x;
    }
};



 class C3: public C {
 public: void f(){};
 }; 


int main(){
    C c;
    C1 c1;
    c1.h(&c);
}