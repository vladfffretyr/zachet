#include <iostream>
#include <stack>
#include <random>
using namespace std;
int main() {
    cout << " size: ";
    size_t size;
    cin >> size;
    stack<int> box;
    size_t i = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> uid(-100, 100);
    do box.push(uid(gen)); while (++i < size);
    cout << "\n Yuor stack:\n\n";
    stack<int> inv;
    while (!box.empty()) {
        auto top = box.top();
        cout << '\t' << top << '\n';
        inv.push(top);
        box.pop();
    }
    stack<int> neg;
    stack<int> pos;
    while (!inv.empty()) {
        auto top = inv.top();
        if (top < 0) neg.push(top);
        else pos.push(top);
        inv.pop();
    }
    cout << "\n Stack(+):\n\n";
    while (!pos.empty()) {
        cout << '\t' << pos.top() << '\n';
        pos.pop();
    }
    cout << "\n Stack(-):\n\n";
    while (!neg.empty()) {
        cout << '\t' << neg.top() << '\n';
        neg.pop();
    }
    cin.ignore();
    cin.get();
}