#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

void printStack(Node* head){
    Node* cur = head;
    while(cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << "\n";
}

int sizeStack(Node* head){
    int size = 0;
    Node* cur = head;
    while(cur != nullptr){
        size+= 1;
        cur = cur->next;
    }
    return size;
}

Node* push(Node* head, int data){
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

Node* pop(Node* head){
    if (head == nullptr) return head;
    else if (head->next == nullptr) return head->next;
    Node* cur = head;
    while (cur->next->next != nullptr) cur = cur->next;
    cur->next = cur->next->next;
    return head;
}

void top(Node* head){
    if (head == nullptr) cout << "NULL\n";
    else cout << head->data << "\n";
}

int main(){
    Node* stack = nullptr;
    stack = push(stack, 5);
    stack = push(stack, 6);
    stack = push(stack, 7);
    stack = push(stack, 8);
    stack = push(stack, 18);
    printStack(stack);
    stack = pop(stack);
    printStack(stack);
    top(stack);
}