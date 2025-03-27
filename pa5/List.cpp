// Jason Waseq
// jwaseq
// pa5
// List.cpp

#include <iostream>
#include <string>
#include "List.h"

using namespace std;

// Exported types -------------------------------------------------------------

List::Node::Node(ListElement x) : data(x), next(nullptr), prev(nullptr) {}

// Class Constructors & Destructors ----------------------------------------

// Creates a new List in the empty state.
List::List() : pos_cursor(0), num_elements(0){
    frontDummy = new Node(0);
    backDummy = new Node(0);

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    beforeCursor = frontDummy;
    afterCursor = backDummy;
}

// Copy constructor
List::List(const List& L) : List() {
    Node* current = L.frontDummy->next;
    while (current != L.backDummy) {
        insertBefore(current->data);
        current = current->next;
    }
}

// Destructor
List::~List() {
    Node* current = frontDummy;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if (num_elements == 0) {
       cerr << "List: front(): empty list" << endl;
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if (num_elements == 0) {
        cerr << "List: back(): empty list" << endl;
    }
    return backDummy->prev->data;
}

// position()
// Returns the position of the cursor in this List: 0 <= position() <= length().
int List::position() const {
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if (pos_cursor == num_elements) {
        cerr << "List: peekNext(): cursor at back" << endl;
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if (pos_cursor == 0) {
        cerr << "List: peekPrev(): cursor at front" << endl;
    }
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    Node* current = frontDummy->next;
    while (current != backDummy) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to the next higher position.
// Returns the List element that was passed over.
// pre: position()<length()
ListElement List::moveNext() {
    if (pos_cursor == num_elements) {
        cerr << "List: moveNext(): cursor at back" << endl;
    }
    ListElement data = afterCursor->data;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return data;
}

// movePrev()
// Advances cursor to the next lower position.
// Returns the List element that was passed over.
// pre: position()>0
ListElement List::movePrev() {
    if (pos_cursor == 0) {
        cerr << "List: movePrev(): cursor at front" << endl;
    }
    ListElement data = beforeCursor->data;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return data;
}

// insertAfter()
// Inserts x after the cursor.
void List::insertAfter(ListElement x) {
    Node* newNode = new Node(x);
    newNode->next = afterCursor;
    newNode->prev = beforeCursor;
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;

    afterCursor = newNode;
    num_elements++;
}

// insertBefore()
// Inserts x before the cursor.
void List::insertBefore(ListElement x) {
    Node* newNode = new Node(x);
    newNode->next = afterCursor;
    newNode->prev = beforeCursor;
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    beforeCursor = newNode;
    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    if (pos_cursor == num_elements) {
        cerr << "List: setAfter(): cursor at back" << endl;
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    if (pos_cursor == 0) {
        cerr << "List: setBefore(): cursor at front" << endl;
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes the element after the cursor.
// pre: position()<length()
void List::eraseAfter() {
    if (pos_cursor == num_elements) {
        cerr << "List: eraseAfter(): cursor at back" << endl;
    }

    Node* nodeToDelete = afterCursor;
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete nodeToDelete;
    num_elements--;
}

// eraseBefore()
// Deletes the element before the cursor.
// pre: position()>0
void List::eraseBefore() {
    if (pos_cursor == 0) {
        cerr << "List: eraseBefore(): cursor at front" << endl;
    }

    Node* nodeToDelete = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete nodeToDelete;
    pos_cursor--;
    num_elements--;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
   Node* currentNode = afterCursor;
    int stepsRight = 0;
    while (currentNode != backDummy) {
        stepsRight++;
        if (currentNode->data == x) {
            beforeCursor = currentNode;
            afterCursor = currentNode->next;
            pos_cursor += stepsRight;
            return pos_cursor;
        }
        currentNode = currentNode->next;
    }
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = length();
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    Node* currentNode = beforeCursor;
    int stepsLeft = 0;
    while (currentNode != frontDummy) {
        stepsLeft++;
        if (currentNode->data == x) {
            beforeCursor = currentNode->prev;
            afterCursor = currentNode;
            pos_cursor -= stepsLeft;
            return pos_cursor;
        }
        currentNode = currentNode->prev;
    }
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
   Node* outerNode = frontDummy->next; 
    int outerIndex = 0;                  
    while (outerNode != backDummy) {
        ListElement outerValue = outerNode->data;
        Node* innerNode = outerNode->next;  
        int innerIndex = outerIndex + 1;      
        while (innerNode != backDummy) {
            ListElement innerValue = innerNode->data;
            Node* prevNode = innerNode->prev;
            Node* nextNode = innerNode->next;
            Node* nodeToRemove = innerNode;
            innerNode = nextNode; 
            if (innerValue == outerValue) {
                prevNode->next = nextNode;
                nextNode->prev = prevNode;
                delete nodeToRemove;
                num_elements--;  
                if (innerIndex <= pos_cursor) {
                    pos_cursor--;
                }
            }
            innerIndex++;
        }
        outerIndex++;
        outerNode = outerNode->next; 
    }
    int finalPos = pos_cursor;
    moveFront();
    while (position() != finalPos) {
        moveNext();
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at position 0.
List List::concat(const List& L) const {
    List newList;
    newList.moveBack();
    Node* currentNode;
    currentNode = this->frontDummy->next;
    while (currentNode != this->backDummy) {
        newList.insertBefore(currentNode->data);
        currentNode = currentNode->next;
    }
    currentNode = L.frontDummy->next;
    while (currentNode != L.backDummy) {
        newList.insertBefore(currentNode->data);
        currentNode = currentNode->next;
    }
    newList.beforeCursor = newList.frontDummy;
    newList.afterCursor = newList.beforeCursor->next;
    newList.pos_cursor = 0;
    return newList;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    string result = "(";
    Node* current = frontDummy->next;
    while (current != backDummy) {
        result += std::to_string(current->data);
        if (current->next != backDummy) {
            result += ", ";
        }
        current = current->next;
    }
    result += ")";
    return result;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    if (length() != R.length()) {
        return false;
    }
    Node* currentThis = frontDummy->next;
    Node* currentR = R.frontDummy->next;
    while (currentThis != backDummy) {
        if (currentThis->data != currentR->data) {
            return false;
        }
        currentThis = currentThis->next;
        currentR = currentR->next;
    }
    return true;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<(std::ostream& stream, const List& L) {
    return stream << L.to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==(const List& A, const List& B) {
    return A.equals(B);
}

// operator=()
// Overwrites the state of this List with the state of L.
List& List::operator=(const List& L) {
    if (this != &L) {
        List temp = L;
        swap(frontDummy, temp.frontDummy);
        swap(backDummy, temp.backDummy);
        swap(num_elements, temp.num_elements);
	swap(pos_cursor, temp.pos_cursor);
	swap(beforeCursor, temp.beforeCursor);
	swap(afterCursor, temp.afterCursor);
    }
    return *this;
}

