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

// функція, що перевіряє чи символ є літерою верхнього регістру
bool IsCyrillicUpper(char symbol)
{
    if ((((int)symbol >= -64) && ((int)symbol <= -33)) || ((int)symbol == -88)) return true;
    else return false;
}

// функція, що перетворює літеру верхнього регістру в нижній регістр
char CyrillicToLower(char symbol)
{
    int a = symbol + 32;
    char b = (char)a;
    return b;
}


// функція для конвертування тексту з файлу у масив символів
int ConvertText(int &symbol_count, char *&symbol_array)
{
    string text_string; // змінна для запису тексту з файлу в рядок
    // вхідний потік для роботи з обраним файлом
    ifstream text_file("C:\\textfile.txt");
    // якщо файл вдалося відкрити
    if (text_file.is_open())
    {
        // stringstream - це потік, аналогічний до cin, тільки його вміст береться з заданого йому рядка
        stringstream string_stream;
        // rdbuf() - отримання буфера потоку (найпростіший спосіб отримати весь вміст файлу для подальшої обробки)
        // вставка буфера потоку rdbuf() файлу в рядок потоку - string_stream
        string_stream << text_file.rdbuf();
        // виводимо вміст файлу в один єдиний рядок text_string
        text_string = string_stream.str();
        text_file.close();
        int symbol_count; // кількість символів у тексті
        // кількість символів - це довжина рядка, в який ми записали текст
        symbol_count = text_string.length();
        symbol_array = new char[symbol_count]; // масив символів з тексту
        // копіюємо рядок у масив символів з кількість елементів symbol_count у ньому
        text_string.copy(symbol_array, symbol_count);
        cout << "Загальна кількість символів у тексті: " << symbol_count << '\n';
        return symbol_count;
    }
    else return 0;
}

// функція для чистки масиву
int CleanText(int &symbol_count, char *&symbol_array)
{
    // отримуємо кількість символів з функції ConvertText
    symbol_count = ConvertText(symbol_count, symbol_array);
    // проходимося по масиву та видаляємо не потрібні елементи
    for (int i = 0; i < symbol_count; i++)
    {
        if ((symbol_array[i] == '!') || (symbol_array[i] == '?') || (symbol_array[i] == '.')
            || (symbol_array[i] == ',') || (symbol_array[i] == ':') || (symbol_array[i] == ';')
            || (symbol_array[i] == '"') || (symbol_array[i] == '-') || (symbol_array[i] == '«')
            || (symbol_array[i] == '»') || (symbol_array[i] == '*') || (symbol_array[i] == '–')
            || (symbol_array[i] == '(') || (symbol_array[i] == ')') || (symbol_array[i] == '/')
            || (symbol_array[i] == '|') || (symbol_array[i] == '’') || (isdigit(symbol_array[i])) || (isalpha(symbol_array[i])))
        {
            symbol_count--; // зменшуємо кількість символів
            for (int j = i; j < symbol_count; j++) { // проходимося від початку числа до кінця масиву
                symbol_array[j] = symbol_array[j + 1]; // зміщуємо усі індекси на одиницю
            }
            i--; // переходимо до попереднього символу (ми змістили індексацію, тому повертаємося назад)
        }
        if (symbol_array[i] == '\n') symbol_array[i] = ' ';
        if (IsCyrillicUpper(symbol_array[i])) symbol_array[i] = CyrillicToLower(symbol_array[i]);
        if ((symbol_array[i - 1] == ' ') && (symbol_array[i] == ' '))
        {
            symbol_count--; // зменшуємо кількість символів
            for (int j = i; j < symbol_count; j++) { // проходимося від початку числа до кінця масиву
                symbol_array[j] = symbol_array[j + 1]; // зміщуємо усі індекси на одиницю
            }
            i--; // переходимо до попереднього символу (ми змістили індексацію, тому повертаємося назад)
        }
    }
    cout << "Кількість символів після чистки: " << symbol_count << '\n';
    return symbol_count;
}

// пошук біграм з пробілами та перетинами
int Bigrams_with_Spaces_Crossing(int symbol_count, char *symbol_array)
{
    // отримуємо кількість символів з функції CleanText
    int symbol_counter = CleanText(symbol_count, symbol_array);
    int bigram_count = symbol_counter - 1; // кількість біграм (відповідно до варіанту пошуку)
    float bigram_count_all = bigram_count; // окрема змінна для загальної кількості біграм
    float frequency_count = 1; // скільки разів біграма зустрічається в тексті (по дефолту хоча б один раз)
    string **frequency_array = new string*[bigram_count]; // двумірний масив біграм та їхніх частот
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
                bigram_count--; // зменшуємо кількість символів
                for (int k = j; k < bigram_count; k++) { // проходимося від початку числа до кінця масиву
                    bigram_array[k] = bigram_array[k + 1]; // зміщуємо усі індекси на одиницю
                }
                j--; // переходимо до попереднього символу (ми змістили індексацію, тому повертаємося назад)
            }
        }
        frequency_array[i][0] = bigram_array[i];
        frequency_array[i][1] = to_string(frequency_count / bigram_count_all);
        frequency_count = 1;
    }
    cout << '\n' << "Біграми з пробілами та перетинами:" << '\n';
    for (int i = 0; i < bigram_count; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0) cout << "Біграма: " << "*" << frequency_array[i][j] << "*";
            else cout << ", її частота: " << frequency_array[i][j] << ";";;
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
    cout << "Ентропія біграми = " << H2 << '\n' << '\n';
    delete []frequency_array;
    delete []bigram_array;
    return 0;
}

// пошук біграм без пробілів та з перетинами
int Bigrams_without_Spaces_Crossing(int symbol_count, char *symbol_array)
{
    // отримуємо кількість символів з функції CleanText
    int symbol_counter = CleanText(symbol_count, symbol_array);
    for (int i = 0; i < symbol_counter; i++)
    {
        if (symbol_array[i] == ' ')
        {
            symbol_counter--; // зменшуємо кількість символів
            for (int j = i; j < symbol_counter; j++) { // проходимося від початку числа до кінця масиву
                symbol_array[j] = symbol_array[j + 1]; // зміщуємо усі індекси на одиницю
            }
            i--; // переходимо до попереднього символу (ми змістили індексацію, тому повертаємося назад)
        }
    }
    int bigram_count = symbol_counter - 1; // кількість біграм (відповідно до варіанту пошуку)
    float bigram_count_all = bigram_count; // окрема змінна для загальної кількості біграм
    float frequency_count = 1; // скільки разів біграма зустрічається в тексті (по дефолту хоча б один раз)
    string **frequency_array = new string*[bigram_count]; // двумірний масив біграм та їхніх частот
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
                bigram_count--; // зменшуємо кількість символів
                for (int k = j; k < bigram_count; k++) { // проходимося від початку числа до кінця масиву
                    bigram_array[k] = bigram_array[k + 1]; // зміщуємо усі індекси на одиницю
                }
                j--; // переходимо до попереднього символу (ми змістили індексацію, тому повертаємося назад)
            }
        }
        frequency_array[i][0] = bigram_array[i];
        frequency_array[i][1] = to_string(frequency_count / bigram_count_all);
        frequency_count = 1;
    }
    cout << '\n' << "Біграми без пробілами та з перетинами:" << '\n';
    for (int i = 0; i < bigram_count; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0) cout << "Біграма: " << "*" << frequency_array[i][j] << "*";
            else cout << ", її частота: " << frequency_array[i][j] << ";";
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
    cout << "Ентропія біграми = " << H2 << '\n' << '\n';
    delete []frequency_array;
    delete []bigram_array;
    return 0;
}

// пошук біграм з пробілами без перетинів
int Bigrams_with_Spaces(int symbol_count, char *symbol_array)
{
    // отримуємо кількість символів з функції CleanText
    int symbol_counter = CleanText(symbol_count, symbol_array);
    int bigram_count = symbol_counter / 2; // кількість біграм (відповідно до варіанту пошуку)
    float bigram_count_all = bigram_count; // окрема змінна для загальної кількості біграм
    float frequency_count = 1; // скільки разів біграма зустрічається в тексті (по дефолту хоча б один раз)
    string **frequency_array = new string*[bigram_count]; // двовимірний масив біграм та їхніх частот
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
                bigram_count--; // зменшуємо кількість символів
                for (int k = j; k < bigram_count; k++) { // проходимося від початку числа до кінця масиву
                    bigram_array[k] = bigram_array[k + 1]; // зміщуємо усі індекси на одиницю
                }
                j--; // переходимо до попереднього символу (ми змістили індексацію, тому повертаємося назад)
            }
        }
        frequency_array[i][0] = bigram_array[i];
        frequency_array[i][1] = to_string(frequency_count / bigram_count_all);
        frequency_count = 1;
    }
    cout << '\n' << "Біграми з пробілами та без перетинів:" << '\n';
    for (int i = 0; i < bigram_count; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0) cout << "Біграма: " << "*" << frequency_array[i][j] << "*";
            else cout << ", її частота: " << frequency_array[i][j] << ";";;
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
    cout << "Ентропія біграми = " << H2 << '\n' << '\n';
    delete []frequency_array;
    delete []bigram_array;
    return 0;
}

// пошук біграм без проілів та без перетинів
int Bigrams_without_Spaces(int symbol_count, char *symbol_array)
{
    // отримуємо кількість символів з функції CleanText
    int symbol_counter = CleanText(symbol_count, symbol_array);
    for (int i = 0; i < symbol_counter; i++)
    {
        if (symbol_array[i] == ' ')
        {
            symbol_counter--; // зменшуємо кількість символів
            for (int j = i; j < symbol_counter; j++) { // проходимося від початку числа до кінця масиву
                symbol_array[j] = symbol_array[j + 1]; // зміщуємо усі індекси на одиницю
            }
            i--; // переходимо до попереднього символу (ми змістили індексацію, тому повертаємося назад)
        }
    }
    int bigram_count = symbol_counter / 2; // кількість біграм (відповідно до варіанту пошуку)
    float bigram_count_all = bigram_count; // окрема змінна для загальної кількості біграм
    float frequency_count = 1; // скільки разів біграма зустрічається в тексті (по дефолту хоча б один раз)
    string **frequency_array = new string*[bigram_count]; // двовимірний масив біграм та їхніх частот
    for (int i = 0; i < bigram_count; i++)
    {
        frequency_array[i] = new string[2];
    }
    string *bigram_array = new string[bigram_count]; // двовимірний масив біграм та їхніх частот
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
                bigram_count--; // зменшуємо кількість символів
                for (int k = j; k < bigram_count; k++) { // проходимося від початку числа до кінця масиву
                    bigram_array[k] = bigram_array[k + 1]; // зміщуємо усі індекси на одиницю
                }
                j--; // переходимо до попереднього символу (ми змістили індексацію, тому повертаємося назад)
            }
        }
        frequency_array[i][0] = bigram_array[i];
        frequency_array[i][1] = to_string(frequency_count / bigram_count_all);
        frequency_count = 1;
    }
    cout << '\n' << "Біграми без пробілів та без перетинів:" << '\n';
    for (int i = 0; i < bigram_count; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0) cout << "Біграма: " << "*" << frequency_array[i][j] << "*";
            else cout << ", її частота: " << frequency_array[i][j] << ";";;
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
    cout << "Ентропія біграми = " << H2 << '\n' << '\n';
    delete []frequency_array;
    delete []bigram_array;
    return 0;
}
