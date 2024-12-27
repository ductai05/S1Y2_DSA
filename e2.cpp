#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int data) : val(data), left(nullptr), right(nullptr) {}
};

Node *insertNode(Node *root, int data)
{
    // insert like BST
    if (root == nullptr)
        return new Node(data);
    if (root->val == data)
        return root;
    if (data > root->val)
        root->right = insertNode(root->right, data);
    else if (data < root->val)
        root->left = insertNode(root->left, data);
    return root;
}

Node *minValueNode(Node *root)
{
    Node *cur = root;
    while (cur->left != nullptr)
    {
        cur = cur->left;
    }
    return cur;
}

Node *deleteNode(Node *root, int data)
{
    if (root == nullptr)
        return root;
    if (data > root->val)
        root->right = deleteNode(root->right, data);
    else if (data < root->val)
        root->left = deleteNode(root->left, data);
    else
    { // data = root->val
        if (root->left == nullptr || root->right == nullptr)
        { // 1 or 0 child
            Node *temp = root->left ? root->left : root->right;
            if (temp == nullptr)
            { // 0 child
                temp = root;
                root = nullptr;
            }
            else
            { // 1 child
                *root = *temp;
            }
            delete temp;
        }
        else
        {
            Node *minV = minValueNode(root->right);
            root->val = minV->val;
            root->right = deleteNode(root->right, minV->val);
        }
    }
    return root;
}

void levelOrder(Node *root, vector<Node *> &lvOrder)
{
    if (root == nullptr)
        return;
    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *cur = q.front();
        q.pop();

        lvOrder.push_back(cur);
        cout << cur->val << " ";
        if (cur->left != nullptr)
            q.push(cur->left);
        if (cur->right != nullptr)
            q.push(cur->right);
    }
}

void LNR(Node *root)
{
    if (root != nullptr)
    {
        LNR(root->left);
        cout << root->val << " ";
        LNR(root->right);
    }
}

int maxNode(Node *root)
{
    Node *cur = root;
    while (cur->right != nullptr)
    {
        cur = cur->right;
    }
    return cur->val;
}

Node *LCA(Node *root, int p, int q)
{
    if (root == nullptr)
        return nullptr;
    if (root->val == p || root->val == q)
        return root;

    Node *left = LCA(root->left, p, q);
    Node *right = LCA(root->right, p, q);

    if (left && right)
        return root;
    return left ? left : right;
}

int main()
{
    // read input
    freopen("e2.txt", "r", stdin);
    Node *root = nullptr;

    int n;
    cin >> n;

    int *keys = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> keys[i];
    }

    int p, q;
    cin >> p >> q;
    // insertNode
    for (int i = 0; i < n; i++)
    {
        root = insertNode(root, keys[i]);
    }

    // Test duyet
    vector<Node *> lvOrder;
    // cout << "levelOrder : ";
    levelOrder(root, lvOrder);
    cout << "\n";

    Node *lca = LCA(root, p, q);
    cout << lca->val;

    return 0;
}