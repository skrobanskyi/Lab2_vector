// Vector.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
using namespace std;
#include <iostream>
#include <sstream>
double StringToDouble(const string& s)
{
	istringstream i(s);
	double x;
	if (!(i >> x))
		return 0;
	return x;
}

bool StringToDoubleCheck(const string& s)
{
	istringstream i(s);
	double x;
	if (!(i >> x))
		return false;
	return true;
}
class Vector
{
private:

	double* ptr;
	int cnt;

public:

	int GetCnt()
	{
		return cnt;
	}

	void SetCnt(int newCnt)
	{
		cnt = newCnt;
	}

	double* GetPtr()
	{
		return ptr;
	}

	void SetPtr(double* newptr)
	{
		ptr = newptr;
	}

	//		vector(vector& a);

	Vector(int CountElem)
	{
		ptr = new double[CountElem];
		//			if (ptr == NULL)
		//				Exeption;
		cnt = CountElem;
	}

	Vector()
	{
		ptr = new double[0];
		//			if (ptr == NULL)
		//				Exeption;
		cnt = 0;
	}

	friend ostream& operator<< (ostream& o, Vector& a)
	{
		if (a.GetCnt() < 1)
		{
			o << "NULL";
			return o;
		}

		int n = a.GetCnt() - 1;
		double* buf = a.GetPtr();
		for (int i = 0; i < n; i++)
			o << buf[i] << ", ";
		o << buf[n];
		return o;
	}

	friend istream& operator>> (istream& o, Vector& a)
	{
		double* p = new double[0];
		a.SetCnt(0);
		a.SetPtr(p);
		string b;

		for (o >> b; StringToDoubleCheck(b); o >> b)
			a.addElement(StringToDouble(b));

		return o;

	}

	friend Vector& operator+ (Vector a, Vector b)
	{
		Vector c;
		int n = b.GetCnt(), N = a.GetCnt();
		double* A = a.GetPtr(), *B = b.GetPtr();
		if (a.GetCnt() < b.GetCnt())
		{
			n = a.GetCnt();
			N = b.GetCnt();
			A = b.GetPtr();
			B = a.GetPtr();
		}

		for (int i = 0; i < n; i++)
			c.addElement(A[i] + B[i]);

		for (int i = n; i < N; i++)
			c.addElement(A[i]);

		c.SetCnt(N);
		return c;
	}

	friend Vector& operator- (Vector a, Vector b)
	{
		Vector c;
		double *tmp, *tmpC;
		int na = a.GetCnt(), nb = b.GetCnt();
		if (na < nb)
		{
			c = b;
			c.SetCnt(nb);
			tmp = a.GetPtr();
			tmpC = c.GetPtr();

			for (int i = 0; i < na; i++)
				tmpC[i] = tmp[i] - tmpC[i];

			for (int i = na; i < nb; i++)
				tmpC[i] = -tmpC[i];
		}
		else
		{
			c = a;
			c.SetCnt(na);
			tmp = b.GetPtr();
			tmpC = c.GetPtr();

			for (int i = 0; i < nb; i++)
				tmpC[i] -= tmp[i];

		}
		return c;
	}

	friend Vector& operator* (Vector& a, Vector& b)
	{
		Vector c;
		double* tmp, *tmpC;
		int na = a.GetCnt(), nb = b.GetCnt();
		if (na < nb)
		{
			c = a;
			c.SetCnt(na);
			tmp = b.GetPtr();
			tmpC = c.GetPtr();

			for (int i = 0; i < na; i++)
				tmpC[i] *= tmp[i];
		}
		else
		{
			c = b;
			c.SetCnt(nb);
			tmp = a.GetPtr();
			tmpC = c.GetPtr();

			for (int i = 0; i < nb; i++)
				tmpC[i] *= tmp[i];

		}
		return c;
	}

	friend Vector& operator/ (Vector& a, Vector& b)
	{
		Vector c;
		double* tmp, *tmpC;
		int na = a.GetCnt(), nb = b.GetCnt();
		if (na < nb)
		{
			c = a;
			c.SetCnt(na);
			tmp = b.GetPtr();
			tmpC = c.GetPtr();

			for (int i = 0; i < na; i++)
				tmpC[i] /= tmp[i];
		}
		else
		{
			c = b;
			c.SetCnt(nb);
			tmp = a.GetPtr();
			tmpC = c.GetPtr();

			for (int i = 0; i < nb; i++)
				tmpC[i] = tmp[i] / tmpC[i];

		}
		return c;
	}

	friend Vector& operator+ (Vector& a, double b)
	{
		int n = a.GetCnt();
		Vector c = a;
		double* tmp = c.GetPtr();
		for (int i = 0; i < n; i++)
			tmp[i] += b;
		return c;
	}

	friend Vector& operator+ (double b, Vector& a)
	{
		return a + b;
	}

	friend Vector& operator- (Vector& a, int b)
	{
		Vector c = a;
		c.delElement(b);
		return c;
	}

	friend Vector& operator* (Vector& a, double b)
	{
		int n = a.GetCnt();
		Vector c = a;
		double* tmp = c.GetPtr();
		for (int i = 0; i < n; i++)
			tmp[i] *= b;
		return c;
	}

	friend Vector& operator* (double b, Vector& a)
	{
		return a * b;
	}

	Vector& operator= (Vector b)
	{
		cnt = b.GetCnt();
		ptr = new double[cnt];
		double* tmp = b.GetPtr();
		for (int i = 0; i < cnt; i++)
			ptr[i] = tmp[i];
		return(*this);
	}


	int addElement(double newElement)
	{
		// Створити новий масив з +1 елементом 
		// Скопiювати зi старого масиву в новий все елементи 
		// Зберегти новий елемент в новому масивi 
		// Видалити старий масив 
		// В старий покажчик зберегти нову пам'ять (новий масив) + змiнити кiлькiсть елементiв 
		double* tmp = new double[cnt + 1];
		if (tmp == NULL)
			return 0;
		for (int i = 0; i < cnt; i++)
			tmp[i] = ptr[i];
		tmp[cnt] = newElement;
		delete ptr;
		cnt++;
		ptr = tmp;
		return 1;
	}

	int delElement(int indexDelElement)
	{
		// Створити новий масив -1 елементом 
		// Коniювати всi елементи в новий масив, крiм видаляеться 
		// Видалити старий масив 
		// В старий покажчик збереrти нову пам'ять (новий масив) + змiнити кiлькiсть елементiв 
		double* tmp;
		int i;
		tmp = new double[cnt - 1];
		if (tmp == NULL)
			return 0;
		for (i = 0; i < indexDelElement; i++)
			tmp[i] = ptr[i];
		for (i = indexDelElement + 1; i < cnt; i++)
			tmp[i - 1] = ptr[i];
		delete ptr;
		cnt--;
		ptr = tmp;
		return 1;
	}

};

int main()
{
    
	Vector g, h, p;
	g.addElement(12);
	g.addElement(3);
	h.addElement(10);
	h.addElement(6);
	h.addElement(1);
	h.addElement(5);
	p = g + h;
	p = 2 * p;
	cout << p;
	cout << '\n';
	cout << p.GetCnt();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
