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

// //-----------------------------------------------------------------------------
// //  BigIntegerClient.cpp 
// //  A test client for the BigInteger ADT
// //-----------------------------------------------------------------------------
// #include<iostream>
// #include<string>
// #include<stdexcept>
// #include"BigInteger.h"

// using namespace std;

// int main(){

//    string s1 = "9128734667000004389234563456345619187236478";
//    //string s2 = "-330293847502398475";
//    string s3 = "9876545439000000000000000200000000000006543654365346534";
//    //string s4 = "9876545439000000000000000100000000000006543654365346534";
//    //string s5 = "98765454390000000000000000000000000000065436543";
//    //string s6 = "9876545439000000000000000000000000000006543";

//    //BigInteger N;
//    BigInteger A = BigInteger(s1);
//    BigInteger B = BigInteger(s3);

//    cout << endl;

//    cout << "A = " << A << endl;
//    cout << "B = " << B << endl;
//    cout << endl;

//    BigInteger C = A+B;
//    BigInteger D = B+A;
//    BigInteger E = A-A;
//    BigInteger F = B-A;
//    BigInteger G = A*B;
//    BigInteger H = B*A;
//    BigInteger I = C*E;

//    cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
//    cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
//    cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
//    cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
//    cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

//    cout << "C = " << C << endl;
//    cout << "D = " << D << endl;
//    cout << "(C==D) = " << ((C==D)?"True":"False") << endl;
//    cout << "E = " << E << endl;
//    cout << "F = " << F << endl;
//    cout << "G = " << G << endl;
//    cout << "H = " << H << endl;
//    cout << "(G==H) = " << ((G==H)?"True":"False") << endl;
//    cout << "I = " << I << endl << endl;

//    cout << endl;

//    A += B;
//    B -= C;
//    C *= D;
//    cout << "A = " << A << endl;
//    cout << "B = " << B << endl;
//    cout << "C = " << C << endl;
//    cout << endl;

//    cout << A*B*C*D*F*G*H << endl << endl;

//    cout << endl;

//    // test exceptions
//    try{
//       BigInteger J = BigInteger("");
//    }catch( std::invalid_argument& e ){
//       cout << e.what() << endl;
//       cout << "   continuing without interruption" << endl;
//    }
//    try{
//       BigInteger J = BigInteger("+");
//    }catch( std::invalid_argument& e ){
//       cout << e.what() << endl;
//       cout << "   continuing without interruption" << endl;
//    }
//    try{
//       BigInteger J = BigInteger("12329837492387492837492$4982379487293847");
//    }catch( std::invalid_argument& e ){
//       cout << e.what() << endl;
//       cout << "   continuing without interruption" << endl;
//    }
//    try{
//       BigInteger J = BigInteger("5298374902837409+82734098729287349827398");
//    }catch( std::invalid_argument& e ){
//       cout << e.what() << endl;
//       cout << "   continuing without interruption" << endl;
//    }

//    cout << endl;

//    return EXIT_SUCCESS;
// }
