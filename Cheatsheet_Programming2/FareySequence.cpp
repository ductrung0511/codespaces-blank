#include <iostream>

using namespace std;

class Fraction {
private:
    size_t nominator;
    size_t denominator;
    bool negative;

public:
    Fraction(int nom = 0, int denom = 1) {
        if (denom == 0) {
            throw std::invalid_argument("Denominator 0");
        }
        negative = (nom < 0) ^ (denom < 0); // XOR for sign
        nominator = std::abs(nom);
        denominator = std::abs(denom);
        simplify();
    }

    static size_t gcd(size_t a, size_t b) {
        while (b != 0) {
            size_t temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    void simplify() {
        size_t g = gcd(nominator, denominator);
        nominator /= g;
        denominator /= g;
    }

    double value() const {
        return  static_cast<double>(nominator) / denominator;
    }
    bool operator<(const Fraction& other) const {
        return this->value() < other.value();
    }
    bool operator==(const Fraction& other) const {
        return nominator == other.nominator && denominator == other.denominator && negative == other.negative;
    }

    void print() const {
        if (negative && nominator != 0) std::cout << "-";
        std::cout << nominator << "/" << denominator << "\n";
    }

    float getValue() const {
        return  negative ?  nominator/denominator * -1  : nominator/denominator ;
    }

    // Accessors for external use
    size_t getNum() const { return nominator; }
    size_t getDen() const { return denominator; }
};


class FareySequence{
    private: 
        size_t degree;
        Fraction * data;
        size_t count ;    
        size_t size;  
    public:
        FareySequence(size_t degree) : degree(degree){
            size = fareySize(degree);
            data = new Fraction[size];
            count = 0;
        }
        ~FareySequence() {
        delete[] data;
        }
        static size_t gcd(size_t a, size_t b) {
            while (b != 0) {
                size_t temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }
        static size_t phi(size_t k) {
            size_t count = 0;
            for (size_t i = 1; i <= k; ++i) {
                if (gcd(i, k) == 1) {
                    ++count;
                }
            }
            return count;
        }
        static size_t fareySize(size_t n) {
            size_t total = 1;  // include 0/1
            for (size_t k = 1; k <= n; ++k) {
                total += phi(k);
            }
            return total;
        }
        void append(Fraction f){
            for(size_t i = 0; i < count; i++){
                if(data[i] == f){
                    return;
                }
            }
            if(count < size ){
                data[count++] = f;
            }
            else{
                cout << "Sequence Full" << endl;
            }
        }
        const Fraction operator[](size_t idx) {
            return data[idx];
        }
        size_t getSize(){ return size;}
        void sort() {
            for (size_t i = 0; i < count - 1; ++i) {
                for (size_t j = 0; j < count - i - 1; ++j) {
                    if (data[j + 1] < data[j]) {
                        // Swap data[j] and data[j + 1]
                        Fraction temp = data[j];
                        data[j] = data[j + 1];
                        data[j + 1] = temp;
                    }
                }
            }
        }
        void print(){
            for (size_t i = 0; i < count; ++i) {
                data[i].print();
            }
        }
        FareySequence& operator=(FareySequence& other){ //FareySequence& to support chaining || Assign one object to another (deep copy)
            // b = a;
            if (this == &other) return *this; // self-assignment check
            delete [] data;
            degree = other.degree;
            size = other.size;
            count = other.count;
            data = new Fraction[size];
            for (size_t i = 0; i < count; ++i) {
                data[i] = other.data[i];
            }
            return *this; // return reference
        }
        FareySequence(const FareySequence& other) { // Create a new object from another
            //	FareySequence b = a; or FareySequence b(a);
            degree = other.degree;
            size = other.size;
            count = other.count;
            data = new Fraction[size];
            for (size_t i = 0; i < count; ++i) {
                data[i] = other.data[i];
            }
        }
};

// Build Farey sequence up to order `n`
void buildFareySequence(size_t n) {
    FareySequence current(1);
    current.append(Fraction(0, 1));
    current.append(Fraction(1, 1));


    for (size_t order = 2; order <= n; ++order) {
        FareySequence next(order);
        next.append(current[0]);

        for (size_t i = 0; i < current.getSize() - 1; ++i) {
            Fraction a = current[i];
            Fraction b = current[i + 1];

            // Get mediant
            size_t mediant_num = a.getNum() + b.getNum();
            size_t mediant_den = a.getDen() + b.getDen();

            if (mediant_den <= order) {
                next.append(Fraction(mediant_num, mediant_den));
            }

            next.append(b);
        }

        // Sort 
        next.sort();
        current = next;
    }

    std::cout << "Farey sequence of degree " << n << ":\n";
    current.print();
}


int main() {
    int degree = 5;
    buildFareySequence(degree); // Call the generator
    return 0;
}
