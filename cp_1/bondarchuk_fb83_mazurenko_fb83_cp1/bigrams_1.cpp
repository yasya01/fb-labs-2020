#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <Windows.h>

using namespace std;

int symbol_count;
char *symbol_array = new char[symbol_count];

int ConvertText(int &symbol_count, char *&symbol_array);
int CleanText(int &symbol_count, char *&symbol_array);
int Bigrams_with_Spaces_Crossing(int symbol_count, char *symbol_array);
int Bigrams_with_Spaces(int symbol_count, char *symbol_array);
bool IsCyrillicUpper(char symbol);
char CyrillicToLower(char symbol);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "�������� ������� ������� � �����: " << ConvertText(symbol_count, symbol_array) << '\n';
    cout << "ʳ������ ������� ���� ������: " << CleanText(symbol_count, symbol_array) << '\n';
    Bigrams_with_Spaces_Crossing(symbol_count, symbol_array);
    Bigrams_with_Spaces(symbol_count, symbol_array);
    delete []symbol_array;
    //system("pause");
    return 0;
}

// �������, �� �������� �� ������ � ������ ��������� �������
bool IsCyrillicUpper(char symbol)
{
    if ((((int)symbol >= -64) && ((int)symbol <= -33)) || ((int)symbol == -88)) return true;
    else return false;
}

// �������, �� ���������� ����� ��������� ������� � ����� ������
char CyrillicToLower(char symbol)
{
    int a = symbol + 32;
    char b = (char)a;
    return b;
}


// ������� ��� ������������� ������ � ����� � ����� �������
int ConvertText(int &symbol_count, char *&symbol_array)
{
    string text_string; // ����� ��� ������ ������ � ����� � �����
    // ������� ���� ��� ������ � ������� ������
    ifstream text_file("C:\\slova.txt");
    // ���� ���� ������� �������
    if (text_file.is_open())
    {
        // stringstream - �� ����, ���������� �� cin, ����� ���� ���� �������� � �������� ���� �����
        stringstream string_stream;
        // rdbuf() - ��������� ������ ������ (����������� ����� �������� ���� ���� ����� ��� �������� �������)
        // ������� ������ ������ rdbuf() ����� � ����� ������ - string_stream
        string_stream << text_file.rdbuf();
        // �������� ���� ����� � ���� ������ ����� text_string
        text_string = string_stream.str();
        text_file.close();
        int symbol_count; // ������� ������� � �����
        // ������� ������� - �� ������� �����, � ���� �� �������� �����
        symbol_count = text_string.length();
        symbol_array = new char[symbol_count]; // ����� ������� � ������
        // ������� ����� � ����� ������� � ������� �������� symbol_count � �����
        text_string.copy(symbol_array, symbol_count);
        return symbol_count;
    }
    else return 0;
}

// ������� ��� ������ ������
int CleanText(int &symbol_count, char *&symbol_array)
{
    // �������� ������� ������� � ������� ConvertText
    symbol_count = ConvertText(symbol_count, symbol_array);
    // ����������� �� ������ �� ��������� �� ������ ��������
    for (int i = 0; i < symbol_count; i++)
    {
        if ((symbol_array[i] == '!') || (symbol_array[i] == '?') || (symbol_array[i] == '.')
            || (symbol_array[i] == ',') || (symbol_array[i] == ':') || (symbol_array[i] == ';')
            || (symbol_array[i] == '"') || (symbol_array[i] == '-') || (symbol_array[i] == '�')
            || (symbol_array[i] == '�') || (symbol_array[i] == '*') || (symbol_array[i] == '�')
            || (symbol_array[i] == '(') || (symbol_array[i] == ')') || (symbol_array[i] == '/')
            || (symbol_array[i] == '|') || (symbol_array[i] == '�') || (symbol_array[i] == '�')
            || (symbol_array[i] == '�') || ((int)symbol_array[i] == 39) || (isdigit(symbol_array[i]))
            || (isalpha(symbol_array[i])) || (symbol_array[i] == '�') || (symbol_array[i] == '�')
            || (symbol_array[i] == '�') || (symbol_array[i] == '�'))
        {
            symbol_count--; // �������� ������� �������
            if (i != symbol_count - 1)
            {
                for (int j = i; j < symbol_count; j++) { // ����������� �� ������� ����� �� ���� ������
                    symbol_array[j] = symbol_array[j + 1]; // ������ �� ������� �� �������
                }
                i--; // ���������� �� ������������ ������� (�� ������� ����������, ���� ����������� �����)
            }
        }
        if (symbol_array[i] == '\n') symbol_array[i] = ' ';
        if (IsCyrillicUpper(symbol_array[i])) symbol_array[i] = CyrillicToLower(symbol_array[i]);
        if ((symbol_array[i - 1] == ' ') && (symbol_array[i] == ' '))
        {
            symbol_count--; // �������� ������� �������
            for (int j = i; j < symbol_count; j++) { // ����������� �� ������� ����� �� ���� ������
                symbol_array[j] = symbol_array[j + 1]; // ������ �� ������� �� �������
            }
            i--; // ���������� �� ������������ ������� (�� ������� ����������, ���� ����������� �����)
        }
    }
    ofstream out;
    out.open("slova_clean.txt");
    if (out.is_open())
    {
        for (int i = 0; i < symbol_count; i++)
        {
            out << symbol_array[i];
        }

    }
    out.close();
    return symbol_count;
}

// ����� ����� � �������� �� ����������
int Bigrams_with_Spaces_Crossing(int symbol_count, char *symbol_array)
{
    int symbol_counter = symbol_count;
    int bigram_count = symbol_counter - 1; // ������� ����� (�������� �� ������� ������
    float frequency_count = 1; // ������ ���� ������ ����������� � ����� (�� ������� ���� � ���� ���)
    string **frequency_array = new string*[bigram_count]; // �������� ����� ����� �� ���� ������
    for (int i = 0; i < bigram_count; i++)
    {
        frequency_array[i] = new string[2];
    }
    string *bigram_array = new string[bigram_count];
    int helper = 0, k = 0;
    for (int i = 0; i < bigram_count; i++)
    {
        string char_1(1, symbol_array[i]);
        string char_2(1, symbol_array[i + 1]);
        bigram_array[i] = char_1 + char_2;
        if (i == 0)
        {
            for (int j = i + 1; j < bigram_count; j++)
            {
                string char_3(1, symbol_array[j]);
                string char_4(1, symbol_array[j + 1]);
                if (bigram_array[i] == char_3 + char_4)
                {
                    frequency_count++;
                }
            }
            frequency_array[k][0] = bigram_array[i];
            frequency_array[k][1] = to_string(frequency_count / bigram_count);
            frequency_count = 1;
            k++;
        }
        else
        {
            for (int n = 0; n < k; n++)
            {
                if (bigram_array[i] == frequency_array[n][0])
                {
                    helper = 1;
                    break;
                }
                else helper = 0;
            }
            if (helper == 0)
            {
                for (int j = i + 1; j < bigram_count; j++)
                {
                    string char_3(1, symbol_array[j]);
                    string char_4(1, symbol_array[j + 1]);
                    if (bigram_array[i] == char_3 + char_4)
                    {
                        frequency_count++;
                    }
                }
                frequency_array[k][0] = bigram_array[i];
                frequency_array[k][1] = to_string(frequency_count / (float)bigram_count);
                frequency_count = 1;
                k++;
            }
            else frequency_count = 1;
        }
    }
    ofstream out;
    out.open("Bigrams_with_Spaces_Crossing.txt");
    if (out.is_open())
    {
        out << "������� � �������� �� � ����������:" << '\n';
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
        float H2, Hz, sum = 0;
        for (int i = 0; i < k; i++)
        {
            sum = sum + (stof(frequency_array[i][1]) * (log(stof(frequency_array[i][1])) / log(2)));
        }
        Hz = 0 - sum;
        H2 = 0.5 * Hz;
        out << "������� ������ = " << H2 << '\n' << '\n';
    }
    out.close();
    delete []frequency_array;
    delete []bigram_array;
    return 0;
}


// ����� ����� � �������� ��� ��������
int Bigrams_with_Spaces(int symbol_count, char *symbol_array)
{
    int symbol_counter = symbol_count;
    int bigram_count = symbol_counter / 2; // ������� ����� (�������� �� ������� ������)
    float frequency_count = 1; // ������ ���� ������ ����������� � ����� (�� ������� ���� � ���� ���)
    string **frequency_array = new string*[bigram_count]; // �������� ����� ����� �� ���� ������
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
    out.open("Bigrams_with_Spaces.txt");
    if (out.is_open())
    {
        out << "������� � �������� �� ��� ��������:" << '\n';
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
        float H2, Hz, sum = 0;
        for (int i = 0; i < k; i++)
        {
            sum = sum + (stof(frequency_array[i][1]) * (log(stof(frequency_array[i][1])) / log(2)));
        }
        Hz = 0 - sum;
        H2 = 0.5 * Hz;
        out << "������� ������ = " << H2 << '\n' << '\n';
    }
    out.close();
    delete []frequency_array;
    delete []bigram_array;
    return 0;
}
