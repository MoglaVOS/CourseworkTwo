#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

struct Node
{
    int value;
    Node* left;
    Node* right;
};

Node* search(int value, Node* root) {
    if (root != nullptr)
    {
        if (value == root->value)
            return root;
        if (value < root->value)
            return search(value, root->left);
        else
            return search(value, root->right);
    }
    else return nullptr;
}

Node* create(int value) {
    Node* root = new Node;
    root->left = nullptr;
    root->right = nullptr;
    root->value = value;
    return root;
}

Node* getMin(Node* root) {
    while (root->left)
        root = root->left;
    return root;
}

Node* deleteB(int value, Node* root) {
    if (root == nullptr)
        return nullptr;
    if (value < root->value)
        root->left = deleteB(value, root->left);
    else if (value > root->value)
        root->right = deleteB(value, root->right);
    else {
        if (root->left == nullptr && root->right == nullptr)
            root = nullptr;
        else if (root->left == nullptr || root->right == nullptr)
            root = root->left ? root->left : root->right;
        else {
            Node* minnode = getMin(root->right);
            root->value = minnode->value;
            root->right = deleteB(minnode->value, root->right);
        }
    }
    return root;
}

void insert(int value, Node* root) {
    if (!root) return;
    if (value < root->value)
    {
        if (root->left != nullptr)
            insert(value, root->left);
        else {
            root->left = new Node;
            root->left->value = value;
            root->left->left = nullptr;
            root->left->right = nullptr;
        }
    } else if (value >= root->value) {
        if (root->right != nullptr)
            insert(value, root->right);
        else {
            root->right = new Node;
            root->right->value = value;
            root->right->left = nullptr;
            root->right->right = nullptr;
        }
    }
}

void destroy(Node* root) {
    if(root!=nullptr) {
        destroy(root->left);
        destroy(root->right);
        delete root;
    }
}

void print(Node* root, string indent = "", bool isLeft = false){
    if(root == nullptr){
        return;
    }
    cout << indent;
    if(isLeft){
        cout << "*-- ";
        indent += "|   ";
    }
    else{
        cout << "`-- ";
        indent += "    ";
    }

    cout << root->value << endl;

    print(root->left, indent, true);
    print(root->right, indent, false);
}

void add(int value, Node*& root) {
    if (root == nullptr)
        root = create(value);
    else
        insert(value, root);
}

void strw(Node* root) {
    if(root){
        std::cout << root->value << ' ';
        strw(root->left);
        strw(root->right);
    }
}

void revw(Node* root) {
    if(root){
        revw(root->left);
        revw(root->right);
        std::cout << root->value << ' ';
    }
}

void symw(Node* root) {
    if(root){
        symw(root->left);
        std::cout << root->value << ' ';
        symw(root->right);
    }
}

void walk(Node*& root) {
    int choice;
    cout <<
         "Walk:\n"
         "1. Straight walk\n"
         "2. Reverse walk\n"
         "3. Symmetrical walk\n\n";
    cout << "Type a number to continue: ";
    cin >> choice;
    switch(choice) {
        case 1:
            strw(root);
            cout << endl;
            break;
        case 2:
            revw(root);
            cout << endl;
            break;
        case 3:
            symw(root);
            cout << endl;
            break;
    }
}

void fill(Node*& root) {
    system("cls");
    cout <<
         "Fill:\n"
         "1. Create with random values\n"
         "2. Create with manual values\n\n";
    int choice;
    cout << "Type a number to continue: ";
    cin >> choice;
    switch(choice) {
        case 1: {
            destroy(root);
            root = nullptr;
            int n;
            cout << "Input value: ";
            cin >> n;
            for(int i = 0; i < n; i++){
                int r = rand() % 200 - 99;
                add(r, root);
            }
            break;
        }
        case 2: {
            destroy(root);
            root = nullptr;
            cout << "Input numbers:\n";
            int val;
            while (true) {
                cin >> val;
                if (cin.fail())
                    break;
                add(val, root);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}

void menu() {
    Node* bt = nullptr;
    while (true) {
        system("cls");
        cout <<
             "Choose a category:\n"
             "1. Create Binary Tree\n"
             "2. Print Binary Tree\n"
             "3. Insert element into Binary Tree\n"
             "4. Delete element from Binary Tree\n"
             "5. Find element in Binary Tree\n"
             "6. Binary Tree walk\n\n";
        int choice;
        cout << "Type a number to continue: ";
        cin >> choice;
        cout << endl;
        switch (choice) {
            case 0:
                return;
            case 1:
                fill(bt);
                break;
            case 2:
                print(bt);
                break;
            case 3: {
                int n;
                cout << "Input a number to insert: ";
                cin >> n;
                auto t1 = steady_clock::now();
                add(n, bt);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                cout << "Inserted in " << result.count() << " nanoseconds." << endl;
                break;
            }
            case 4: {
                int n;
                cout << "Input a number to delete: ";
                cin >> n;
                auto t1 = steady_clock::now();
                deleteB(n, bt);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                cout << "Deleted in " << result.count() << " nanoseconds." << endl;
                break;
            }
            case 5: {
                int n;
                cout << "Input a number to search: ";
                cin >> n;
                auto t1 = steady_clock::now();
                Node* node = search(n, bt);
                auto t2 = steady_clock::now();
                auto result = duration_cast<nanoseconds>(t2 - t1);
                if (node != nullptr)
                    cout << "Element found: " << node->value << " (" << result.count() << " nanoseconds)" << endl;
                else
                    cout << "Element not found (" << result.count() << " nanoseconds)" << endl;
                break;
            }
            case 6:
                walk(bt);
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
        system("pause");
    }
}

int main()
{
    srand(time(nullptr));
    while (true) {
        system("cls");
        cout <<
             "Choose tree type from below:\n"
             "0. Exit\n"
             "1. Binary Search Tree\n\n";
        int choice;
        cout << "Type a number to continue: ";
        cin >> choice;
        cout << endl;
        switch (choice) {
            case 0:
                return 0;
            case 1:
                menu();
                break;
            default:
                cout << "\nCategory with number " << choice << " does not exist." << endl;
                break;
        }
    }
}