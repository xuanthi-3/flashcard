#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

//======================
// Thông tin Flashcard
//======================

struct Flashcard
{
    string word;
    string meaning;
    string example;

    int correct;
    int wrong;
    int priority;
};

//======================
// Node BST
//======================

struct Node
{
    Flashcard data;
    Node* left;
    Node* right;
};

//======================
// So sánh Priority Queue
//======================

struct ComparePriority
{
    bool operator()(Flashcard a, Flashcard b)
    {
        return a.priority > b.priority;
    }
};

//======================
// Khai báo hàm BST
//======================

Node* createNode(Flashcard x);

void insert(Node*& root, Flashcard x);

Node* search(Node* root, string word);

void removeNode(Node*& root, string word);

Node* findMin(Node* root);

void inorder(Node* root);

//======================
// Flashcard
//======================

Flashcard inputFlashcard();

void editFlashcard(Node* root);

void deleteFlashcard(Node*& root);

//======================
// Queue phiên học
//======================

void loadQueue(Node* root,
    queue<Flashcard>& q);

//======================
// Priority Queue
//======================

void buildPriority(Node* root,
    priority_queue<
    Flashcard,
    vector<Flashcard>,
    ComparePriority>& pq);

//======================
// Phiên học
//======================

void studySession(
    priority_queue<
    Flashcard,
    vector<Flashcard>,
    ComparePriority>& pq,
    stack<Flashcard>& undoStack);

//======================
// Undo
//======================

void undo(stack<Flashcard>& undoStack);

//======================
// Thống kê
//======================

void statistics(Node* root);

//======================
// Lưu file
//======================

void saveFile(Node* root,
    ofstream& out);

void saveToFile(Node* root);

//======================
// Đọc file
//======================

void loadFromFile(Node*& root);

#endif