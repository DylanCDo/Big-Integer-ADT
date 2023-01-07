#include<iostream>
#include<string>
#include<stdexcept>
#include <cmath>
#include"BigInteger.h"

using namespace std;

int main(){

    string s = "-111122223333";

    string t = "111122223333";

    BigInteger A = BigInteger(s);

    BigInteger B = BigInteger(t);

    // cout << "A = " << A << endl;

    // cout << "B = " << B << endl;

    // cout << "A Compared to B: " << A.compare(B) << endl;

    // cout << "B Compared to A: " << B.compare(A) << endl;

    // cout << "Boolean Operations: " << endl;

    // cout<< "A < B: " << (A < B) << endl; 

    // cout<< "A <= B: " << (A <= B) << endl;

    // cout<< "A > B: " << (A > B) << endl; 

    // cout<< "A >= B: " << (A >= B) << endl; 

    // cout<< "A == B: " << (A == B) << endl; 

    // BigInteger C = A.add(B);

    // BigInteger D = A.sub(B);

    // BigInteger E = C + D;

    // BigInteger F = C - D;

    // cout << "Addition Function of A and B = C " << C << endl;

    // cout << "Subtraction Function of A and B = D " << D << endl;

    // cout << "C + D = E " << E << endl;

    // cout << "C - D = F " << F << endl;

    // A.negate();

    // cout << "Testing negate() on A: " << A << endl;

    // A.makeZero();

    // cout << "Testing makeZero() on A: " << A << endl;

    BigInteger X = A.mult(B);

    cout << "A * B = " << X << endl;

}
