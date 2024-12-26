#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

void printQueue(Node* head){
    Node* cur = head;
    while(cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << "\n";
}

int sizeQueue(Node* head){
    int size = 0;
    Node* cur = head;
    while(cur != nullptr){
        size+= 1;
        cur = cur->next;
    }
    return size;
}

Node* dequeue(Node* head){
    if (head == nullptr) return head;
    head = head->next;
    return head; 
}

Node* enqueue(Node* head, int data){
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

void front(Node* head){
    if (head == nullptr) cout << "NULL\n";
    else cout << head->data << "\n";
}

int main(){
    Node* queue = nullptr;
    queue = enqueue(queue, 0);
    queue = enqueue(queue, 12);
    queue = enqueue(queue, 34);
    queue = enqueue(queue, 56);
    printQueue(queue);
    queue = dequeue(queue);
    printQueue(queue);
    front(queue);
}