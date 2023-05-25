#include <iostream>
#include <queue>

using namespace std;

// объединение упорядоченных очередей
queue<int> mergeQueues(queue<int> q1, queue<int> q2) {
    queue<int> mergedQueue;

    // пока обе очереди не пусты
    while (!q1.empty() && !q2.empty()) {
        // выбираем минимальный элемент из очередей
        if (q1.front() <= q2.front()) {
            mergedQueue.push(q1.front());
            q1.pop();
        }
        else {
            mergedQueue.push(q2.front());
            q2.pop();
        }
    }

    // если первая очередь не пуста
    while (!q1.empty()) {
        mergedQueue.push(q1.front());
        q1.pop();
    }

    // если вторая очередь не пуста
    while (!q2.empty()) {
        mergedQueue.push(q2.front());
        q2.pop();
    }

    return mergedQueue;
}

int main() {
    queue<int> q1, q2;

    // заполнение очередей
    q1.push(2);
    q1.push(4);
    q1.push(6);
    q1.push(8);

    q2.push(1);
    q2.push(3);
    q2.push(5);
    q2.push(7);

    // объединение упорядоченных очередей
    queue<int> mergedQueue = mergeQueues(q1, q2);

    // вывод объединенной очереди
    while (!mergedQueue.empty()) {
        cout << mergedQueue.front() << " ";
        mergedQueue.pop();
    }

    return 0;
}