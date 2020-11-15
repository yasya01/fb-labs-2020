﻿// lab3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <Windows.h>

using namespace std;

int symbol_count;
char *symbol_array = new char[symbol_count];
string alph = "абвгдежзийклмнопрстуфхцчшщьыэюя";
string bigrams_my[5] = {"еш","еы","ск", "шя","до"};//до
string bigrams_ru[5] = {"ст","но","то","на","ен"};
int res_a[24], res_b[24];
//b>a
int funk_x(char a, char b)
{
	int pa= alph.find_first_of(a);
	int pb = alph.find_first_of(b);

	int X = pa * 31 + pb;

	return X;
}
int gcd(int a, int b)
{
	if (a == 0)
	{
		return b;
	}

	else
	{
		int d = gcd(b%a, a);
		return d;
	}
}

void gcd_ex(int a, int b, int *x, int *y, int *d)
{
	int q, r, x1, x2, y1, y2;
	if (b == 0)
	{
		*d = a;
		*x = 1;
		*y = 0;
	}
	else
	{
		x2 = 1; x1 = 0; y2 = 0; y1 = 1;
		while (b > 0)
		{
			q = a / b;
			r = a - q * b;
			*x = x2 - q * x1;
			*y = y2 - q * y1;
			a = b; b = r; x2 = x1; x1 = *x; y2 = y1; y1 = *y;
		}
		*d = a, *x = x2, *y = y2;

	}
}

int mod_reverse(int a, int m)
{
	int x, y, d;
	gcd_ex(a, m, &x, &y, &d);
	if (d != 1)
	{
		cout << "no solution"<<endl;
		return 0;
	}
	else
	{
		x = (x % m + m) % m;
		return x;
	}
}

//  a*x=b mod(n)      n > a    n > b
int fun_lin(int a, int b, int n)
{

	if (gcd(a, n) == 1)
	{
		int x;
		x = (mod_reverse(a, n)*b) % n;

		return x;
	}
	if (gcd(a, n) > 1)
	{
		int d = gcd(a, n);
		if (b%d != 0)
		{
			cout << "No solution" << endl;
			return false;
		}
		else
		{
			int x0;
			int a1 = a / gcd(a, n);
			int b1 = b / gcd(a, n);
			int n1 = n / gcd(a, n);
			x0 = (mod_reverse(a1, n1) * b1) % n1;
			int d = gcd(a, n);
			int *x_arr = new int[d];
			for (int i = 0; i < gcd(a, n); i++)
			{
				x_arr[i] = x0 + i * n1;
			}
			return 0;
		}
	}
}

//a,b, c, d - значення з біграмс ру.
int funk_ab()
{
	
	int u = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i != j)
			{
				string temp3 = bigrams_my[i];
				string temp4 = bigrams_my[j];
				int Y1 = funk_x(temp3[0], temp3[1]);
				int Y2 = funk_x(temp4[0], temp4[1]);
				int Y3 = (Y1 - Y2);
				string temp1 = bigrams_ru[i];
				string temp2 = bigrams_ru[j];
				int X1 = funk_x(temp1[0], temp1[1]);
				int X2 = funk_x(temp2[0], temp2[1]);
				int m = 31 * 31;
				int X3 = (X1 - X2);
				if (fun_lin(X3, Y3, m) == false)
				{
					cout << "NO" << endl;
				}
				else
				{
					int A = fun_lin(X3, Y3, m);
					if (A < 0)
					{
						A = A + 961;
					}
					int B = fmod((Y1 - A * X1), m);
					if (B < 0)
					{
						B = B + 961;
					}
					//cout << "A - " << A << endl << "B - " << B << endl;
					res_a[u] = A; res_b[u] = B;
					u++;
				}

			}
		}
	}


	///////////////////////////////////////////////////
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i != j)
			{
				string temp3 = bigrams_my[j];
				string temp4 = bigrams_my[i];
				int Y1 = funk_x(temp3[0], temp3[1]);
				int Y2 = funk_x(temp4[0], temp4[1]);
				int Y3 = (Y1 - Y2);
				string temp1 = bigrams_ru[i];
				string temp2 = bigrams_ru[j];
				int X1 = funk_x(temp1[0], temp1[1]);
				int X2 = funk_x(temp2[0], temp2[1]);
				int m = 31 * 31;
				int X3 = (X1 - X2);
				if (fun_lin(X3, Y3, m) == false)
				{
					cout << "NO" << endl;
				}
				else
				{
					int A = fun_lin(X3, Y3, m);
					if (A < 0)
					{
						A = A + 961;
					}
					int B = fmod((Y1 - A * X1), m);
					if (B < 0)
					{
						B = B + 961;
					}
					//cout << "A - " << A << endl << "B - " << B << endl;
					res_a[u] = A; res_b[u] = B;
					u++;
				}

			}
		}
	}


	for (int i = 0; i < 24; i++)
	{
		cout << res_a[i] << " - " << res_b[i] << endl;
	}

	return 0;
}


int Bigrams_without_Spaces(ifstream &myfile)
{

	stringstream string_stream;
	string_stream << myfile.rdbuf();
	string text_string = string_stream.str();
	myfile.close();
	int symbol_count;
	symbol_count = text_string.length();
	symbol_array = new char[symbol_count];
	text_string.copy(symbol_array, symbol_count);

	int symbol_counter = symbol_count;
	int bigram_count = symbol_counter / 2; 
	float frequency_count = 1; 
	string **frequency_array = new string*[bigram_count]; 
	for (int i = 0; i < bigram_count; i++)
	{
		frequency_array[i] = new string[2];
	}
	string *bigram_array = new string[bigram_count];
	int helper = 0, k = 0, n = 0;
	for (int i = 0; i < symbol_counter - 1; i = i + 2)
	{
		string char_1(1, symbol_array[i]);
		string char_2(1, symbol_array[i + 1]);
		bigram_array[n] = char_1 + char_2;
		if (i == 0)
		{
			for (int j = i + 2; j < symbol_counter - 1; j = j + 2)
			{
				string char_3(1, symbol_array[j]);
				string char_4(1, symbol_array[j + 1]);
				if (bigram_array[n] == char_3 + char_4)
				{
					frequency_count++;
				}
			}
			frequency_array[k][0] = bigram_array[n];
			frequency_array[k][1] = to_string(frequency_count / bigram_count);
			frequency_count = 1;
			k++;
		}
		else
		{
			for (int m = 0; m < k; m++)
			{
				if (bigram_array[n] == frequency_array[m][0])
				{
					helper = 1;
					break;
				}
				else helper = 0;
			}
			if (helper == 0)
			{
				for (int j = i + 2; j < symbol_counter - 1; j = j + 2)
				{
					string char_3(1, symbol_array[j]);
					string char_4(1, symbol_array[j + 1]);
					if (bigram_array[n] == char_3 + char_4)
					{
						frequency_count++;
					}
				}
				frequency_array[k][0] = bigram_array[n];
				frequency_array[k][1] = to_string(frequency_count / (float)bigram_count);
				frequency_count = 1;
				k++;
			}
			else frequency_count = 1;
		}
		n++;
	}
	ofstream out;
	out.open("Bigrams_without_Spaces.txt");
	if (out.is_open())
	{
		out << "Bigrams:" << '\n';
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (j == 0) out << frequency_array[i][j];
				else out << '\t' << frequency_array[i][j];
			}
			out << '\n';
		}
		out << '\n';
	}
	out.close();
	delete[]frequency_array;
	delete[]bigram_array;
	return 0;
}


void fun_dec(ifstream &myfile)
{
	stringstream string_stream;
	string_stream << myfile.rdbuf();
	string text_string = string_stream.str();
	myfile.close();
	int k = 0;
	ofstream out;
	out.open("1.txt");
	for (int g = 0; g < 24; g++)
	{
		int k = 0;
		while (k != text_string.length())
		{


			char temp, temp1;
			temp = text_string[k];
			temp1 = text_string[k + 1];

			int Y = funk_x(temp, temp1);
			int X = fmod(mod_reverse(res_a[g], 961)*(Y - res_b[g]), 961);



			for (int i = 0; i < 31; i++)
			{
				for (int j = 0; j < 31; j++)
				{
					char a = alph[i];
					char b = alph[j];
					if (X == funk_x(a, b))
					{
						out << a << b;

					}
				}
			}

			k = k + 2;

		}
		out << endl << endl;
		out << "HELLOOOOO" << endl;
	}
}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	//int a, b, d, x, y,m;
	ifstream in;
	in.open("text.txt");
	//Bigrams_without_Spaces(in);
	/*cout << "Put a and b" << endl;
	cin >> a >> b;
	//gcd_ex(a, b, &x, &y, &d);
	//cout << d << " " << x << " " << y;
	//cin >> a >> m;
	//mod_reverse(a,m);
	//fun_lin(4, 7, 18);
	*/
	//cout<<funk_x('в', 'б');
	funk_ab();
	/*for (int i = 0; i < 12; i++)
	{
		cout << res_a[i] << " " << res_b[i] << endl;
	}
	*/
	fun_dec(in);
	
	return 0;
}






