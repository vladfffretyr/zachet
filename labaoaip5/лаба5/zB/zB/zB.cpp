#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int m = 20;
int table[1000] = { 0 };
string tableInfo[1000] = {};//15
string randFio[] = { "Vorobyov", "Denisenok", "Ageenko", "Kharetski", "Gorbach", "Sokolov", "Ermishin", "Malishevski", "chumachenco", "Samochvalov", "Frantskevich", "Babaika", "Vino", "viski", "Voskresenskii"};
int n;
int a[1000];
bool overflow;
int collisions;

int HashF(int num)
{
    return num % m;
}

void createTable()
{
    int i;
    for (i = 0; i < 1000; i++)
        table[i] = -1;

    collisions = 0;

    int h, h0, g;
    for (i = 0; i < n; i++)
    {
        h = HashF(a[i]);
        h0 = h;
        g = 1;
        while (1)
        {
            if (table[h] == a[i]) // Если число повторяется
                break;
            if (table[h] == -1)   // Если нашли пустое место в хэш-таблице
            {
                table[h] = a[i];
                tableInfo[h] = randFio[rand()%15];
                break;
            }
            if (g >= m)           // Если переполнение
            {
                overflow = true;
                return;
            }
            collisions++;
            h = h0 + g;
            if (h >= m)
                h -= m;
            g++;
        }
    }
    overflow = false;
}

void displayTable()
{
    cout << ("-----------------------------------------------------------\n");
    cout << ("| Хеш   |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |\n");
    cout << ("-----------------------------------------------------------\n");
    cout << ("| Год |");
    for (int i = 0; i < 10; i++)
        cout << setw(3) << table[i] << " |";
    cout << endl;
    cout << "------------------------------------------------------------\n";

    if (!overflow) cout << "Переполнения таблицы не было\n";
    else           cout << "Возникло переполнение таблицы\n";
    cout << "Количество коллизий: " << collisions << endl;
}


bool search(int num)
{
    int h = HashF(num);
    for (int g = h; g < m; ++h)
    {
        if (table[h] == num)
            cout << table[h] << "/" << tableInfo[h] <<"/"<< 2200+rand()%21 << endl;
            return true;
    }
    return false;
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    while (1) {
        cout << "Введите размер хеш-таблицы       : ";
        cin >> m;
        cout << "Введите количество исходных чисел: ";
        cin >> n;
        system("cls");
        for (int i = 0; i < n; i++)
        {
            a[i] = 1980+rand() % m + 12;
            cout << a[i] << ' ';
        }
        cout << endl;
        createTable();
        displayTable();


        int k;
        cout << ("Введите год для поиска: "); cin >> k;

        if (search(k))
            cout << endl;
        else
            cout << ("Объект был не найден\n");

        system("pause");
        system("cls");
    }
    return 0;
}