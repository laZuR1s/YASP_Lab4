//5. Заменить каждое число на корень из суммы квадрата текущего числа
//и квадрата первого числа.Ответ округлить до целых.
//Лазарев Александр 9 группа

import Vector;
import <vector>;
import <Windows.h>;
import <iostream>;
import <fstream>;
import <string>;
import <algorithm>;

std::fstream file_gen_for(std::string filename, int N, int M)
{
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::trunc);
    if (file.is_open())
    {
        for (int i = 0; i < N; ++i)
        {
            file << (rand() % (M - (-1 * M) + 1) + (-1 * M));
            file << " ";
        }
        file.seekg(0);
    }
    else std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
    return file;
}

std::fstream file_gen_gen(std::string filename, int N, int M)
{
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::trunc);
    if (file.is_open())
    {

        std::generate_n(std::ostream_iterator<int>(file, " "), N, [M]() { return (rand() % (M - (-1 * M) + 1) + (-1 * M)); });  //
        file.seekg(0);

    }
    else std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
    return file;
}

void read_and_check(int& input, int min = 0, int max = MAXINT)
{
    std::cout << "-> ";
    while (!(std::cin >> input) || input > max || input < min)
    {
        std::cout << "Ошибка ввода!\n";
        std::cin.clear();
        std::cin.ignore(255, '\n');
        std::cout << "-> ";
    }
}

std::string get_file_name()
{
    const std::string CANT = "'|\"\\/*:?<>+%!@";
    std::string fname;
    bool flag;
    while (true)
    {
        flag = true;
        std::cout << "Введите имя файла: ";
        std::cin >> fname;
        for (char a : fname)
        {
            for (char b : CANT)
                if (a == b)
                {
                    flag = false;
                    break;
                }
            if (!flag) break;
        }
        if (flag) break;
        else std::cout << "Неверное имя файла!\n";
    }

    return fname;
}

int fill_menu()
{
    std::cout << "Выберите способ заполнения файла\n"
        << "1. Используя цикл\n"
        << "2. Используя generate_n\n";
    int choice{};
    read_and_check(choice, 1, 2);
    return choice;
}

int action_menu()
{
    std::cout << "Выберите действие\n"
        << "1. Модифицировать список\n"
        << "2. Найти сумму элементов списка\n"
        << "3. Найти среднее арифметическое элементов списка\n"
        << "4. Вывести контейнер\n"
        << "5. Завершить работу с данным списком\n";
    int choice{};
    read_and_check(choice, 1, 5);
    return choice;
}

int mod_menu()
{
    std::cout << "Выберите вариант modify\n"
        << "1.for\n"
        << "2.transform\n"
        << "3.for_each\n";
    int choice{};
    read_and_check(choice, 1, 3);
    return choice;
}

std::pair<std::vector<int>::iterator, std::vector<int>::iterator> get_borders(VECTOR& vector)
{
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> result;
    while (true)
    {
        int left{}, right{};
        std::cout << "Введите порядковый номер первого элемента.\n";
        read_and_check(left, 0);
        std::cout << "Введите порядковый номер последнего элемента не включительно.\n";
        read_and_check(right, 0);
        if (left > right && right)
            std::cout << "Ввод некорректен\n";
        else
        {
            if (!left)
                result.first = vector.begin();
            else
                result.first = vector.get_iterator(left);
            if (!right)
                result.second = vector.end();
            else
                result.second = vector.get_iterator(right);
            break;
        }
    }
    return result;
}

std::vector<int> mod(VECTOR& vector)
{
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> borders = get_borders(vector);
    int choice = mod_menu();
    if (choice == 1)
        return vector.modify_for(borders.first, borders.second);
    if (choice == 2)
        return vector.modify_transform(borders.first, borders.second);
    return vector.modify_foreach(borders.first, borders.second);
}

int output_menu()
{
    std::cout << "Выберите способ вывода контейнера\n"
        << "1. В консоль\n"
        << "2. В файл\n";
    int choice{};
    read_and_check(choice, 1, 2);
    return choice;
}




int main()
{
    SetConsoleOutputCP(1251);
    srand(GetTickCount64());

    while (true)
    {
        std::cout << "Введите количество чисел в файле: ";
        int N{};
        read_and_check(N, 1);
        std::cout << "Введите границы генерации: ";
        int M{};
        read_and_check(M, 1);
        std::string file_name = get_file_name();
        std::fstream file = fill_menu() == 1 ? file_gen_for(file_name, N, M) : file_gen_gen(file_name, N, M);
        VECTOR vector; 
        vector.fill(file);
        file.close();
        std::cout << "Получившийся список:";  vector.print(); std::cout << std::endl;
        bool flag = true;
        while (flag)
        {
            switch (action_menu())
            {
            case 1: // modify
            {
                std::vector<int> mod_vector = mod(vector);
                if (mod_vector.empty())
                    std::cout << "Модифицированный контейнер пуст";
                else
                    for (int elem : mod_vector)
                        std::cout << elem << ' ';
                std::cout << '\n';
                break;
            }

            case 2: // sum
                std::cout << "Сумма равна " << vector.sum() << '\n';
                break;

            case 3: // average
                std::cout << "Среднее арифметическое равно " << vector.average() << '\n';
                break;

            case 4: // print
                if (output_menu() == 1)
                    vector.print(std::cout);
                else
                {
                    file_name = get_file_name();
                    std::ofstream file(file_name);
                    vector.print(file);
                }
                break;

            case 5:
                flag = false;
                break;
            }
        }
        char is_exit{};
        std::cout << "Завершить выполнение программы? Y/любая другая клавиша: ";
        std::cin >> is_exit;
        if (is_exit == 'Y' || is_exit == 'y')
            break;
    }
}