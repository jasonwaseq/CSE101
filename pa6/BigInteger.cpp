// Jason Waseq
// jwaseq
// pa6
// BigInteger.cpp

#include<iostream>
#include<string>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include "List.h"
#include "BigInteger.h"

using namespace std;

const long BASE  = 1000000000;  
const int POWER = 9;     

// Class Constructors & Destructors ----------------------------------------

BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}

BigInteger::BigInteger(long x) {
    signum = (x > 0) - (x < 0);  
    x = std::abs(x);
    do {
        digits.insertAfter(x % BASE);
        x /= BASE;
    } while (x > 0);
    if (signum == 0) digits.insertAfter(0);
}

BigInteger::BigInteger(std::string s) {
    if (s.empty()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    signum = (s[0] != '-') ? 1 : -1;
    s = (s[0] == '+' || s[0] == '-') ? s.substr(1) : s;
    if (s.find_first_not_of("0123456789") != std::string::npos) {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    s = std::string(POWER - s.length() % POWER, '0') + s;
    for (int i = s.length(); i > 0; i -= POWER) {
        digits.insertAfter(std::stol(s.substr(i - POWER, POWER)));
    }
    while (digits.length() > 1 && digits.front() == 0) {
        digits.eraseAfter();
    }
    if (digits.length() == 1 && digits.front() == 0) {
        signum = 0;
    }
}

BigInteger::BigInteger(const BigInteger& N) {
    this->signum = N.signum;
    this->digits = N.digits;
}

// Access functions --------------------------------------------------------

int BigInteger::sign() const{
    return signum;
}

int BigInteger::compare(const BigInteger& N) const {
    if (signum != N.signum) return (signum > N.signum) ? 1 : -1;
    if (signum == 0) return 0;
    const List& A = digits, & B = N.digits;
    if (A.length() != B.length()) return (A.length() > B.length()) ? signum : -signum;
    List A_copy = A, B_copy = B;
    A_copy.moveFront(), B_copy.moveFront();
    while (A_copy.position() < A.length()) {
        if (A_copy.peekNext() != B_copy.peekNext()) 
            return (A_copy.peekNext() > B_copy.peekNext()) ? signum : -signum;
        A_copy.moveNext(), B_copy.moveNext();
    }
    return 0;
}

// Manipulation procedures -------------------------------------------------

void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

void BigInteger::negate() {
    signum *= -1;
}

// BigInteger Arithmetic operations ----------------------------------------

BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger A = *this, B = N, result;
    if (A.sign() > 0 && B.sign() < 0) {
        B.negate();
        return A.sub(B);
    }
    if (A.sign() < 0 && B.sign() > 0) {
        A.negate();
        return B.sub(A);
    }
    if (A.sign() < 0 && B.sign() < 0) {
        A.negate();
        B.negate();
        result = A.add(B);
        result.negate();
        return result;
    }
    if (A > B) return B.add(A);
    List& a = A.digits, &b = B.digits, &sumDigits = result.digits;
    long carry = 0;
    for (a.moveBack(), b.moveBack(); a.position() > 0 && b.position() > 0; a.movePrev(), b.movePrev()) {
        long sum = carry + a.peekPrev() + b.peekPrev();
        carry = sum / BASE;
        sumDigits.insertAfter(sum % BASE);
    }
    while (b.position() > 0) {
        long sum = carry + b.peekPrev();
        carry = sum / BASE;
        sumDigits.insertAfter(sum % BASE);
        b.movePrev();
    }
    if (carry > 0) {
        sumDigits.insertAfter(carry);
    }
    result.signum = 1;
    return result;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger A = *this, B = N, C;
    if (A == B) return C;
    if (A.sign() != B.sign()) {
        B.negate();
        return A.add(B);
    }
    if (A.sign() < 0 && B.sign() < 0) {
        A.negate();
        B.negate();
        return B.sub(A);
    }
    if (A < B) {
        C = B.sub(A);
        C.negate();
        return C;
    }   
    List& a = A.digits, &b = B.digits, &c = C.digits;
    long borrow = 0; 
    for (a.moveBack(), b.moveBack(); b.position() > 0; a.movePrev(), b.movePrev()) {
        long diff = a.peekPrev() - b.peekPrev() - borrow;
        if (diff < 0) {
            diff += BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }
        c.insertAfter(diff);
    }   
    while (a.position() > 0) {
        long diff = a.peekPrev() - borrow;
        c.insertAfter(diff < 0 ? diff + BASE : diff);
        borrow = diff < 0;
        a.movePrev();
    }
    while (C.digits.length() > 1 && C.digits.front() == 0) {
        C.digits.eraseAfter();
    }  
    C.signum = (C.digits.length() == 1 && C.digits.front() == 0) ? 0 : 1;
    return C;
}

BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger A = *this;
    BigInteger B = N;
    BigInteger C;
    List a = A.digits;
    List b = B.digits;
    int counter = 0;
    a.moveBack();
    int j = a.position();
    for (int i = j; i > 0; i--) {
        long w = a.peekPrev();
        List temp;
        long carry = 0;
        long tempResult = 0;
        for (b.moveBack(); b.position() > 0; b.movePrev()) {
            tempResult = (b.peekPrev() * w) + carry;
            carry = tempResult / BASE;
            tempResult %= BASE;
            temp.insertAfter(tempResult);
        }
        if (carry > 0) {
            temp.insertAfter(carry);
        }
        temp.moveBack();
        for (int k = 0; k < counter; k++) {
            temp.insertAfter(0);
        }
        BigInteger X;
        X.signum = 1;
        X.digits = temp;
        C = C.add(X);  
        a.movePrev();  
        counter++;
    }
    C.signum = A.signum * B.signum; 
    return C;
}

// Other Functions ---------------------------------------------------------

std::string BigInteger::to_string() {
    if (signum == 0) return "0";
    std::string a = (signum == -1) ? "-" : "";
    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        std::string current_str = std::to_string(digits.peekNext());
        if (digits.position() != 0) {
            current_str = std::string(POWER - current_str.length(), '0') + current_str;
        }
        a += current_str;
    }
    return a;
}

// Overriden Operators -----------------------------------------------------

std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.to_string();
}

bool operator==(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 0;
}

bool operator<(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == -1;
}

bool operator<=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) <= 0;
}

bool operator>( const BigInteger& A, const BigInteger& B ) {
     return !(A <= B);
}

bool operator>=( const BigInteger& A, const BigInteger& B ) {
    return !(A < B);
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A.add(B);
}
 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A.sub(B); 
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.mult(B);
    return A.mult(B);
}

