#include <iostream>

using namespace std;

const string strWeekDay[7] = { "Monday", "Tuesday", "Wednesday", "Thusday", "Friday", "Saturday", "Sunday" };

class WeekDay
{
private:
    int currentDay;

public:
    WeekDay()
    {
        currentDay = 1;
    }
    int getDay()const { return currentDay; }
    void print()
    {
        std::cout << "Value: " << currentDay << std::endl;
    }
    //префиксные операторы
    WeekDay& operator++ ()
    {
        if (currentDay + 1 > 7)
            currentDay = 1;
        else currentDay += 1;

        return *this;
    }
    WeekDay& operator-- ()
    {
        if (currentDay - 1 < 1)
            currentDay = 7;
        else currentDay -= 1;

        return *this;
    }
    // постфиксные операторы
    WeekDay operator++ (int)
    {
        WeekDay copy{ *this };

        if (currentDay + 1 > 7)
            currentDay = 1;
        else
            ++(*this);
        return copy;
    }
    WeekDay operator-- (int)
    {
        WeekDay copy{ *this };

        if (currentDay - 1 < 1)
            currentDay = 7;
        else
            --(*this);
        return copy;
    }
    //оператор вывода
    friend std::ostream& operator<<(std::ostream& stream, const WeekDay& weekDay)
    {
        stream << strWeekDay[weekDay.currentDay - 1] << endl;;
        return stream;
    }

};
int main()
{
    WeekDay day;
    day++;
    day.print();
    --day;
    day.print();
    cout << day;
    return 0;
}
