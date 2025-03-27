// Jason Waseq
// jwaseq
// pa8
// Dictionary.cpp

#include "Dictionary.h"
#include <iostream>
#include <string>

// Class Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = 0; 
}

Dictionary::Dictionary() {
    nil = new Node("", 0);
    nil->color = 0; 
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("", 0);
    nil->color = 0;
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
    clear();
    delete nil;
}

// Helper Functions (Optional) ---------------------------------------------

void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key + (R->color == 1 ? " (RED)\n" : "\n");
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::BST_insert(Node* M) {
    Node* y = nil;
    Node* x = root;
    while (x != nil) {
        y = x;
        if (M->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    M->parent = y;
    if (y == nil) {
        root = M;
    } else if (M->key < y->key) {
        y->left = M;
    } else {
        y->right = M;
    }
    M->left = nil;
    M->right = nil;
    M->color = 1; 
    RB_InsertFixUp(M);
    num_pairs++;
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    while (R != nil && k != R->key) {
        if (k < R->key) {
            R = R->left;
        } else {
            R = R->right;
        }
    }
    return R;
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    while (R->left != nil) {
        R = R->left;
    }
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    while (R->right != nil) {
        R = R->right;
    }
    return R;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N->right != nil) {
        return findMin(N->right);
    }
    Node* y = N->parent;
    while (y != nil && N == y->right) {
        N = y;
        y = y->parent;
    }
    return y;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) {
        return findMax(N->left);
    }
    Node* y = N->parent;
    while (y != nil && N == y->left) {
        N = y;
        y = y->parent;
    }
    return y;
}

// RBT Helper Functions (Optional) -----------------------------------------

void Dictionary::LeftRotate(Node* N) {
    Node* y = N->right;
    N->right = y->left;
    if (y->left != nil) {
        y->left->parent = N;
    }
    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->left) {
        N->parent->left = y;
    } else {
        N->parent->right = y;
    }
    y->left = N;
    N->parent = y;
}

void Dictionary::RightRotate(Node* N) {
    Node* y = N->left;
    N->left = y->right;
    if (y->right != nil) {
        y->right->parent = N;
    }
    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->right) {
        N->parent->right = y;
    } else {
        N->parent->left = y;
    }
    y->right = N;
    N->parent = y;
}

void Dictionary::RB_InsertFixUp(Node* N) {
    while (N->parent->color == 1) {
        if (N->parent == N->parent->parent->left) {
            Node* y = N->parent->parent->right;
            if (y->color == 1) {
                N->parent->color = 0;
                y->color = 0;
                N->parent->parent->color = 1;
                N = N->parent->parent;
            } else {
                if (N == N->parent->right) {
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = 0;
                N->parent->parent->color = 1;
                RightRotate(N->parent->parent);
            }
        } else {
            Node* y = N->parent->parent->left;
            if (y->color == 1) {
                N->parent->color = 0;
                y->color = 0;
                N->parent->parent->color = 1;
                N = N->parent->parent;
            } else {
                if (N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = 0;
                N->parent->parent->color = 1;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = 0;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N) {
    while (N != root && N->color == 0) {
        if (N == N->parent->left) {
            Node* w = N->parent->right;
            if (w->color == 1) {
                w->color = 0;
                N->parent->color = 1;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if (w->left->color == 0 && w->right->color == 0) {
                w->color = 1;
                N = N->parent;
            } else {
                if (w->right->color == 0) {
                    w->left->color = 0;
                    w->color = 1;
                    RightRotate(w);
                    w = N->parent->right;
                }
                w->color = N->parent->color;
                N->parent->color = 0;
                w->right->color = 0;
                LeftRotate(N->parent);
                N = root;
            }
        } else {
            Node* w = N->parent->left;
            if (w->color == 1) {
                w->color = 0;
                N->parent->color = 1;
                RightRotate(N->parent);
                w = N->parent->left;
            }
            if (w->right->color == 0 && w->left->color == 0) {
                w->color = 1;
                N = N->parent;
            } else {
                if (w->left->color == 0) {
                    w->right->color = 0;
                    w->color = 1;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                w->color = N->parent->color;
                N->parent->color = 0;
                w->left->color = 0;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = 0;
}

void Dictionary::RB_Delete(Node* N) {
    Node* y = N;
    Node* x;
    int y_original_color = y->color;
    if (N->left == nil) {
        x = N->right;
        RB_Transplant(N, N->right);
    } else if (N->right == nil) {
        x = N->left;
        RB_Transplant(N, N->left);
    } else {
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == N) {
            x->parent = y;
        } else {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if (y_original_color == 0) {
        RB_DeleteFixUp(x);
    }
    delete N;
    num_pairs--;
}

// Access functions --------------------------------------------------------

int Dictionary::size() const {
    return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    return search(root, k) != nil;
}

valType& Dictionary::getValue(keyType k) const {
    Node* N = search(root, k);
    if (N == nil) {
        throw std::invalid_argument("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    return N->val;
}

bool Dictionary::hasCurrent() const {
    return current != nil;
}

keyType Dictionary::currentKey() const {
    if (!hasCurrent()) {
        throw std::invalid_argument("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw std::invalid_argument("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    Node* N = search(root, k);
    if (N != nil) {
        N->val = v;
    } else {
        Node* M = new Node(k, v);
        BST_insert(M);
    }
}

void Dictionary::remove(keyType k) {
    Node* N = search(root, k);
    if (N == nil) {
        throw std::invalid_argument("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    if (N == current) {
        current = nil;
    }
    RB_Delete(N);
}

void Dictionary::begin() {
    if (root != nil) {
        current = findMin(root);
    }
}

void Dictionary::end() {
    if (root != nil) {
        current = findMax(root);
    }
}

void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::invalid_argument("Dictionary: next(): current undefined");
    }
    current = findNext(current);
}

void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::invalid_argument("Dictionary: prev(): current undefined");
    }
    current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

std::string Dictionary::to_string() const {
    std::string s;
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const {
    std::string s;
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
    if (num_pairs != D.num_pairs) {
        return false;
    }
    std::string this_string = to_string();
    std::string D_string = D.to_string();
    return this_string == D_string;
}

// Overloaded Operators ----------------------------------------------------

std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    return stream << D.to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
    if (this != &D) {
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}

