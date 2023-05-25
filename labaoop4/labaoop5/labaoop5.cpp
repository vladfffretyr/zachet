#include <iostream>
#include <cmath>

using namespace std;

class Vector2D {
protected:
    double x, y;

public:
    Vector2D(double x, double y) : x(x), y(y) {}

    double length() {
        return sqrt(x * x + y * y);
    }

    virtual void print() {
        cout << "(" << x << ", " << y << ")" << endl;
    }

    virtual void printLength() {
        cout << "Length: " << length() << endl;
    }
};

class Vector3D : public Vector2D {
private:
    double z;

public:
    Vector3D(double x, double y, double z) : Vector2D(x, y), z(z) {}

    double length() {
        return sqrt(x * x + y * y + z * z);
    }

    void print() override {
        cout << "(" << x << ", " << y << ", " << z << ")" << endl;
    }

    void printLength() override {
        cout << "Length: " << length() << endl;
    }
};

int main() {
    Vector2D v2d(3.0, 4.0);
    Vector3D v3d(3.0, 4.0, 5.0);

    // Полиморфизм: вызываем методы print() и printLength() для объектов разных классов,
    // но с одним и тем же типом указателя.
    Vector2D* pv = &v2d;
    pv->print();
    pv->printLength();

    pv = &v3d;
    pv->print();
    pv->printLength();

    return 0;
}
