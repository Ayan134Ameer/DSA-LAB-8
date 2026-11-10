#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

Node* createNode(int value)
{
    Node *n = new Node;
    n->data = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

Node* insert(Node *root, int value)
{
    if(root == NULL)
        return createNode(value);

    if(value < root->data)
        root->left = insert(root->left, value);
    else if(value > root->data)
        root->right = insert(root->right, value);

    return root;
}

Node* minimum(Node *root)
{
    while(root->left != NULL)
        root = root->left;

    return root;
}

Node* deleteNode(Node *root, int value)
{
    if(root == NULL)
        return NULL;

    if(value < root->data)
        root->left = deleteNode(root->left, value);
    else if(value > root->data)
        root->right = deleteNode(root->right, value);
    else
    {
        if(root->left == NULL)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == NULL)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        Node *temp = minimum(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

void inorder(Node *root)
{
    if(root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main()
{
    Node *root = NULL;

    int values[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};

    for(int i = 0; i < 9; i++)
        root = insert(root, values[i]);

    root = deleteNode(root, 20);
    cout << "After deleting 20: ";
    inorder(root);

    root = deleteNode(root, 30);
    cout << endl << "After deleting 30: ";
    inorder(root);

    root = deleteNode(root, 50);
    cout << endl << "After deleting 50: ";
    inorder(root);

    return 0;
}
