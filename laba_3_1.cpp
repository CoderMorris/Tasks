#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>
#include <string>
using namespace std;

const int N1 = 10000;
const int N2 = 50000;
const int N3 = 100000;
const int N4 = 150000;

string const filename = "test_numbers.txt";
string const test1 = "test_10.txt";
string const test2 = "test_100.txt";
string const test3 = "test_500.txt";
string const test4 = "test_1000.txt";

int* read_file(string filename, int n)
{
    int* numbers = new int[n];
    ifstream inputFile(filename);
    if (inputFile.is_open())
    {
        int number = 0;
        int count = 0;
        while (inputFile >> number && count < n)
        {
            numbers[count] = number;
            count++;
        }
        inputFile.close();
    }
    return numbers;
}

void BubbleSort(int* a, int n, long long& osn, long long& vsp, long long& memory)
{
    int i, j, x;
    memory += 3 * sizeof(int);
    for (i = 1; ++vsp && i < n; i++) {
        for (j = n - 1; ++vsp && j >= i; j--) 
        {
            if (++osn && a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
            }
        }
    }
}

void BubbleSort2(int* a, int n, long long& osn, long long& vsp, long long& memory)
{
    int i = 1, j, x, k; /*i=1 - левая граница сравниваемых элементов*/
    memory += 4 * sizeof(int);
    do
    {
        k = 0; /*признак отсутствия обменов*/
        for (j = n - 1; ++vsp && j >= i; j--)
            if (++osn && a[j - 1] > a[j])
            {
                x = a[j - 1];
                a[j - 1] = a[j];
                a[j] = x;
                k = j; /*запоминаем место последнего обмена*/
            }
        i = k; /*запоминаем место последнего обмена как левую границу*/
    } while (k && ++vsp);
}


void ShakerSort(int* a, int n, long long& osn, long long& vsp, long long& memory)
{
    int j, k = n - 1, left = 1, right = n - 1, x;
    memory += 5 * sizeof(int);
    do {
        for (j = right; ++vsp && j >= left; j--)
        {	
            if (++osn && a[j - 1] < a[j])
            {
                x = a[j];
                a[j] = a[j-1];
                a[j-1] = x;
                k = j; 
            }
        }
        left = k + 1; //просто k

        for (j = left; ++vsp && j <= right; j++) 
        {
            if (++osn && a[j - 1] < a[j])
            {
                x = a[j];
                a[j] = a[j-1];
                a[j-1] = x;
                k = j;
            }
        }
        right = k - 1;
    } while (++vsp && left < right);
}

//void QuickSort(int* a, int n, long long& osn, long long& vsp, long long& memory)
//{
//    const int M = log(n) / log(2) + 1;
//    int i, j, left, right, s, x, w;
//    struct stack { int left, right; } *stack;
//    stack = (struct stack*)malloc(M * sizeof(struct stack));
//    s = 0;
//    stack[0].left = 0;
//    stack[0].right = n - 1;
//    memory = 8 * sizeof(int) + sizeof(struct stack*) + M * sizeof(struct stack);
//    do /*выбор из стека последнего запроса*/
//    {
//        left = stack[s].left;
//        right = stack[s].right;
//        s--;
//        do /*разделение а[left]… a[right]*/
//        {
//            i = left; j = right;
//            x = a[(left + right) / 2];
//            do
//            {
//                while (++osn && a[i] < x) i++;
//                while (++osn && x < a[j]) j--;
//                if (++vsp && i <= j)
//                {
//                    w = a[i]; a[i] = a[j]; a[j] = w;
//                    i++; j--;
//                }
//            } while (++vsp && i < j);
//            if (vsp+=2 && i < right && right - i >= j - left) /*если правая часть не меньше левой*/
//            { /*запись в стек границ правой части*/
//                s++;
//                stack[s].left = i;
//                stack[s].right = right;
//                right = j; /*теперь left и right ограничивают левую часть*/
//            }
//            else if (vsp+=2 && j > left && j - left > right - i) /*если левая часть больше правой*/
//            { /*запись в стек границ левой части*/
//                s++;
//                stack[s].left = left;
//                stack[s].right = j;
//                left = i; /*теперь left и right ограничивают правую часть*/
//            }
//            else left = right; /*делить больше нечего, интервал "схлопывается"*/
//        } while (++vsp && left < right);
//    } while (++vsp && s > -1);
//    free(stack);
//}

void QuickSort(int* a, int n, long long& osn, long long& vsp, long long& memory)
{
    int x, w, i, j;
    x = a[n / 2];
    i = 0; j = n - 1;
    memory += 4 * sizeof(int);

    do
    {
        while (++osn && a[i] < x) { i++; }
        while (++osn && x < a[j]) { j--; }
        if (++vsp && i <= j)
        {
            w = a[i]; a[i] = a[j]; a[j] = w;
            i++; j--;
        }
    } while (++vsp && i < j);

    if (++vsp && j > 0) { QuickSort(a, j + 1, osn, vsp, memory); }
    if (++vsp && i < n - 1) { QuickSort(a + i, n - i, osn, vsp, memory); }

    //освобождение памяти на рекурсивном возврате
}

//
//void NaturalMergeSort(int* a, int n, long long& osn, long long& vsp, long long& memory)
//{
//    int split;
//    int end, * p = a, * tmp;
//    bool flag = 0, sorted = 0;
//    int pos1, pos2, pos3;
//    tmp = (int*)malloc(n * sizeof(int));
//    memory += 7 * sizeof(int) + 2 * sizeof(bool) + n * sizeof(int);
//    do
//    {
//        end = n; pos2 = pos3 = 0;
//        do
//        {
//            p += pos2; end = n - pos3;
//            for (split = 1; ++vsp && split < end && ++osn && p[split - 1] <= p[split]; split++);
//            if (++vsp && split == n) 
//            { 
//                sorted = 1; 
//                break; 
//            }
//            pos1 = 0; pos2 = split;
//
//            while (++vsp && pos1 < split && ++vsp && pos2 < end)
//            {
//                if (++osn && p[pos1] < p[pos2])
//                    tmp[pos3++] = p[pos1++];
//                else
//                {
//                    tmp[pos3++] = p[pos2++];
//                    if (++osn && p[pos2] < p[pos2 - 1]) break;
//                }
//            }
//            
//            while (++vsp && pos2 < end && ++osn && tmp[pos3 - 1] <= p[pos2]) 
//            { 
//                tmp[pos3++] = p[pos2++];
//            }
//
//            while (++vsp && pos1 < split) 
//            { 
//                tmp[pos3++] = p[pos1++];
//            }
//
//        } while (++vsp && pos3 < n);
//
//        if (++vsp && sorted) break;
//        p = tmp;
//        tmp = a;
//        a = p;
//        flag = !flag;
//
//    } while (++vsp && split < n);
//
//    if (++vsp && flag)
//    {
//        for (pos1 = 0; ++vsp && pos1 < n; pos1++) 
//        {
//            tmp[pos1] = a[pos1];
//        }
//        free(a);
//    }
//    else
//        free(tmp);
//}

void test_sort(int* n, int size, int i)
{
    long long osn = 0, vsp = 0, memory = 0;
    double  start = 0, end = 0;
    start = clock();
    switch (i)
    {
    case 1: 
        BubbleSort(n, size, osn, vsp, memory); break;
    case 2: 
        ShakerSort(n, size, osn, vsp, memory); break;
    case 3: 
        QuickSort(n, size, osn, vsp, memory); break;
    case 4: 
        /*NaturalMergeSort(n, size, osn, vsp, memory); break;*/
        BubbleSort2(n, size, osn, vsp, memory); break;
    }
    end = clock();
    double result = end - start;
    cout << setw(22) << osn << "|" << setw(30) << vsp << "|" << setw(13) << result << "|" << setw(17) << memory << "|" << endl;
}

void print_inf(int* n, int size)
{
    int* n1 = new int[size];//создаем массив под копию основного массива
    for (int i = 0; i < size; i++) { n1[i] = n[i]; } //копируем элементы

    for (int i = 1; i < 5; i++) //проводим сортировки исходного массива для всех заданных алгоритмов сортировки
    {
        switch (i)
        {
        case 1:
            cout << "Сортировка пузырьком."; break;
        case 2:
            cout << "Шейкерная сортировка."; break;
        case 3:
            cout << "Быстрая сортировка."; break;
        case 4:
            /*cout << "Сортировка естественным слиянием."; break;*/
            cout << "С фиксацией места" << endl;
        }

        cout << " Количество элементов - " << size << endl;
        cout << "----------------------------------------------------------------------------------------------------------" << endl;
        cout << "|" << setw(18) << "Случай" << "|" << setw(22) << "Основные сравнения:" << "|" << 
            setw(30) << "Вспомогательные сравнения:" << "|" << setw(13) << "Время(мс):" << "|" << 
            setw(17) << "Память(байты):" << "|" << endl;
        cout << "----------------------------------------------------------------------------------------------------------" << endl;

        cout << "|" << setw(18) << "Неупорядоченный" << "|";
        test_sort(n, size, i);

        cout << "|" << setw(18) << "По возрастанию" << "|";
        test_sort(n, size, i);

        reverse(n, n + size);//переставляем элементы массива в обратный порядок
        cout << "|" << setw(18) << "По убыванию" << "|";
        test_sort(n, size, i);//сортируем упорядоченный в обратном порядке массив
        cout << "----------------------------------------------------------------------------------------------------------" << endl;
        cout << "\n\n" << endl;

        for (int j = 0; j < size; j++) { n[j] = n1[j]; } //в исходный массив переносим исходные числа из копии 
    }

    delete[] n1;//очищаем память вспомогательного массива
}

void run_algorithms()
{
    int* n;

    n = read_file(filename, N1); print_inf(n, N1); delete[] n;

    n = read_file(filename, N2); print_inf(n, N2); delete[] n;

    n = read_file(filename, N3); print_inf(n, N3); delete[] n;

    n = read_file(filename, N4); print_inf(n, N4); delete[] n;
}

void create_file(int n, int count)
{
    int* res = new int[n];
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(10000000, 99999999);
    int k = 0;
    for (int i = 0; i < n / count; ++i)
    {
        int num = dist(rng);
        for (int j = 0; j < count; ++j)
        {
            res[k++] = num;
        }
    }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(res, res + n - 1, default_random_engine(seed));
    ofstream f("test_" + to_string(count) + ".txt");
    for (int i = 0; i < n; ++i)
    {
        f << res[i] << " ";
        if ((i + 1) % 10 == 0) f << "\n";
    }
    f.close();
    cout << "Файл " << "test_" << count << ".txt" << " успешно создан." << endl;
    delete[] res;
}

void run_algorithms_2()
{
    int* n;

    cout << "\nВ массиве 10 повторяющихся элементов" << endl;
    n = read_file(test1, N4); print_inf(n, N4); delete[] n;

    cout << "В массиве 100 повторяющихся элементов" << endl;
    n = read_file(test2, N4); print_inf(n, N4); delete[] n;

    cout << "В массиве 500 повторяющихся элементов" << endl;
    n = read_file(test3, N4); print_inf(n, N4); delete[] n;

    cout << "В массиве 1000 повторяющихся элементов" << endl;
    n = read_file(test4, N4); print_inf(n, N4); delete[] n;
}

int main()
{
    int menu = 0;
    setlocale(LC_ALL, "Rus");
    do {
        system("cls");
        cout << "1. Запустить алгоритмы без повторов ключей" << endl;
        cout << "2. Запустить алгоритмы с повторами ключей" << endl;
        cout << "3. Выход" << endl;
        cin >> menu;
        if (cin.fail()) // проверка на ошибку при вводе
        {
            cin.clear(); // очищает флаг ошибки в потоке ввода
            cin.seekg(0, ios::beg); // перемещает указатель в потоке ввода в начало (откуда можно повторно считывать данные)
        }
        switch (menu)
        {
        case 1:
            system("cls");
            run_algorithms(); // запускаем тесты для алгоритмов c N1 N2 N3 N4 количесством элементов
            system("pause");
            break;
        case 2:
            system("cls");
            create_file(150000, 10);
            create_file(150000, 100);
            create_file(150000, 500);
            create_file(150000, 1000);
            run_algorithms_2();
            system("pause");
            break;
        }
    } while (menu != 3);
    return 0; 
}
