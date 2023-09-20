﻿#include<iostream>
#include<Windows.h>
using namespace std;

//enum (Enumeration - Пречисление) - это набор именованных целочисленных констрант.
enum Color
{
	red = 0x000000FF,
	green = 0x0000FF00,
	blue = 0x00FF0000,
	yellow = 0x0000FFFF,
	purple = 0x00FF00FF,
	white = 0x00FFFFFF
};

#define SHAPE_TAKE_PARAMETERS Color color, int start_x, int start_y, int line_width
#define SHAPE_GIVE_PARAMETERS color, start_x, start_y, line_width
class Shape
{
	static const int MIN_START_X = 10;
	static const int MAX_START_X = 800;

	static const int MIN_START_Y = 10;
	static const int MAX_START_Y = 500;

	static const int MIN_LINE_WIDTH = 1;
	static const int MAX_LINE_WIDTH = 30;
protected:
	Color color;
	int start_x;
	int start_y;
	int line_width;
public:
	Color get_color()const
	{
		return color;
	}
	int get_start_x()const
	{
		return start_x;
	}
	int get_start_y()const
	{
		return start_y;
	}
	int get_line_width()const
	{
		return line_width;
	}
	void set_color(Color color)
	{
		this->color = color;
	}
	void set_start_x(int start_x)
	{
		if (start_x < MIN_START_X)start_x = MIN_START_X;
		if (start_x > MAX_START_X)start_x = MAX_START_X;
		this->start_x = start_x;
	}
	void set_start_y(int start_y)
	{
		if (start_y < MIN_START_Y) start_y = MIN_START_Y;
		if (start_y > MAX_START_Y) start_y = MAX_START_Y;
		this->start_y = start_y;
	}
	void set_line_width(int line_width)
	{
		if (line_width < MIN_LINE_WIDTH)line_width = MIN_LINE_WIDTH;
		if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
		this->line_width = line_width;
	}
	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
	Shape(SHAPE_TAKE_PARAMETERS)
	{
		set_color(color);
		set_start_x(start_x);
		set_start_y(start_y);
		set_line_width(line_width);
	}
	~Shape() {}
};

class Square :public Shape
{
	double side;
public:
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		this->side = side;
	}
	Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
	{
		set_side(side);
	}
	~Square() {}

	double get_area()const override
	{
		return side * side;
	}
	double get_perimeter()const override
	{
		return side * 4;
	}
	void draw()const override
	{
		/*for (int i = 0; i < side; i++)
		{
			for (int i = 0; i < side; i++)
			{
				cout << "* ";
			}
			cout << endl;
		}*/

		HWND hwnd = GetConsoleWindow();	//1) Получаем окно консоли:
		HDC hdc = GetDC(hwnd);			//2) Получаем контекст устройства для окна консоли

		HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//3) Создаем карандаш, который рисует контур фигуры
		HBRUSH hBrush = CreateSolidBrush(color);	//4) Создаем кисть, она рисует заливку фигуры

		//5) Выбираем, чем и на чем рисовать. Рисуют всегда на контексте устройства, для рисования используем карандаш и кисть.
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		//6) Рисуем прямоугольник. Для его рисования нужно указать координаты верхнего-левого и правого-нижнего усгла
		Rectangle(hdc, start_x, start_y, start_x + side, start_y + side);

		//7) Удаляем все созданные инструменты:
		DeleteObject(hBrush);
		DeleteObject(hPen);

		//8) Освобождаем контекст устройства
		ReleaseDC(hwnd, hdc);

		//Контекст устройства и все инструменты занимают ресурсы, а ресурсы нужно освобождать.
	}
};
class Rectangle :public Shape
{
	double side_a;
	double side_b;
public:
	double get_side_a()const
	{
		return side_a;
	}
	double get_side_b()const
	{
		return side_b;
	}
	void set_side_a(double side_a)
	{
		this->side_a = side_a;
	}
	void set_side_b(double side_b)
	{
		this->side_b = side_b;
	}
	double get_area()const override
	{
		return side_a * side_b;
	}
	double get_perimeter()const override
	{
		return (side_a + side_b) * 2;
	}
	void draw()const override
	{
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		HPEN hPen = CreatePen(PS_SOLID, line_width, color);
		HBRUSH hBrush = CreateSolidBrush(color);

		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		::Rectangle(hdc, start_x, start_y, start_x + side_a, start_y + side_b);

		DeleteObject(hPen);
		DeleteObject(hBrush);

		ReleaseDC(hwnd, hdc);
	}

	Rectangle(double side_a, double side_b, SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS)
	{
		set_color(color);
		set_start_x(start_x);
		set_start_y(start_y);
		set_side_a(side_a);
		set_side_b(side_b);
	}
	~Rectangle() {}
};

void main()
{
	setlocale(LC_ALL, "");
	Square square(150, Color::red, 200, 200, 5);
	cout << "Длина стороны: " << square.get_side() << endl;
	cout << "Периметр:\t" << square.get_perimeter() << endl;
	cout << "Площадь:\t" << square.get_area() << endl;
	square.draw();

	class Rectangle rect(250, 150, Color::blue, 200, 450, 5);
	cout << "Сторона A:\t" << rect.get_side_a() << endl;
	cout << "Сторона B:\t" << rect.get_side_b() << endl;
	cout << "Площадь:\t" << rect.get_area() << endl;
	cout << "Периметр:\t" << rect.get_perimeter() << endl;
	rect.draw();
}