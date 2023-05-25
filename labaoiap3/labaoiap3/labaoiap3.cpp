
#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

int tabs = 0;
int kol_vo = 0;


struct Branch
{
    int Data;
    Branch* LeftBranch;
    Branch* RightBranch;
};



void Add(int aData, Branch*& aBranch)
{
    if (!aBranch)
    {
        aBranch = new Branch;
        aBranch->Data = aData;
        aBranch->LeftBranch = 0;
        aBranch->RightBranch = 0;
        return;
    }
    else
        if (aBranch->Data > aData)
        {
            Add(aData, aBranch->LeftBranch);
        }
        else
        {
            Add(aData, aBranch->RightBranch);
        };
}

void print(Branch* aBranch)
{
    if (!aBranch) return;
    tabs += 5;

    print(aBranch->LeftBranch);
    for (int i = 0; i < tabs; i++) cout << " ";
    cout << aBranch->Data << endl;


    print(aBranch->RightBranch);

    tabs -= 5;
    return;
}



void chislo_yzlov(Branch* aBranch, map < int, int >& m, int level)
{
    m[level]++;
    if (aBranch->LeftBranch)  chislo_yzlov(aBranch->LeftBranch, m, level + 1);
    if (aBranch->RightBranch) chislo_yzlov(aBranch->RightBranch, m, level + 1);
}

void add_elem(int aData, Branch*& aBranch)
{
    if (!aBranch)
    {
        aBranch = new Branch;
        aBranch->Data = aData;
        aBranch->LeftBranch = 0;
        aBranch->RightBranch = 0;
        return;
    }
    else
    {
        if (aData < aBranch->Data) {
            add_elem(aData, aBranch->LeftBranch);
        }
        else if (aData > aBranch->Data) {
            add_elem(aData, aBranch->RightBranch);
        }
    }
}

void is_Empty(Branch*& aBranch)
{
    if (!aBranch)
    {
        cout << "Дерево пустое...";
    }
    else
    {
        cout << "Дерево не пустое...";
    }
}

void FreeTree(Branch* aBranch)
{
    if (!aBranch) return;
    FreeTree(aBranch->LeftBranch);
    FreeTree(aBranch->RightBranch);
    delete aBranch;
    return;
}

Branch* del_elem(Branch*& aBranch, int aData) {
    if (aBranch == NULL)
        return aBranch;

    if (aData == aBranch->Data) {

        Branch* tmp;
        if (aBranch->RightBranch == NULL)
            tmp = aBranch->LeftBranch;
        else {

            Branch* ptr = aBranch->RightBranch;
            if (ptr->LeftBranch == NULL) {
                ptr->LeftBranch = aBranch->LeftBranch;
                tmp = ptr;
            }
            else {

                Branch* pmin = ptr->LeftBranch;
                while (pmin->LeftBranch != NULL) {
                    ptr = pmin;
                    pmin = ptr->LeftBranch;
                }
                ptr->LeftBranch = pmin->RightBranch;
                pmin->LeftBranch = aBranch->LeftBranch;
                pmin->RightBranch = aBranch->RightBranch;
                tmp = pmin;
            }
        }

        delete aBranch;
        return tmp;
    }
    else if (aData < aBranch->Data)
        aBranch->LeftBranch = del_elem(aBranch->LeftBranch, aData);
    else
        aBranch->RightBranch = del_elem(aBranch->RightBranch, aData);
    return aBranch;
}

int main()
{
    setlocale(LC_ALL, "rus");
    Branch* Root = 0;
    int vel;
    int element;
    int k;

    cout << "Введите кол-во элементов для будущего дерева: ";
    cin >> vel;
    cout << endl;

    cout << "Проверим дерево на пустоту до его заполнения: " << endl;
    is_Empty(Root);
    cout << endl;

    for (int i = 0; i < vel; i++)
    {
        Add(rand() % 100, Root);
    }

    cout << "Проверим дерево на пустоту после его заполнения: " << endl;
    is_Empty(Root);
    cout << endl;

    cout << "Вывод бинарного дерева: " << endl;
    print(Root);
    cout << endl;
    map < int, int > m;
    chislo_yzlov(Root, m, 0);
    for (auto i : m)
    {
        cout << "На уровне " << i.first << " находится " << i.second << "узлов\n";
    }

    cout << "Добавим новый элемент в бинарное дерево:" << endl;
    cout << "Введите новый элемент: ";
    cin >> element;
    add_elem(element, Root);

    cout << "Вывод бинарного дерева: " << endl;
    print(Root);
    cout << endl;

        cout << "Удалим элемент из бинарного дерева:" << endl;
    cout << "Введите новый элемент: ";
    cin >> element;
    del_elem(Root, element);

    cout << "Вывод бинарного дерева: " << endl;
    print(Root);
    cout << endl;

    FreeTree(Root);
    cout << "Вся динамическая память очищена..." << endl;

    return 0;
}