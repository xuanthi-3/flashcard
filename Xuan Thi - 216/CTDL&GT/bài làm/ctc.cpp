#include "kb.h"

int main()
{
    Node* root = NULL;

    queue<Flashcard> q;

    priority_queue<
        Flashcard,
        vector<Flashcard>,
        ComparePriority> pq;

    stack<Flashcard> undoStack;

    loadFromFile(root);

    int choice;

    do
    {
        cout << "\n========== MENU ==========\n";
        cout << "1. Them flashcard\n";
        cout << "2. Xoa flashcard\n";
        cout << "3. Sua flashcard\n";
        cout << "4. Tim kiem tu\n";
        cout << "5. Hien thi tat ca\n";
        cout << "6. Tao Queue hoc\n";
        cout << "7. Tao Priority Queue\n";
        cout << "8. Phien hoc\n";
        cout << "9. Undo\n";
        cout << "10. Thong ke\n";
        cout << "11. Luu file\n";
        cout << "0. Thoat\n";
        cout << "==========================\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Flashcard x = inputFlashcard();
            insert(root, x);
            break;
        }

        case 2:
        {
            deleteFlashcard(root);
            break;
        }

        case 3:
        {
            editFlashcard(root);
            break;
        }

        case 4:
        {
            string word;

            cin.ignore();

            cout << "Nhap tu can tim: ";
            getline(cin, word);

            Node* p = search(root, word);

            if (p == NULL)
            {
                cout << "Khong tim thay!\n";
            }
            else
            {
                cout << "\nWord: " << p->data.word << endl;
                cout << "Meaning: " << p->data.meaning << endl;
                cout << "Example: " << p->data.example << endl;
                cout << "Correct: " << p->data.correct << endl;
                cout << "Wrong: " << p->data.wrong << endl;
                cout << "Priority: " << p->data.priority << endl;
            }

            break;
        }

        case 5:
        {
            inorder(root);
            break;
        }

        case 6:
        {
            while (!q.empty())
                q.pop();

            loadQueue(root, q);

            cout << "Da tao Queue!\n";
            break;
        }

        case 7:
        {
            while (!pq.empty())
                pq.pop();

            buildPriority(root, pq);

            cout << "Da tao Priority Queue!\n";
            break;
        }

        case 8:
        {
            studySession(pq, undoStack);
            break;
        }

        case 9:
        {
            undo(undoStack);
            break;
        }

        case 10:
        {
            statistics(root);
            break;
        }

        case 11:
        {
            saveToFile(root);
            cout << "Da luu file!\n";
            break;
        }

        case 0:
        {
            saveToFile(root);
            cout << "Tam biet!\n";
            break;
        }

        default:
            cout << "Lua chon khong hop le!\n";
}

    } while (choice != 0);

    return 0;
}
