#include<iostream>
#include<stdio.h>
#include<fstream>
#include <string>
#include<cmath>
using namespace std;
const int n = 255;

void freq1_ent1()
{
 setlocale(LC_ALL, "rus");
 cout << "Укажите имя файла: " << endl;
 char name[40];
 cin.getline(name, 40);
 fstream file(name, ios::app);
 int size = 0;
 file.seekg(0, std::ios::end);
 size = file.tellg();
 cout << "Size " << size << endl;
 file.close();


 char *myArray = new char[size];
 char current_char;
 int i = 0;
 ifstream myfile(name, ios::app);

 if (myfile.is_open())
 {
  while (!myfile.eof())
  {
   myfile >> myArray[i];
   i++;
  }

  char symbols[n];     // строка символів без повторень
  double chance[n];   // частота
  int symbolsLenth = 0;

  for (int i = 0; i < size; i++)
  {
   int flg = 0;
   for (int j = 0; j < symbolsLenth; j++) {
    if (myArray[i] == symbols[j]) {
     chance[j]++; //якщо символи однакові збільчуємо частоту
     flg = 1;
     break;
    }
   }
   if (!flg)
   {
    chance[symbolsLenth] = 1.0;
    symbols[symbolsLenth] = myArray[i];
    symbolsLenth++;
   }
  }

  // сортування
  int flg = 1;
  while (flg)
  {
   flg = 0;
   for (int i = 0; i < symbolsLenth - 1; i++) {
    if (chance[i] < chance[i + 1]) {
     double tmp = chance[i];
     chance[i] = chance[i + 1];
     chance[i + 1] = tmp;
     char ch = symbols[i];
     symbols[i] = symbols[i + 1];
     symbols[i + 1] = ch;
     flg = 1;
    }
   }
  }

  ofstream out;
  out.open("Freq1.txt");
  if (out.is_open())
  {
   out << "Частота символов:\n";
   for (int i = 0; i < symbolsLenth; i++)
   {
    out << "Символ " << symbols[i] << " частота- " << chance[i] << endl;
   }
  }
  out.close();


  out.open("Entropy1.txt");

  if (out.is_open())
  {
   out << "Ентопия: \n";
   for (int i = 0; i < symbolsLenth; i++)
   {
    float k;
    k = -(chance[i] / size)*log((chance[i] / size)) / log(2);
    out << "Символ H" << symbols[i] << " ентопия- " << k << endl;
   }
  }
  out.close();

 }
}

int main()

{
 freq1_ent1();
 cout << "Final";
 system("Pause");
 return 0;

}
