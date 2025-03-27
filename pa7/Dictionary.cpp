// Jason Waseq
// jwaseq
// pa7
// Dictionary.cpp

#include "Dictionary.h"

// Class Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v) : key(k), val(v), parent(nullptr), left(nullptr), right(nullptr) {}

Dictionary::Dictionary() : nil(new Node("", 0)), root(nil), current(nil), num_pairs(0) {
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
}

Dictionary::Dictionary(const Dictionary& D) : nil(new Node("", 0)), root(nil), current(nil), num_pairs(0) {
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
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
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
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
    if (R == nil || k == R->key) {
        return R;
    } else if (k < R->key) {
        return search(R->left, k);
    } else {
        return search(R->right, k);
    }
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
    Node* P = N->parent;
    while (P != nil && N == P->right) {
        N = P;
        P = P->parent;
    }
    return P;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) {
        return findMax(N->left);
    }
    Node* P = N->parent;
    while (P != nil && N == P->left) {
        N = P;
        P = P->parent;
    }
    return P;
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
    Node* P = nil;
    Node* R = root;
    while (R != nil) {
        P = R;
        if (k < R->key) {
            R = R->left;
        } else if (k > R->key) {
            R = R->right;
        } else {
            R->val = v;
            return;
        }
    }
    Node* N = new Node(k, v);
    N->parent = P;
    if (P == nil) {
        root = N;
    } else if (k < P->key) {
        P->left = N;
    } else {
        P->right = N;
    }
    N->left = nil;
    N->right = nil;
    num_pairs++;
}

void Dictionary::remove(keyType k) {
    Node* N = search(root, k);
    if (N == nil) {
        throw std::invalid_argument("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    if (N == current) {
        current = nil;
    }
    if (N->left == nil) {
        if (N->parent == nil) {
            root = N->right;
        } else if (N == N->parent->left) {
            N->parent->left = N->right;
        } else {
            N->parent->right = N->right;
        }
        if (N->right != nil) {
            N->right->parent = N->parent;
        }
    } else if (N->right == nil) {
        if (N->parent == nil) {
            root = N->left;
        } else if (N == N->parent->left) {
            N->parent->left = N->left;
        } else {
            N->parent->right = N->left;
        }
        if (N->left != nil) {
            N->left->parent = N->parent;
        }
    } else {
        Node* Y = findMin(N->right);
        if (Y->parent != N) {
            if (Y->parent == nil) {
                root = Y->right;
            } else if (Y == Y->parent->left) {
                Y->parent->left = Y->right;
            } else {
                Y->parent->right = Y->right;
            }
            if (Y->right != nil) {
                Y->right->parent = Y->parent;
            }
            Y->right = N->right;
            Y->right->parent = Y;
        }
        if (N->parent == nil) {
            root = Y;
        } else if (N == N->parent->left) {
            N->parent->left = Y;
        } else {
            N->parent->right = Y;
        }
        Y->parent = N->parent;
        Y->left = N->left;
        Y->left->parent = Y;
    }

    delete N;
    num_pairs--;
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
    std::string thisString, DString;
    inOrderString(thisString, root);
    inOrderString(DString, D.root);
    return thisString == DString;
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
        clear();
        preOrderCopy(D.root, D.nil);
    }
    return *this;
}

