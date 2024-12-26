    ht.add("mango", 7);
    ht.add("lemon", 8);
    ht.add("watermelon", 9);
    ht.add("pineapple", 10);
    ht.add("passion fruit", 11);
    ht.add("mandarine", 12);
    ht.add("mandarine", 13);
    ht.add("lychee", 14);

    // print hashTable
    cout << "\nHash table contents after full:\n";
    for (int i = 0; i < ht.capacity; i++) {
        if (ht.table[i] != nullptr) {
            cout << "Key: " << ht.table[i]->key << " - Value: " << ht.table[i]->value << "\n";
        }
    }

    ht.release(); 
    return 0;
}