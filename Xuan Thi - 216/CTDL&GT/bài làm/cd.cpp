#include "kb.h"

//======================
// Tạo node
//======================

Node* createNode(Flashcard x)
{
    Node* p = new Node;

    p->data = x;
    p->left = NULL;
    p->right = NULL;

    return p;
}

//======================
// Thêm BST
//======================

void insert(Node*& root, Flashcard x)
{
    if (root == NULL)
    {
        root = createNode(x);
        return;
    }

    if (x.word < root->data.word)
        insert(root->left, x);

    else if (x.word > root->data.word)
        insert(root->right, x);
}

//======================
// Tìm kiếm
//======================

Node* search(Node* root, string word)
{
    if (root == NULL)
        return NULL;

    if (word == root->data.word)
        return root;

    if (word < root->data.word)
        return search(root->left, word);

    return search(root->right, word);
}

//======================
// Node nhỏ nhất
//======================

Node* findMin(Node* root)
{
    while (root->left != NULL)
        root = root->left;

    return root;
}

//======================
// Xóa node
//======================

void removeNode(Node*& root, string word)
{
    if (root == NULL)
        return;

    if (word < root->data.word)
        removeNode(root->left, word);

    else if (word > root->data.word)
        removeNode(root->right, word);

    else
    {
        if (root->left == NULL)
        {
            Node* temp = root;
            root = root->right;
            delete temp;
        }

        else if (root->right == NULL)
        {
            Node* temp = root;
            root = root->left;
            delete temp;
        }

        else
        {
            Node* temp = findMin(root->right);

            root->data = temp->data;

            removeNode(root->right, temp->data.word);
        }
    }
}

//======================
// Duyệt LNR
//======================

void inorder(Node* root)
{
    if (root == NULL)
        return;

    inorder(root->left);

    cout << "----------------------\n";
    cout << "Word: " << root->data.word << endl;
    cout << "Meaning: " << root->data.meaning << endl;
    cout << "Example: " << root->data.example << endl;
    cout << "Correct: " << root->data.correct << endl;
    cout << "Wrong: " << root->data.wrong << endl;
    cout << "Priority: " << root->data.priority << endl;

    inorder(root->right);
}

//======================
// Nhập flashcard
//======================

Flashcard inputFlashcard()
{
    Flashcard x;

    cin.ignore();

    cout << "Nhap tu: ";
    getline(cin, x.word);

    cout << "Nhap nghia: ";
    getline(cin, x.meaning);

    cout << "Nhap vi du: ";
    getline(cin, x.example);

    x.correct = 0;
    x.wrong = 0;
    x.priority = 1;

    return x;
}
//======================
// Sửa Flashcard
//======================

void editFlashcard(Node* root)
{
    string word;

    cin.ignore();

    cout << "Nhap tu can sua: ";
    getline(cin, word);

    Node* p = search(root, word);

    if (p == NULL)
    {
        cout << "Khong tim thay!\n";
        return;
    }

    cout << "Nhap nghia moi: ";
    getline(cin, p->data.meaning);

    cout << "Nhap vi du moi: ";
    getline(cin, p->data.example);

    cout << "Da cap nhat!\n";
}

//======================
// Xoa Flashcard
//======================

void deleteFlashcard(Node*& root)
{
    string word;

    cin.ignore();

    cout << "Nhap tu can xoa: ";
    getline(cin, word);

    removeNode(root, word);

    cout << "Da xoa!\n";
}

//======================
// Dua BST vao Queue
//======================

void loadQueue(Node* root, queue<Flashcard>& q)
{
    if (root == NULL)
        return;

    loadQueue(root->left, q);

    q.push(root->data);

    loadQueue(root->right, q);
}

//======================
// Dua BST vao Priority Queue
//======================

void buildPriority(
    Node* root,
    priority_queue<
    Flashcard,
    vector<Flashcard>,
    ComparePriority>& pq)
{
    if (root == NULL)
        return;

    buildPriority(root->left, pq);

    pq.push(root->data);

    buildPriority(root->right, pq);
}
//======================
// Phiên học
//======================

void studySession(
    priority_queue<
    Flashcard,
    vector<Flashcard>,
    ComparePriority>& pq,
    stack<Flashcard>& undoStack)
{
    while (!pq.empty())
    {
        Flashcard x = pq.top();
        pq.pop();

        cout << "\n=====================\n";
        cout << "Word: " << x.word << endl;
        cout << "Meaning: " << x.meaning << endl;
        cout << "Example: " << x.example << endl;

        int choice;

        cout << "\n1. Dung\n";
        cout << "2. Sai\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;

        if (choice == 0)
            break;

        undoStack.push(x);

        if (choice == 1)
        {
            x.correct++;
            x.priority++;
        }
        else
        {
            x.wrong++;
            if (x.priority > 1)
                x.priority--;
        }

        pq.push(x);
    }
}

//======================
// Undo
//======================

void undo(stack<Flashcard>& undoStack)
{
    if (undoStack.empty())
    {
        cout << "Khong co thao tac de Undo!\n";
        return;
    }

    Flashcard x = undoStack.top();
    undoStack.pop();

    cout << "Da Undo tu: " << x.word << endl;
}

//======================
// Thong ke
//======================

void statistics(Node* root)
{
    if (root == NULL)
        return;

    statistics(root->left);

    cout << "\n----------------------\n";
    cout << root->data.word << endl;
    cout << "Correct: " << root->data.correct << endl;
    cout << "Wrong: " << root->data.wrong << endl;

    statistics(root->right);
}

//======================
// Luu file
//======================

void saveFile(Node* root, ofstream& out)
{
    if (root == NULL)
        return;

    saveFile(root->left, out);

    out << root->data.word << "|"
        << root->data.meaning << "|"
        << root->data.example << "|"
        << root->data.correct << "|"
        << root->data.wrong << "|"
        << root->data.priority << endl;

    saveFile(root->right, out);
}

void saveToFile(Node* root)
{
    ofstream out("flashcard.txt");

    if (!out)
    {
        cout << "Khong mo duoc file!\n";
        return;
    }

    saveFile(root, out);

    out.close();
}

//======================
// Doc file
//======================

void loadFromFile(Node*& root)
{
    ifstream in("flashcard.txt");

    if (!in)
        return;

    while (!in.eof())
    {
        Flashcard x;

        getline(in, x.word, '|');
        if (x.word == "")
            break;

        getline(in, x.meaning, '|');
        getline(in, x.example, '|');

        string s;

        getline(in, s, '|');
        x.correct = stoi(s);

        getline(in, s, '|');
        x.wrong = stoi(s);

        getline(in, s);
        x.priority = stoi(s);

        insert(root, x);
    }

    in.close();
}
