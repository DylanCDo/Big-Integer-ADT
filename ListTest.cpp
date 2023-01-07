#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

   List A;

   //Testing empty list check.

   List A = *pA;


   //Teting for insert After.
   for( int i = 0; i <= 10; i++ ){
      A.insertAfter(i);
   }

   cout << "List A = " << A << endl;

   //Testing for insert Before

   for( int i = 0; i <= 10; i++ ){
       A.insertBefore(i);
   }

   cout << "List A = " << A << endl;

   //Testing position

   cout << "Position of Cursor A = " << A.position() << endl;

   //Testing MoveBack

   A.moveBack();

   cout << "Position of Cursor A = " << A.position() << endl;

   //Testing MoveForward

   A.moveFront();

   cout << "Position of Cursor A = " << A.position() << endl;

   //Testing Move Next

   A.moveNext();
   
   cout << "Position of Cursor A = " << A.position() << endl;

   //Testing Move Back

   A.movePrev();
   
   cout << "Position of Cursor A = " << A.position() << endl;

   //Testing Equals (==)

   List B = A;
   
   cout << "A==B is " << (A==B?"true":"false") << endl;

   //Testing Concat

   List C = A.concat(B);

   cout << "List C = " << C << endl;

   //Testing cleanup

   C.cleanup();

   cout << "List C = " << C << endl;

   //Testing for erases

   C.moveNext();

   C.eraseBefore();

   cout << "List C = " << C << endl;

   C.eraseAfter();

   cout << "List C = " << C << endl;

   //Testing sets

   C.moveNext();

   C.setAfter(-99);

   cout << "List C = " << C << endl;

   C.setBefore(-98);

   cout << "List C = " << C << endl;

   //Testing peeks

   cout << "peeking next" << C.peekNext(); << endl;

   cout << "peeking previous" << C.peekPrev(); << endl;

}  
