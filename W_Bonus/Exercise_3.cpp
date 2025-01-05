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
        hashNode* next;
        hashNode(string k, int v) : key(k), value(v), next(nullptr) {}
    };

    int capacity;
    vector <hashNode *> table;

    // Functions ( Methods )
    // initialize an empty hash table with the given size.
    void init (unsigned int hashSize){
        capacity = hashSize;
        table.resize(capacity, nullptr);
    }

    // free all dynamically allocated memory in the hash table.
    void release(){
        for (int i = 0; i < capacity; i++){
            hashNode* cur = table[i];
            while (cur != nullptr){
                hashNode* temp = cur;
                cur = cur->next;
                delete temp;
            }
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
    void add(string key, int value){ //  Linked list
        unsigned int hashValue = hashFunction(key) % capacity;
        hashNode* newNode = new hashNode(key, value);

        if (table[hashValue] == nullptr){
            table[hashValue] = newNode;
            return;
        }
        hashNode* cur = table[hashValue];
        while(cur->next != nullptr){
            if (cur->key == key){
                cur->value = value; 
                return;
            }
            cur = cur->next;
        }
        if (cur->key == key){
            cur->value = value; 
            return;
        }
        cur->next = newNode;
        return;
    }

    // search element in the table. If not existed, return NULL.
    int* searchValue(string key){
        unsigned int hashValue = hashFunction(key) % capacity;

        hashNode* cur = table[hashValue];
        while(cur != nullptr){
            if (cur->key == key){
                int* res = new int (cur->value);
                return res;
            }
            cur = cur->next;
        }
        return nullptr;
    }

    // remove an element from the hash table.
    void removeKey(string key){
        unsigned int hashValue = hashFunction(key) % capacity;
        hashNode* cur = table[hashValue];
        hashNode* prev = nullptr;

        while (cur != nullptr){
            if (cur->key == key){
                if (prev == nullptr){
                    table[hashValue] = cur->next;
                } else {
                    prev->next = cur->next;
                }
                delete cur;
                return;
            }
            prev = cur;
            cur = cur->next;
        }
        cout << "Not found this key to remove.\n";
    }

    void printLL(hashNode* root){
        while (root != nullptr){
            cout << "Key: " << root->key << " - Value: " << root->value << "\n";
            root = root->next;
        }
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
        ht.printLL(ht.table[i]);
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
    }
    cout << "\n";

    // print hashTable
    cout << "\nHash table contents after adding:\n";
    for (int i = 0; i < ht.capacity; i++) {
        if (ht.table[i] != nullptr) cout << "\nTable id: " << i << "\n";
        ht.printLL(ht.table[i]);
    }

    ht.release(); 
    return 0;
}