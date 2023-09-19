//virtual type name(parameters)specifiers = 0;
#include<iostream>
using namespace std;

class Animal
{
public:
	virtual void sound() = 0;
};

class Cat :public Animal
{
public:
	void sound()override
	{
		cout << "���" << endl;
	}
};
class Dog :public Animal
{
public:
	void sound()
	{
		cout << "���" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Animal animal;
	Cat cat;
	cat.sound();

	Dog dog;
}