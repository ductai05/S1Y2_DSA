#include <iostream>
#include <vector>
using namespace std;

struct hashTable
{
    // Variables ( Attributes )
    struct hashNode
    {
        string key;
        int value;
        hashNode* left;
        hashNode* right;
        int height;
        hashNode(string k, int v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    int height(hashNode* node){
        if (node == nullptr) return 0;
        return node->height;
    }

    int getBalance(hashNode* node){
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    hashNode* rightRotate(hashNode* A){ // (B->C)<-A  =>  B->(C<-A)  
        hashNode* B = A->left;
        hashNode* C = B->right;

        B->right = A;
        A->left = C;
        
        A->height = 1 + max(height(A->left), height(A->right));
        B->height = 1 + max(height(B->left), height(B->right));
        return B;
    }

    hashNode* leftRotate(hashNode* A){ // A->(C<-B)  =>  (A->C)<-B
        hashNode* B = A->right;
        hashNode* C = B->left;

        B->left = A;
        A->right = C;

        A->height = 1 + max(height(A->left), height(A->right));
        B->height = 1 + max(height(B->left), height(B->right));
        return B;
    }

    int capacity;
    vector <hashNode *> table;

    // Functions ( Methods )
    // initialize an empty hash table with the given size.
    void init (unsigned int hashSize){
        capacity = hashSize;
        table.resize(capacity, nullptr);
    }

    // free all dynamically allocated memory in the hash table.
    void deleteAVL(hashNode* root){
        if (root == nullptr){
            return;
        } 
        deleteAVL(root->left);
        deleteAVL(root->right);
        delete root;
    }

    void release(){
        for (int i = 0; i < capacity; i++){
            hashNode* cur = table[i];
            deleteAVL(cur);
        }
        table.clear();
    }

    // hash functions to compute the index for a given key.
    unsigned int hashFunction(string key){
        int n = key.size();
        int m = 1000000009, asciiValue; // m = 10^9 + 9
        long long hash = 0, p = 31;
        for (int i = 0; i < n; i++){
            asciiValue = int(key[i]);
            hash += (asciiValue * p) % m;
            p = (p * 31) % m;
        }
        return static_cast<unsigned int> (hash);
    }

    // add element. If the key existed, update the old value.
    hashNode* insertNode(hashNode* root, string key, int value){
        // a. insertNode like BST
        if (root == nullptr) {
            hashNode* newNode = new hashNode(key, value);
            return newNode;
        }
        if (key < root->key) root->left = insertNode(root->left, key, value); 
        else if (key > root->key) root->right = insertNode(root->right, key, value);
        else root->value = value; // update the old value.

        // b. update Height
        root->height = 1 + max(height(root->left), height(root->right));

        // c. get Balance factor
        int balance = getBalance(root);

        // Left Left case:
        if (balance > 1 && getBalance(root->left) >= 0){
            return rightRotate(root);
        }
        // Left Right case:
        if (balance > 1 && getBalance(root->left) < 0){
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right case:
        if (balance < -1 && getBalance(root->right) <= 0){
            return leftRotate(root);
        }
        // Right Left case:
        if (balance < -1 && getBalance(root->right) > 0){
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root; // unchange root
    }

    void add(string key, int value){ //  Linked list
        unsigned int hashValue = hashFunction(key) % capacity;
        hashNode* newNode = new hashNode(key, value);

        table[hashValue] = insertNode(table[hashValue], key, value);
        return;
    }

    // search element in the table. If not existed, return NULL.
    int* searchNode(hashNode* root, string key){
        if (root == nullptr) return nullptr;
        if (root->key == key){
            int* res = new int(root->value);
            return res;
        }
        if (key < root->key) {
            return searchNode(root->left, key);
        }
        else {
            return searchNode(root->right, key);
        }
    }

    int* searchValue(string key){
        unsigned int hashValue = hashFunction(key) % capacity;
        return searchNode(table[hashValue], key);
    }

    // remove an element from the hash table.
    hashNode* minKeyNode(hashNode* node){
        hashNode* current = node;
        while (current->left != nullptr){
            current = current->left;
        }
        return current;
    }

    hashNode* deleteNode(hashNode* root, string key){
        // a. deleteNode BST
        if (root == nullptr) return root;

        if (key < root->key) root->left = deleteNode(root->left, key);
        else if (key > root->key) root->right = deleteNode(root->right, key);
        else {
            // no child or one child
            if ((root->left == nullptr) || (root->right == nullptr)){
                hashNode* temp = root->left ? root->left : root->right;

                if (temp == nullptr){ // no child case
                    temp = root;
                    root = nullptr;
                } else { // one child case
                    *root = *temp; // child -> root
                }
                delete temp;
            } else { // two child
                // get inorder successor
                hashNode* temp = minKeyNode(root->right);
                root->key = temp->key; // swap value (root <-> inorder successor)
                root->value = temp->value;
                root->right = deleteNode(root->right, temp->key); // delete inorder successor
            }
        }

        if (root == nullptr) return root;

        // b. update height;
        root->height = 1 + max(height(root->left), height(root->right));

        // c. get Balance factor
        int balance = getBalance(root);

        // Left Left case:
        if (balance > 1 && getBalance(root->left) >= 0){
            return rightRotate(root);
        }
        // Left Right case:
        if (balance > 1 && getBalance(root->left) < 0){
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right case:
        if (balance < -1 && getBalance(root->right) <= 0){
            return leftRotate(root);
        }
        // Right Left case:
        if (balance < -1 && getBalance(root->right) > 0){
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void removeKey(string key){
        unsigned int hashValue = hashFunction(key) % capacity;
        table[hashValue] = deleteNode(table[hashValue], key);
    }

    void printAVL(hashNode* root){
        if (root == nullptr) return;
        cout << "Key: " << root->key << " - Value: " << root->value << "\n";
        printAVL(root->left);
        printAVL(root->right);
    }
};

int main() {
    hashTable ht;
    ht.init(100); // init

    // add
    ht.add("apple", 1);
    ht.add("banana", 2);
    ht.add("cherry", 3);
    ht.add("date", 4);
    ht.add("fig", 5);

    // searchValue
    int* valuePtr = ht.searchValue("banana");
    if (valuePtr != nullptr) cout << "Found banana with value: " << *valuePtr << "\n";
    else cout << "Banana not found." << "\n";

    valuePtr = ht.searchValue("fig");
    if (valuePtr != nullptr) cout << "Found date with value: " << *valuePtr << "\n";
    else cout << "date not found." << "\n";

    // removeKey
    cout << "Delete banana.\n";
    ht.removeKey("banana");

    // searchValue *after* removeKey
    valuePtr = ht.searchValue("banana");
    if (valuePtr != nullptr) cout << "Found banana with value: " << *valuePtr << "\n";
    else cout << "Banana not found after removing." << "\n";

    // print hashTable
    cout << "\nHash table contents:\n";
    for (int i = 0; i < ht.capacity; i++) {
        ht.printAVL(ht.table[i]);
    }

    // add
    ht.add("mandarine", 12);
    ht.add("mandarine", 13);
    ht.add("lychee", 14);
    ht.add("lychee", 15);

    cout << "\nNew key-value:";
    string str = "abc";
    for (int i = 0; i < 20; i++){
        ht.add(str, i);
        str[2] = char(int(str[2]) + 1);
        str[1] = char(int(str[1]) - 1);
        cout << str << " ";
    } cout << "\n";

    // print hashTable
    cout << "\nHash table contents after adding:\n";
    for (int i = 0; i < ht.capacity; i++) {
        if (ht.table[i] != nullptr) cout << "\nTable id: " << i << "\n";
        ht.printAVL(ht.table[i]);
    }

    ht.release(); 
    return 0;
}      