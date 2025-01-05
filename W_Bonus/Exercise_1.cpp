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
        hashNode(string k, int v) : key(k), value(v) {};
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
            delete table[i];
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
    void add(string key, int value){ //  Linear Probing
        unsigned int hashValue = hashFunction(key);
        for (int i = 0; i < capacity; i++){
            int id = (hashValue + i) % capacity;
            if (table[id] == nullptr){
                table[id] = new hashNode(key, value);
                return;
            } else if (table[id]->key == key){
                table[id]->value = value;
                return;
            } 
        }
        cout << "The table is full" << "\n";
        return;
    }

    // search element in the table. If not existed, return NULL.
    int* searchValue(string key){
        unsigned int hashValue = hashFunction(key);

        for (int i = 0; i < capacity; i++){
            int id = (hashValue + i) % capacity;
            if (table[id] != nullptr && table[id]->key == key){
                return &(table[id]->value);
            }
        }
        return nullptr;
    }

    // remove an element from the hash table.
    void removeKey(string key){
        int* idP = searchValue(key);
        if (idP == nullptr) {
            cout << "Not found this key to remove.\n";
            return;
        }
        unsigned int hashValue = hashFunction(key);
        for (int i = 0; i < capacity; i++){
            int id = (hashValue + i) % capacity;
            if (table[id] != nullptr && table[id]->key == key){
                delete table[id];
                table[id] = nullptr;
                return;
            }
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
        if (ht.table[i] != nullptr) {
            cout << "Key: " << ht.table[i]->key << " - Value: " << ht.table[i]->value << endl;
        }
    }

    // add
    ht.add("grape", 6);
    ht.add("mango", 7);
    ht.add("lemon", 8);
    ht.add("watermelon", 9);
    ht.add("pineapple", 10);
    ht.add("passion fruit", 11);
    ht.add("mandarine", 12);
    ht.add("mandarine", 13);
    ht.add("lychee", 14);

    // print hashTable
    cout << "\nHash table contents after adding:\n";
    for (int i = 0; i < ht.capacity; i++) {
        if (ht.table[i] != nullptr) {
            cout << "Key: " << ht.table[i]->key << " - Value: " << ht.table[i]->value << "\n";
        }
    }

    ht.release(); 
    return 0;
}