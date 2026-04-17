#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Node {
    string data;
    Node* prev;
    Node* next;
    Node* rand;
};

int main()
{
    // создаём входной файл
    ofstream create("inlet.in");
    create << "apple;2" << endl;
    create << "banana;-1" << endl;
    create << "carrot;1" << endl;
    create.close();

    // читаем входной файл
    ifstream fin("inlet.in");
    if (!fin.is_open()) {
        cout << "File not found!" << endl;
        return 1;
    }

    vector<string> dataList;
    vector<int> randList;
    string line;

    while (getline(fin, line)) {
        int pos = line.find(';');
        string data = line.substr(0, pos);
        int randIndex = stoi(line.substr(pos + 1));
        dataList.push_back(data);
        randList.push_back(randIndex);
    }
    fin.close();

    // создаём узлы
    vector<Node*> nodes;
    for (int i = 0; i < dataList.size(); i++) {
        Node* n = new Node();
        n->data = dataList[i];
        n->prev = nullptr;
        n->next = nullptr;
        n->rand = nullptr;
        nodes.push_back(n);
    }

    // связываем prev/next
    for (int i = 0; i < nodes.size(); i++) {
        if (i > 0) nodes[i]->prev = nodes[i - 1];
        if (i < nodes.size() - 1) nodes[i]->next = nodes[i + 1];
    }

    // связываем rand
    for (int i = 0; i < nodes.size(); i++) {
        if (randList[i] != -1) {
            nodes[i]->rand = nodes[randList[i]];
        }
    }

    // выводим список
    cout << "Original list:" << endl;
    for (int i = 0; i < nodes.size(); i++) {
        cout << i << ". data=" << nodes[i]->data;
        if (nodes[i]->rand != nullptr) {
            cout << " rand=" << nodes[i]->rand->data;
        }
        else {
            cout << " rand=nullptr";
        }
        cout << endl;
    }

    // === СЕРИАЛИЗАЦИЯ ===
    ofstream fout("outlet.out", ios::binary);
    int count = nodes.size();
    fout.write((char*)&count, sizeof(count));

    for (int i = 0; i < nodes.size(); i++) {
        int len = nodes[i]->data.size();
        fout.write((char*)&len, sizeof(len));
        fout.write(nodes[i]->data.c_str(), len);

        int randIndex = -1;
        if (nodes[i]->rand != nullptr) {
            for (int j = 0; j < nodes.size(); j++) {
                if (nodes[i]->rand == nodes[j]) {
                    randIndex = j;
                    break;
                }
            }
        }
        fout.write((char*)&randIndex, sizeof(randIndex));
    }
    fout.close();
    cout << "\nSerialized to outlet.out!" << endl;

    // === ДЕСЕРИАЛИЗАЦИЯ ===
    ifstream bin("outlet.out", ios::binary);
    int count2;
    bin.read((char*)&count2, sizeof(count2));

    vector<Node*> nodes2;
    vector<int> randList2;

    for (int i = 0; i < count2; i++) {
        int len;
        bin.read((char*)&len, sizeof(len));
        string data(len, ' ');
        bin.read(&data[0], len);

        int ri;
        bin.read((char*)&ri, sizeof(ri));

        Node* n = new Node();
        n->data = data;
        n->prev = nullptr;
        n->next = nullptr;
        n->rand = nullptr;
        nodes2.push_back(n);
        randList2.push_back(ri);
    }
    bin.close();

    // связываем prev/next
    for (int i = 0; i < nodes2.size(); i++) {
        if (i > 0) nodes2[i]->prev = nodes2[i - 1];
        if (i < nodes2.size() - 1) nodes2[i]->next = nodes2[i + 1];
    }

    // связываем rand
    for (int i = 0; i < nodes2.size(); i++) {
        if (randList2[i] != -1) {
            nodes2[i]->rand = nodes2[randList2[i]];
        }
    }

    // проверяем
    cout << "\nDeserialized from outlet.out:" << endl;
    for (int i = 0; i < nodes2.size(); i++) {
        cout << i << ". data=" << nodes2[i]->data;
        if (nodes2[i]->rand != nullptr) {
            cout << " rand=" << nodes2[i]->rand->data;
        }
        else {
            cout << " rand=nullptr";
        }
        cout << endl;
    }

    // очистка памяти
    for (int i = 0; i < nodes.size(); i++) delete nodes[i];
    for (int i = 0; i < nodes2.size(); i++) delete nodes2[i];

    return 0;
}