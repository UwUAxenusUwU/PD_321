#include<iostream>
#include<exception>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	/*try
	{
		throw 0;
	}
	catch (int e)
	{
		std::cerr << "Error# " << e << endl;
	}*/
	try
	{
		throw std::exception("throwing exception from main()");
		int a, b;
		cout << "������� ��� �����: "; cin >> a >> b;
		cout << a / b << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	catch (...)
	{
		//������������� ����������, ������� �����������, ���� �� ������� �� ���� ������ ����������.
		//������������� ���������� �� ���������� ���� ����������
		std::cerr << "Error: ���-�� ����� �� ���...." << endl;
	}

}