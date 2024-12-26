#include <iostream>
#include <unordered_set>
using namespace std;

struct Node{
    int data;
    Node* next;
};

void printLL(Node* head){
    Node* cur = head;
    while(cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << "\n";
}

int sizeLL(Node* head){
    int size = 0;
    Node* cur = head;
    while(cur != nullptr){
        size+= 1;
        cur = cur->next;
    }
    return size;
}

Node* addHead(Node* head, int data){
    Node* temp = new Node;
    temp->data = data;
    temp->next = head;
    return temp;
}

Node* addTail(Node* head, int data){
    Node* temp = new Node;
    temp->data = data;
    temp->next = nullptr;
    
    Node* cur = head;
    if (head != nullptr){
        while(cur->next != nullptr) cur = cur->next;
        cur->next = temp;
        return head;
    }
    return temp;
}

Node* removeHead(Node* head){
    if (head == nullptr) return head;
    head = head->next;
    return head; 
}

Node* removeTail(Node* head){
    if (head == nullptr) return head;
    else if (head->next == nullptr) return head->next;
    Node* cur = head;
    while (cur->next->next != nullptr) cur = cur->next;
    cur->next = cur->next->next;
    return head;
}

Node* removeDuplicate(Node* head){
    unordered_set<int> set;
    Node* cur = head;
    Node* pre = nullptr;
    while (cur != nullptr) {
        if (set.find(cur->data) != set.end()) {
            pre->next = cur->next;
            Node* temp = cur;
            cur = cur->next;
            delete temp;
        } else {
            set.insert(cur->data);
            pre = cur;
            cur = cur->next;
        }
    }
    return head;
}

int main(){
    Node* head = nullptr; 
    head = addTail(head, 3);
    head = addHead(head, 2);
    head = addHead(head, 1);
    head = addTail(head, 4);
    head = addTail(head, 5);
    head = addTail(head, 3);
    head = addTail(head, 5);
    head = addTail(head, 6);
    printLL(head);
    cout << sizeLL(head) << "\n";
    head = removeDuplicate(head);
    printLL(head);
}