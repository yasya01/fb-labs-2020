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
int Bigrams_without_Spaces_Crossing(int symbol_count, char *symbol_array);
int Bigrams_with_Spaces(int symbol_count, char *symbol_array);
int Bigrams_without_Spaces(int symbol_count, char *symbol_array);
bool IsCyrillicUpper(char symbol);
char CyrillicToLower(char symbol);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Bigrams_with_Spaces_Crossing(symbol_count, symbol_array);
    Bigrams_without_Spaces_Crossing(symbol_count, symbol_array);
    Bigrams_with_Spaces(symbol_count, symbol_array);
    Bigrams_without_Spaces(symbol_count, symbol_array);
    delete []symbol_array;
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
    ifstream text_file("C:\\textfile.txt");
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
        cout << "�������� ������� ������� � �����: " << symbol_count << '\n';
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
            || (symbol_array[i] == '|') || (symbol_array[i] == '�') || (isdigit(symbol_array[i])) || (isalpha(symbol_array[i])))
        {
            symbol_count--; // �������� ������� �������
            for (int j = i; j < symbol_count; j++) { // ����������� �� ������� ����� �� ���� ������
                symbol_array[j] = symbol_array[j + 1]; // ������ �� ������� �� �������
            }
            i--; // ���������� �� ������������ ������� (�� ������� ����������, ���� ����������� �����)
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
    cout << "ʳ������ ������� ���� ������: " << symbol_count << '\n';
    return symbol_count;
}

// ����� ����� � �������� �� ����������
int Bigrams_with_Spaces_Crossing(int symbol_count, char *symbol_array)
{
    // �������� ������� ������� � ������� CleanText
    int symbol_counter = CleanText(symbol_count, symbol_array);
    int bigram_count = symbol_counter - 1; // ������� ����� (�������� �� ������� ������)
    float bigram_count_all = bigram_count; // ������ ����� ��� �������� ������� �����
    float frequency_count = 1; // ������ ���� ������ ����������� � ����� (�� ������� ���� � ���� ���)
    string **frequency_array = new string*[bigram_count]; // �������� ����� ����� �� ���� ������
    for (int i = 0; i < bigram_count; i++)
    {
        frequency_array[i] = new string[2];
    }
    string *bigram_array = new string[bigram_count];
    for (int i = 0; i < bigram_count; i++)
    {
        string char_1(1, symbol_array[i]);
        string char_2(1, symbol_array[i + 1]);
        bigram_array[i] = char_1 + char_2;
    }
    for (int i = 0; i < bigram_count; i++)
    {
        for (int j = i + 1; j < bigram_count; j++)
        {
            if ((bigram_array[i].compare(bigram_array[j]) == 0))
            {
                frequency_count++;
                bigram_count--; // �������� ������� �������
                for (int k = j; k < bigram_count; k++) { // ����������� �� ������� ����� �� ���� ������
                    bigram_array[k] = bigram_array[k + 1]; // ������ �� ������� �� �������
                }
                j--; // ���������� �� ������������ ������� (�� ������� ����������, ���� ����������� �����)
            }
        }
        frequency_array[i][0] = bigram_array[i];
        frequency_array[i][1] = to_string(frequency_count / bigram_count_all);
        frequency_count = 1;
    }
    cout << '\n' << "������� � �������� �� ����������:" << '\n';
    for (int i = 0; i < bigram_count; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0) cout << "�������: " << "*" << frequency_array[i][j] << "*";
            else cout << ", �� �������: " << frequency_array[i][j] << ";";;
        }
        cout << '\n';
    }
    cout << '\n';
    float H2, Hz, sum = 0;
    for (int i = 0; i < bigram_count; i++)
    {
        sum = sum + (stof(frequency_array[i][1]) * log(stof(frequency_array[i][1])));
    }
    Hz = 0 - sum;
    H2 = 0.5 * Hz;
    cout << "������� ������ = " << H2 << '\n' << '\n';
    delete []frequency_array;
    delete []bigram_array;
    return 0;
}

// ����� ����� ��� ������ �� � ����������
int Bigrams_without_Spaces_Crossing(int symbol_count, char *symbol_array)
{
    // �������� ������� ������� � ������� CleanText
    int symbol_counter = CleanText(symbol_count, symbol_array);
    for (int i = 0; i < symbol_counter; i++)
    {
        if (symbol_array[i] == ' ')
        {
            symbol_counter--; // �������� ������� �������
            for (int j = i; j < symbol_counter; j++) { // ����������� �� ������� ����� �� ���� ������
                symbol_array[j] = symbol_array[j + 1]; // ������ �� ������� �� �������
            }
            i--; // ���������� �� ������������ ������� (�� ������� ����������, ���� ����������� �����)
        }
    }
    int bigram_count = symbol_counter - 1; // ������� ����� (�������� �� ������� ������)
    float bigram_count_all = bigram_count; // ������ ����� ��� �������� ������� �����
    float frequency_count = 1; // ������ ���� ������ ����������� � ����� (�� ������� ���� � ���� ���)
    string **frequency_array = new string*[bigram_count]; // �������� ����� ����� �� ���� ������
    for (int i = 0; i < bigram_count; i++)
    {
        frequency_array[i] = new string[2];
    }
    string *bigram_array = new string[bigram_count];
    for (int i = 0; i < bigram_count; i++)
    {
        string char_1(1, symbol_array[i]);
        string char_2(1, symbol_array[i + 1]);
        bigram_array[i] = char_1 + char_2;
    }
    for (int i = 0; i < bigram_count; i++)
    {
        for (int j = i; j < bigram_count; j++)
        {
            if ((bigram_array[i].compare(bigram_array[j]) == 0) && (i != j))
            {
                frequency_count++;
                bigram_count--; // �������� ������� �������
                for (int k = j; k < bigram_count; k++) { // ����������� �� ������� ����� �� ���� ������
                    bigram_array[k] = bigram_array[k + 1]; // ������ �� ������� �� �������
                }
                j--; // ���������� �� ������������ ������� (�� ������� ����������, ���� ����������� �����)
            }
        }
        frequency_array[i][0] = bigram_array[i];
        frequency_array[i][1] = to_string(frequency_count / bigram_count_all);
        frequency_count = 1;
    }
    cout << '\n' << "������� ��� �������� �� � ����������:" << '\n';
    for (int i = 0; i < bigram_count; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0) cout << "�������: " << "*" << frequency_array[i][j] << "*";
            else cout << ", �� �������: " << frequency_array[i][j] << ";";
        }
        cout << '\n';
    }
    cout << '\n';
    float H2, Hz, sum = 0;
    for (int i = 0; i < bigram_count; i++)
    {
        sum = sum + (stof(frequency_array[i][1]) * log(stof(frequency_array[i][1])));
    }
    Hz = 0 - sum;
    H2 = 0.5 * Hz;
    cout << "������� ������ = " << H2 << '\n' << '\n';
    delete []frequency_array;
    delete []bigram_array;
    return 0;
}

// ����� ����� � �������� ��� ��������
int Bigrams_with_Spaces(int symbol_count, char *symbol_array)
{
    // �������� ������� ������� � ������� CleanText
    int symbol_counter = CleanText(symbol_count, symbol_array);
    int bigram_count = symbol_counter / 2; // ������� ����� (�������� �� ������� ������)
    float bigram_count_all = bigram_count; // ������ ����� ��� �������� ������� �����
    float frequency_count = 1; // ������ ���� ������ ����������� � ����� (�� ������� ���� � ���� ���)
    string **frequency_array = new string*[bigram_count]; // ���������� ����� ����� �� ���� ������
    for (int i = 0; i < bigram_count; i++)
    {
        frequency_array[i] = new string[2];
    }
    string *bigram_array = new string[bigram_count];
    int n = 0;
    for (int i = 0; i < symbol_counter - 1; i = i + 2)
    {
        string char_1(1, symbol_array[i]);
        string char_2(1, symbol_array[i + 1]);
        bigram_array[n] = char_1 + char_2;
        n++;
    }
    for (int i = 0; i < bigram_count; i++)
    {
        for (int j = i + 1; j < bigram_count; j++)
        {
            if ((bigram_array[i].compare(bigram_array[j]) == 0))
            {
                frequency_count++;
                bigram_count--; // �������� ������� �������
                for (int k = j; k < bigram_count; k++) { // ����������� �� ������� ����� �� ���� ������
                    bigram_array[k] = bigram_array[k + 1]; // ������ �� ������� �� �������
                }
                j--; // ���������� �� ������������ ������� (�� ������� ����������, ���� ����������� �����)
            }
        }
        frequency_array[i][0] = bigram_array[i];
        frequency_array[i][1] = to_string(frequency_count / bigram_count_all);
        frequency_count = 1;
    }
    cout << '\n' << "������� � �������� �� ��� ��������:" << '\n';
    for (int i = 0; i < bigram_count; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0) cout << "�������: " << "*" << frequency_array[i][j] << "*";
            else cout << ", �� �������: " << frequency_array[i][j] << ";";;
        }
        cout << '\n';
    }
    cout << '\n';
    float H2, Hz, sum = 0;
    for (int i = 0; i < bigram_count; i++)
    {
        sum = sum + (stof(frequency_array[i][1]) * log(stof(frequency_array[i][1])));
    }
    Hz = 0 - sum;
    H2 = 0.5 * Hz;
    cout << "������� ������ = " << H2 << '\n' << '\n';
    delete []frequency_array;
    delete []bigram_array;
    return 0;
}

// ����� ����� ��� ����� �� ��� ��������
int Bigrams_without_Spaces(int symbol_count, char *symbol_array)
{
    // �������� ������� ������� � ������� CleanText
    int symbol_counter = CleanText(symbol_count, symbol_array);
    for (int i = 0; i < symbol_counter; i++)
    {
        if (symbol_array[i] == ' ')
        {
            symbol_counter--; // �������� ������� �������
            for (int j = i; j < symbol_counter; j++) { // ����������� �� ������� ����� �� ���� ������
                symbol_array[j] = symbol_array[j + 1]; // ������ �� ������� �� �������
            }
            i--; // ���������� �� ������������ ������� (�� ������� ����������, ���� ����������� �����)
        }
    }
    int bigram_count = symbol_counter / 2; // ������� ����� (�������� �� ������� ������)
    float bigram_count_all = bigram_count; // ������ ����� ��� �������� ������� �����
    float frequency_count = 1; // ������ ���� ������ ����������� � ����� (�� ������� ���� � ���� ���)
    string **frequency_array = new string*[bigram_count]; // ���������� ����� ����� �� ���� ������
    for (int i = 0; i < bigram_count; i++)
    {
        frequency_array[i] = new string[2];
    }
    string *bigram_array = new string[bigram_count]; // ���������� ����� ����� �� ���� ������
    int n = 0;
    for (int i = 0; i < symbol_counter - 1; i = i + 2)
    {
        string char_1(1, symbol_array[i]);
        string char_2(1, symbol_array[i + 1]);
        bigram_array[n] = char_1 + char_2;
        n++;
    }
    for (int i = 0; i < bigram_count; i++)
    {
        for (int j = i + 1; j < bigram_count; j++)
        {
            if ((bigram_array[i].compare(bigram_array[j]) == 0))
            {
                frequency_count++;
                bigram_count--; // �������� ������� �������
                for (int k = j; k < bigram_count; k++) { // ����������� �� ������� ����� �� ���� ������
                    bigram_array[k] = bigram_array[k + 1]; // ������ �� ������� �� �������
                }
                j--; // ���������� �� ������������ ������� (�� ������� ����������, ���� ����������� �����)
            }
        }
        frequency_array[i][0] = bigram_array[i];
        frequency_array[i][1] = to_string(frequency_count / bigram_count_all);
        frequency_count = 1;
    }
    cout << '\n' << "������� ��� ������ �� ��� ��������:" << '\n';
    for (int i = 0; i < bigram_count; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0) cout << "�������: " << "*" << frequency_array[i][j] << "*";
            else cout << ", �� �������: " << frequency_array[i][j] << ";";;
        }
        cout << '\n';
    }
    cout << '\n';
    float H2, Hz, sum = 0;
    for (int i = 0; i < bigram_count; i++)
    {
        sum = sum + (stof(frequency_array[i][1]) * log(stof(frequency_array[i][1])));
    }
    Hz = 0 - sum;
    H2 = 0.5 * Hz;
    cout << "������� ������ = " << H2 << '\n' << '\n';
    delete []frequency_array;
    delete []bigram_array;
    return 0;
}
