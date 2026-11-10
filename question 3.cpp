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

void displayRange(Node *root, int L, int R)
{
    if(root == NULL)
        return;

    if(root->data > L)
        displayRange(root->left, L, R);

    if(root->data >= L && root->data <= R)
        cout << root->data << " ";

    if(root->data < R)
        displayRange(root->right, L, R);
}

int countRange(Node *root, int L, int R)
{
    if(root == NULL)
        return 0;

    if(root->data >= L && root->data <= R)
        return 1 + countRange(root->left, L, R) + countRange(root->right, L, R);

    if(root->data < L)
        return countRange(root->right, L, R);

    return countRange(root->left, L, R);
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

Node* deleteOutsideRange(Node *root, int L, int R)
{
    if(root == NULL)
        return NULL;

    root->left = deleteOutsideRange(root->left, L, R);
    root->right = deleteOutsideRange(root->right, L, R);

    if(root->data < L)
        return deleteNode(root, root->data);

    if(root->data > R)
        return deleteNode(root, root->data);

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

    int values[] = {50, 25, 75, 10, 30, 60, 90, 20, 40, 70, 80};

    for(int i = 0; i < 11; i++)
        root = insert(root, values[i]);

    int L = 25;
    int R = 70;

    cout << "IDs in range: ";
    displayRange(root, L, R);

    cout << endl << "Count: " << countRange(root, L, R);

    root = deleteOutsideRange(root, L, R);

    cout << endl << "After deleting outside range: ";
    inorder(root);

    return 0;
}
