#include "stdafx.h"
#include <math.h>
#define Pi 3.14159265359


class Rectangle 
{
	int _a;
	int _b;

public:

	int get_square();
	void set_a(int);
	void set_b(int);
};

class Circle
{
	int _r;

public:

	int get_square();
	void set_r(int);
};

class Segment
{
	int _x1;
	int _x2;
	int _y1;
	int _y2;

public:

	int get_length();
	void set_coords(int, int, int, int);

};

class Vector
{
	int _x;
	int _y;

public:

	void set_coords(int, int);
	void sum_vectors(Vector);
	int get_x();
	int get_y();

};

int Rectangle::get_square() 
{
	int S = _a * _b;
	return S;
}


void Rectangle::set_a(int a) 
{
	_a = a;
}

void Rectangle::set_b(int b) 
{
	_b = b;
}




void Circle::set_r(int r)
{
	_r = r;
}

int Circle::get_square()
{
	int S = _r * Pi;
	return S;
}

void Segment::set_coords(int x1, int x2, int y1, int y2)
{
	_x1 = x1;
	_x2 = x2;
	_y1 = y1;
	_y2 = y2;
}

int Segment::get_length()
{
	int x = _x2 - _x1;
	int y = _y2 - _y1;
	int length = sqrt(x*x + y*y);
	return length;
}

void Vector::set_coords(int x, int y)
{
	_x = x;
	_y = y;
}

void Vector::sum_vectors(Vector v)
{
	_x = _x + v.get_x();
	_y = _y + v.get_y();
}


int Vector::get_x()
{
	return _x;
}
int Vector::get_y()
{
	return _y;
}

int get_square(int a, int b) {
	return a*b;
}

float get_square(float a, float b) {
	return a*b;
}


int main()
{
	printf("%d\n", get_square(5, 4));
	printf("%f\n", get_square(float(5.5), float(4.2)));

	Rectangle my_rectangle;
	my_rectangle.set_a(2);
	my_rectangle.set_b(3);
	printf("Rectangle S = %d\n", my_rectangle.get_square());

	Circle my_circle;
	my_circle.set_r(10);
	printf("Circle S = %d\n", my_circle.get_square());

	Segment my_segment;
	my_segment.set_coords(5,10,12,18);
	printf("Segment L = %d\n", my_segment.get_length());

	Vector my_vector1;
	Vector my_vector2;

	my_vector1.set_coords(5, 11);
	my_vector2.set_coords(-2, 6);
	my_vector1.sum_vectors(my_vector2);
	printf("Vector 1 + Vector 2 = [%d;%d] \n", my_vector1.get_x(), my_vector1.get_y());
	return 0;

}
