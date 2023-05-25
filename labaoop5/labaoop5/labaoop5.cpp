#include <iostream> 
using namespace std;

class Body
{
protected:
	enum shape
	{
		shar,
		prisma,
		parallelepiped,
		cub,
		piramida,
		conus,
		cylinder
	};

	shape body_shape{ shar };

	double r = 0, h = 0, a = 0, b = 0, P = 0;
	double s_osn = 0, s_bok = 0, s_full = 0, v = 0, p = 0;

	enum material
	{
		metal,
		wood,
		plastic,
		cardboard
	};

	material body_material{ metal };

public:
	virtual double calculate_s_osn() = 0;
	virtual double calculate_s_bok() = 0;
	virtual double calculate_s_full() = 0;
	virtual double calculate_v() = 0;
	virtual double calculate_p() = 0;
	virtual double increase_body() = 0;
	virtual double reduction_body() = 0;
	virtual void show() = 0;
};

class Cub : public Body
{

public:

	Cub(double a, int mat)
	{
		body_shape = cub;
		this->a = a;
		body_material = static_cast<material> (mat);
	}
	virtual double calculate_s_osn() override
	{
		s_osn = a * a;
		return s_osn;
	}
	virtual double calculate_s_bok() override
	{
		s_bok = 4 * (a * a);
		return s_bok;
	}
	virtual double calculate_s_full() override
	{
		s_full = 2 * s_osn + s_bok;
		return s_full;
	}
	virtual double calculate_v() override
	{
		v = a * a * a;
		return v;
	}
	virtual double calculate_p() override
	{
		switch (body_material)
		{
		case Body::metal:
			p = v * 7, 86;
			return p;

		case Body::wood:
			p = v * 0.6;
			return p;

		case Body::plastic:
			p = v * 1;
			return p;

		case Body::cardboard:
			p = v * 0.4;
			return p;

		default:
			cout << "ОШИБКА " << endl;
			break;
		}
	}
	virtual void show() override
	{
		cout << "Куб " << endl;

		switch (body_material)
		{
		case Body::metal:
			cout << "Металлический " << endl;
			break;
		case Body::wood:
			cout << "Деревянный " << endl;
			break;
		case Body::plastic:
			cout << "Пластиковый " << endl;
			break;
		case Body::cardboard:
			cout << "Картонный " << endl;
			break;
		default:
			cout << "ОШИБКА " << endl;
			break;
		}

		cout << "Площадь грани = " << s_osn << endl
			<< "Площадь поверхности тела = " << s_full << endl
			<< "Вес = " << p << endl;
	}

	virtual double increase_body() override
	{
		return 0;
	}

	virtual double reduction_body() override
	{
		return 0;
	}
};

int main()
{
	setlocale(LC_ALL, "");

	Cub c1(3, 0);
	c1.calculate_s_osn();
	c1.calculate_s_bok();
	c1.calculate_s_full();
	c1.calculate_v();
	c1.calculate_p();
	c1.show();
}

