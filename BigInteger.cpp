#include <cmath>
#include <iostream>
#include "BigInteger.h"

const long base = 1000000000;
const long power = 9;
const long zeroes = ceil(log10(base));

using namespace std;

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){

    signum = 0;
    
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){

    //Prerequisite for this function
    if (s.length() == 0){
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }

    //Setting signum to 0.
    signum = 0;

    //Checking for the optional sign at the front of the string and erasing it if so.
    if ( s[0] == '-' ){
        signum = -1;
        s.erase(0,1);
    } else if ( s[0] == '+' ){
        signum = 1;
        s.erase(0,1);
    }

    //Reversing the string to add to the list.
    int j = s.length() - 1;
    int length = s.length();
    for (int i = 0 ; i < (length/2); i++){
        swap(s[i], s[j]);    
        j -= 1;
    }

    //Creating a string to add to.
    string d = "";

    //Creating a variable to keep track of the amount of characters are added to the string.
    long count = 0;
    long digit = 0;
    long num = 0;

    //Iterating through the string and checing each element if it isn't a digit.
    for (char &c : s){
        if ( !(std::isdigit(c)) ){
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }

        //Adding to d.
        string x(1, c);
        if (d.length() != 0){
            d.insert(0, x);
        } else {
            d += x;
        }
        
        //Incrementing count.
        count ++;

        //converting the number into a digit for the BigInteger
        if (count == zeroes){

            //Converting the digit and finding overFlow.
            num = stol(d);
            digit = num % base;
            num = num/base;

            //Resetting temp variables to original states
            d = "";
            count = 0;

            //inserting it into the list.
            digits.insertAfter(digit);
        }

    }

    //Converting the digit and finding overFlow.
    if (d.length() != 0){
        num += stol(d);
        digit = num % base;
        num = num/base;

        //inserting it into the list.
        digits.insertAfter(digit);
    }

    

    if (num != 0){
        digits.insertAfter(num);
    }

    //If signum isn't set yet.
    if (signum == 0){
        signum = 1;
    }

    //Removing Leading zeroes
    for (int i = 0 ; i < digits.length(); i++){
        if (digits.peekNext() == 0){
            digits.eraseAfter();
            i--;
        } else {
            break;
        }
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger::BigInteger(const BigInteger& N){

    this->signum = N.signum;
    this->digits = N.digits;

}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::BigInteger::compare(const BigInteger& N) const{

    //Determining the comparison based on the sign.
    if (sign() > N.sign()){
        return 1;
    } else if (sign() < N.sign()){
        return -1;

    //Now Checking the Lists of each BigInteger to determine the comparison results. 
    } else if (sign() == N.sign()){

        //Since the signs are equal, checking to see if they are 0 first.
        if (sign() == 0){
            return 0;
        }
        
        //Creating copy  the digits list from both entries.
        List A = this->digits;
        List B = N.digits;

        //Checking to see which list is physically longer and returning output based on the sign.
        if (A.length() < B.length()){
            if (sign() == -1){
                return 1;
            } else {
                return -1;
            }
        } else if (A.length() > B.length()){

            if (sign() == -1){
                return -1;
            } else {
                return 1;
            }

        //This means that the lengths of A and B are equal. It is time to check individual elements.
        //At this point, both the signs and the length of the list are the same.
        } else {
            
            //Moving the cursot to the front on both entries
            A.moveFront();
            B.moveFront();

            //Checking if each element starting from the front of the list is not equal.
            for (int i = 0; i < A.length(); i++){

                //Setting variables for digits and adding their respective signs to them.
                long digitA = A.peekNext() * this->sign();
                long digitB = B.peekNext() * N.sign();

                //Comparing each individual element.
                if (digitA != digitB){

                    if (digitA < digitB){
                        return -1;
                    } else {
                        return 1;
                    }

                }

                //Iterating the lists.
                A.moveNext();
                B.moveNext();
            }

            //All tests have concluded, therefore these integers are equal.
            return 0;

        }

    }

    

    //If it returns 99, something is wrong.
    return 99;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::BigInteger::makeZero(){
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::BigInteger::negate(){
    if (sign() != 0){

        if (sign() == -1){
            signum = 1;
        } else {
            signum = -1;
        }

    }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{

    //Return Variable
    BigInteger S; 

    //Copies of this and N
    BigInteger C1  = (*this);
    BigInteger C2  = N;
    
    //If one of the BigIntegers are zero, it will just set S to the other one and return it.
    if ((*this) == S){
        S = N;

        return S;
    } else if (N == S){
        S = (*this);

        return S;
    }

    //Determining the signum based on comparisons
    if (this->signum == N.signum){
        S.signum = this->signum;

    //Signum is not the same, which leads to comparing the asbolute values of the values.
    } else {

        //If it isn't positive, make it positive.
        if (C1.signum != 1){
            C1.negate();
        }

        //If it isn't positive, make it positive.
        if (C2.signum != 1){
            C2.negate();
        }
        
        //Comparing the physical value to determine what the signum of this function will be.
        if (C1 >= C2){
            S.signum = this->signum;
        } else {
            S.signum = N.signum;
        }
    }


    //Creating Big and Small Lists.
    List Big;
    List Small;

    //Variables;
    int iters;
    int bigSign;
    int smallSign;
    long overFlow = 0;
    bool reduction = false;

    //Setting the iter variable and List Copies.
    if (C1 >= C2){

        //Setting the Lists.
        Big = this->digits;
        Small = N.digits;

        //Setting the signs.
        bigSign = this->sign();
        smallSign = N.sign();

        //Setting the iters to the smallest list length.
        iters = Small.length();

    } else {
        
        //Setting the Lists. 
        Big = N.digits;
        Small = this->digits;

        //Setting the signs.
        bigSign = N.sign();
        smallSign = this->sign();

        //Setting the iters to the smallest list length.
        iters = Small.length();
    }

    //If the signs are the same, set arithmetics sign variables to positive.
    if (this->sign() == N.sign()){
        bigSign = 1;
        smallSign = 1;
    }

    //Moving the cursors of the lists back.
    Big.moveBack();
    Small.moveBack();

    //Iterating through the lists.
    //This should only iterate for as long as small.
    for (int i = 0; i < iters; i++){

        //Peeking the previous element.
        long digitA = Big.peekPrev() * bigSign;
        long digitB = Small.peekPrev() * smallSign;

        //Applying reduction if it is true
        if (reduction){

            //If digitA is not zero, reduce, else, add the base and keep reduction true.
            if (digitA != 0){
                digitA -= 1 * bigSign;
                reduction = false;
            } else {
                digitA += base * bigSign;
                digitA -= 1 * bigSign;
            }
            
        }

        //If the signs aren't the same, there can potentially be reduction
        if (bigSign != smallSign){

            //Checking if reduction is plausible
            if(abs(digitA) < abs(digitB)){
                digitA += base * bigSign;
                reduction = true;
            }
        }

        //Addition time :D
        long digitS = digitA + digitB;

        //Adding an overFlow if it exists.
        if (overFlow != 0){
            digitS += overFlow;
            overFlow = 0;
        }

        //Obtaining overflow
        if (abs(digitS) >= base){
            //Retrieving the overflow amount by dividing by the base.
            overFlow = digitS/base;

            //Retrieving the remainder
            digitS = abs(digitS)%base * bigSign;
        }

        //Adding the digit to the new BigInteger
        //Adding absolute value because negatives are not allowed as an entry for this adt.
        S.digits.insertAfter(abs(digitS));

        //Moving the cursor of Big and Small back.
        Big.movePrev();
        Small.movePrev();
    }

    //Iterating through the rest of Big.
    //Will not perform if big is the same length as small.
    for (int j = 0; j < Big.length() - iters; j++){

        long digitA = Big.peekPrev() * bigSign;

        //Applying reduction if it is true
        if (reduction){

            //If digitA is not zero, reduce, else, add the base and keep reduction true.
            if (digitA != 0){
                digitA -= 1 * bigSign;
                reduction = false;
            } else {
                digitA += base * bigSign;
                digitA -= 1 * bigSign;
            }
            
        }

        //Adding an overFlow if it exists.
        if (overFlow != 0){
            digitA += overFlow;
            overFlow = 0;
        }

        //Obtaining overflow
        if (abs(digitA) >= base){
            //Retrieving the overflow amount by dividing by the base.
            overFlow = digitA/base;

            //Retrieving the remainder
            digitA = abs(digitA)%base * bigSign;
        }

        //Adding the rest of the numbers
        S.digits.insertAfter(abs(digitA));

        //Moving the cursor of Big back by one.
        Big.movePrev();
    }

    //Adding an overFlow if it exists.
    if (overFlow != 0){
        S.digits.insertAfter(abs(overFlow));
    }

    //Removing Leading zeroes
    for (int i = 0 ; i < S.digits.length(); i++){
        if (S.digits.peekNext() == 0){
            S.digits.eraseAfter();
            i--;
        } else {
            break;
        }
    }

    //If the resulting BigInteger is 0, makeZero for safety measures.
    if (S.digits.length() == 0){
        S.makeZero();
    }

    //Returning the newly formed BigInteger.
    return S;

}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger S = N;
    S.negate();
    return this->add(S);
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{

    //Return Variable
    BigInteger S;

    //Copies of this->digits and N.digits
    List C1;
    List C2;

    //Checking if either integer is zero
    if ((*this) == S || N == S){
        return S;
    }

    //Determing the top and bottom of the arithmetic operation.
    if (this->digits.length() >= N.digits.length()){
        C1 = this->digits;
        C2 = N.digits;
    } else {
        C1 = N.digits;
        C2 = this->digits;
    }

    //Creating overflow
    long overFlow = 0;
    
    //Moving the cursor to the back of the shorter list.
    C2.moveBack();

    //Performing the arithmetic. Iterating through the shorter list first
    for (int i = 0; i < C2.length(); i++){

        //Creating a list to store the arithmetics
        BigInteger mult;

        //Setting mult's sign to positive.
        mult.signum = 1;

        //Moving C2's cursor to the element before
        C2.movePrev();
 
        //Creating the first long to be multiplied.
        long x = C2.peekNext();

        //Moving the cursor to the back of the longer list.
        C1.moveBack();

        //Iterating though the longer list
        for (int j = 0; j < C1.length(); j++){

            //Moving C1's cursor to the element before
            C1.movePrev();

            //Obtaining the second number for the multiplication.
            long y = C1.peekNext();

            //Multiplying :D
            long result = x * y;

            //adding it to the list.
            mult.digits.insertAfter(result);

        }

        //Moving back the mult.digits cursor
        mult.digits.moveBack();

        //Normalizing
        for (int j = 0; j < mult.digits.length(); j++){

            mult.digits.movePrev();

            long digit = mult.digits.peekNext();

            //Adding an overFlow if it exists.
            if (overFlow != 0){
                digit += overFlow;
                overFlow = 0;
            }

            //Obtaining overflow
            if (digit >= base){
                //Retrieving the overflow amount by dividing by the base.
                overFlow = digit/base;

                //Retrieving the remainder
                digit = digit%base;
            }

            mult.digits.setAfter(digit);

        }

        if (overFlow != 0){
            mult.digits.insertAfter(overFlow);
            overFlow = 0;
        }

        if (overFlow != 0){
            mult.digits.insertAfter(overFlow);
        }

        //Moving back the mult.digits cursor
        mult.digits.moveBack();

        //Shifting the number based on the iteration
        for (int k = 0; k < i ; k++){
            mult.digits.insertAfter(0);
        }

        //Moving mult cursor back to the front for safety.
        mult.digits.moveFront();

        //Adding mult to S.
        S += mult;

    }

    //Determining the signs
    if (this->signum == N.signum){
        S.signum = 1;
    } else {
        S.signum = -1;
    }

    return S;

}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){

    //Initializing the return string.
    string s = "";

    //Checking if the Big integer is 0
    if (digits.length()==0){
        return s+= "0";
    }

    //Adding a negative in case the Big Integer is a negative number.
    if (signum == -1){
        s += "-";
    }

    //Turning the base number to a string
    string strbase = std::to_string(base);

    //Taking the length of the string base - 1 to determine the maximum amount of leading zeroes to be printed.
    int lead  = strbase.length() - 1;

    //Moving the cursor of digits to the front to start iterations.
    digits.moveFront();

    //Iterating through the elements of digits.
    for (int i = 0; i < digits.length(); i ++){

        //Asigns the iterated element into a long.
        long digit = digits.peekNext();

        //Converts it into a string.
        string conversion = std::to_string(digit);

        //Records the length of the digit string.
        int conversionLen = conversion.length();

        
        //Loop to determine the amount of leading 0's that need to be printed.
        for (int j = 0; j < lead - conversionLen; j++){

            //Preventing printing a zero out if it is the first number.
            if (digits.position() != 0){
                s+= "0";
            }
            
        }

        //Moving the cursor to the next element in digits.
        digits.moveNext();

        //Adding to s
        s+= conversion;
    }

    //Returning the string
    return s;
}


// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == 0);
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == -1);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == -1 || A.compare(B) == 0);
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == 1);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == 1 || A.compare(B) == 0);
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    BigInteger C = A.add(B);
    return C;
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    BigInteger C = A.sub(B);
    return C;
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    BigInteger C = A.mult(B);
    return C;
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    return A = A.mult(B);
}

