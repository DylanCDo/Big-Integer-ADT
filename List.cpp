#include<iostream>
#include<string>
#include "List.h"

// Class Constructors & Destructors ----------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}

// Creates new List in the empty state.
List::List(){
    frontDummy = new Node(-123456789);
    backDummy = new Node(-123456789);

    frontDummy->prev = backDummy;
    backDummy->next = frontDummy;

    afterCursor = backDummy;
    beforeCursor = frontDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy constructor.
List::List(const List& L){

    // make this an empty List
    frontDummy = new Node(-123456789);
    backDummy = new Node(-123456789);

    frontDummy->prev = backDummy;
    backDummy->next = frontDummy;

    afterCursor = backDummy;
    beforeCursor = frontDummy;
    pos_cursor = 0;
    num_elements = 0;

    if (L.length() == 0){
        return;
    }

    Node* N = L.frontDummy->next;
    while( N != L.backDummy ){
        this->insertBefore(N->data);
        N = N->next;
    }


}

// Destructor
List::~List(){
    moveFront();
    while ( length() > 0 ){

        eraseAfter();

    }

    delete frontDummy;

    delete backDummy;

}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    if( length() == 0 ){
       throw std::length_error("List: getFront(): empty List");
    }
    return (frontDummy->next)->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if( length() == 0 ){
       throw std::length_error("List: getFront(): empty List");
    }
    return(backDummy->prev)->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    if( 0 > pos_cursor && pos_cursor > length() ){
        throw std::length_error("List: position(): cursor is out of range");
    }
    return(pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    if( pos_cursor >= length() ){
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return(afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if( position() <= 0 ){
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return(beforeCursor->data);
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    moveFront();
    while ( length() > 0){
        eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;

}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    pos_cursor = length();
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
    if( position() >= length() ){
        throw std::range_error("List: moveNext(): cursor at back");
    }

    ListElement returnValue = afterCursor->data;

    pos_cursor += 1;
    afterCursor = afterCursor->next;
    beforeCursor = beforeCursor->next;

    return returnValue;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if( position() <= 0 ){
        throw std::range_error("List: movePrev(): cursor at front");
    }

    ListElement returnValue = beforeCursor->data;

    pos_cursor -= 1;
    afterCursor = afterCursor->prev;
    beforeCursor = beforeCursor->prev;

    return returnValue;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){

    //Creating New Node
    Node* N = new Node(x);

    //Setting the next and previous of the New Node
    N->prev = beforeCursor;
    N->next = afterCursor;


    //Setting the beforeCursor's next and afterCursor's prev to the New Node
    beforeCursor->next = N;
    afterCursor->prev = N;
    
    //Setting the afterCursor to the New Node.
    afterCursor = N;

    //Increasing the number of elements
    num_elements += 1;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    //Creating New Node
    Node* N = new Node(x);

    //Setting the next and previous of the New Node
    N->prev = beforeCursor;
    N->next = afterCursor;

    //Setting the beforeCursor's next and afterCursor's prev to the New Node
    beforeCursor->next = N;
    afterCursor->prev = N;
    
    //Setting the beforeCursor to the New Node.
    beforeCursor = N;

    //Increasing the number of elements
    num_elements += 1;

    //Increasing the cursor positiong due to New Node being added before the cursor.
    pos_cursor += 1;

}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if( position() >= length() ){
        throw std::range_error("List: setAfter(): cursor at back");
    }

    //Setting afterCursor's element to x.
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if( position() <= 0 ) {
        throw std::range_error("List: setBefore(): cursor at front");
    }

    //Setting beforeCursor's element to x.
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if( position() >= length() ){
        throw std::range_error("List: eraseAfter(): cursor at back");
    }

    Node* N = afterCursor;

    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;

    afterCursor = afterCursor->next;

    num_elements -= 1;

    delete N;

}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if( position() <= 0 ){
        throw std::range_error("List: eraseBefore(): cursor at front");
    }

    if (beforeCursor == frontDummy){
        return;
    }

    Node* N = beforeCursor;

    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;

    beforeCursor = beforeCursor->prev;

    num_elements -= 1;

    pos_cursor -= 1;

    delete N;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    for (int i = position(); i < length(); i++){
        if (afterCursor->data == x){
            moveNext();
            return position();
        } else {
            moveNext();
        }
    }

    moveBack();

    return -1;

}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    for (int i = position(); i > 0; i--){
        if (beforeCursor->data == x){
            movePrev();
            return position();
        } else {
            movePrev();
        }
    }

    moveFront();

    return -1;

}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){

    //Iterating through the nodes.
    Node* N = frontDummy;
    Node* check;

    while(true){

        //Iterating the node to next.
        N = N->next;

        //Checking if N is at the end.
        if (N == backDummy){
            break;
        }

        //Setting the check to be the next node after N.
        check = N;

        //Setting 
        while(check != backDummy){

            check = check->next;

            //Checking if
            if (check == backDummy){
                break;
            }
            
            if (N->data == check->data ){
                Node* del = check;

                //Iterating check to the next node
                check = check->next;

                //Setting check's previous to the del's previous.
                check->prev = del->prev;

                //Setting the node bfore the deleted node's next to the check.
                check->prev->next = check;

                //Subtracting number of elements.
                num_elements -= 1;

                //if the cursor becomes greater than the length, it will move back into range.
                if (position() > length()){
                    pos_cursor -= 1;
                }

                delete del;
            }

        }

    }
}
 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List X;

    Node* N = this->frontDummy->next;
    while( N != this->backDummy ){
        X.insertBefore(N->data);
        N = N->next;
    }

    Node* M = L.frontDummy->next;
    while( M != L.backDummy ){
        X.insertBefore(M->data);
        M = M->next;
    }

    X.moveFront();

    return X;

}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    std::string s = "(";

    for(Node* N = frontDummy->next; N != backDummy ; N=N->next){
        s += std::to_string(N->data);

        if (N->next != backDummy){
            s += ", ";
        }
    }

    s+= ")";

    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    Node* N = nullptr;
    Node* M = nullptr;

    if (this->length() != R.length() ){
        return false;
    }

    N = this->frontDummy->next;
    M = R.frontDummy->next;
    for (int i = 0; i < length(); i ++){
        if (N->data != M->data){
            return false;
        }
        N = N->next;
        M = M->next;
    }
    return true;
}


// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if ( this != &L ){
        List temp = L;

        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
    }

    return *this;
}
