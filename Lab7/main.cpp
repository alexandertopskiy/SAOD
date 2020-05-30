//Лабораторная работа №7 (Раздел 1, Тема 4, Номер 1) - ЛИНЕЙНЫЙ ДИНАМИЧЕСКИЙ ДВУНАПРАВЛЕННЫЙ СПИСОК

#include <iostream>
#include <cstdlib>

using namespace std;

int num1; //кол-во элементов в списке, ИСКЛЮЧИТЕЛЬНО ДЛЯ ВЫВОДА ИНФОРМАЦИИ ПОЛЬЗОВАТЕЛЮ,
          // в функциях важной роли не играет

//метод обработки ошибок ввода команды (проверяет, чтобы были введены ТОЛЬКО цифры, без букв).
// возвращает ПРАВИЛЬНО ВВЕДЕННОЕ ЧИСЛО
int failure() {
    int a;
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД \n" << endl;
    }
    //    cin.ignore(32767, '\n');
    return a;
}

//ОПИСАНИЕ СТРУКТУРЫ ДИНАМИЧЕСКИЙ СПИСОК
struct Dynamic2List {
    string value; //строка-значение
    Dynamic2List *right, *left; //ссылочные переменные-указатели на соседние элементы
} *Head; //Head - заголовок списка

//инициализация-создание пустого списка
inline void initList() {
    Head = new Dynamic2List(); //выделяется память под заголовок
    Head -> left = Head; // оба ссылочных поля заголовка устанавливаются в адрес самого заголовка
    Head -> right = Head;
    Head -> value = "HEAD";
    num1 = 0; // счетчик числа элементов, ИСКЛЮЧИТЕЛЬНО ДЛЯ ВЫВОДА ИНФОРМАЦИИ ПОЛЬЗОВАТЕЛЮ, в функциях важной роли не играет
}

// Проверка пустоты списка
bool isListEmpty(){
    if (Head->right == Head) //если ссылочная часть right у заголовка по прежнему указывает на самого себя (c момента инициализации)
        return 1;
    else return 0;
}

//Проход по списку и вывод состояния
void showList() {
    cout << "\nСостояние списка: ";
    if (!isListEmpty()) { //проверить, в списке есть элементы?
        cout << "в списке " << num1 << " элементов\n";
        int choice = -1; // выбор, куда добавлять
        while ((choice != 0) && (choice != 1)){
            cout <<"\n В каком направлении вывести элементы списка?\n 0 - В прямом\n 1 - В обратном\n\n Введите номер команды: ";
            choice = failure(); //ввод номера команды c проверкой на ошибку
            Dynamic2List *Current; //ввод вспомогательной ссылочной переменной
            int i; //номер элемента списка
            string leftlink, rightlink; //на что ссылается (value следующего)
            if (choice == 0) { // ВЫВОД В ПРЯМОМ НАПРАВЛЕНИИ
                i = 1;
                Current = Head -> right; //установка Current в адрес первого реального элемента
                while (Current != Head) {
                    rightlink = (Current -> right) -> value;
                    leftlink = (Current -> left) -> value;
                    cout << i << ") " << Current -> value << ", левый сосед: " << leftlink  << ", правый сосед: " << rightlink  << "\n";
                    Current = Current -> right;
                    i++;
                }
            }
            else if (choice == 1) { // ВЫВОД В ОБРАТНОМ НАПРАВЛЕНИИ
                i = num1;
                Current = Head -> left; //установка Current в адрес последнего элемента
                while (Current != Head) {
                    rightlink = (Current -> right) -> value;
                    leftlink = (Current -> left) -> value;
                    cout << i << ") " << Current -> value << ", левый сосед: " << leftlink  << ", правый сосед: " << rightlink  << "\n";
                    Current = Current -> left;
                    i--;
                }
            }
            else {cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ\n"; choice = -1;}
        }
    }
    else cout << "СПИСОК ПУСТОЙ\n";
}

//Добавление элемента в список
void push(){
    string _value;
    Dynamic2List *Current = nullptr; //ввод вспомогательной ссылочной переменной
    Dynamic2List *Temp = new Dynamic2List; //объявление вспомогательной ссылочной переменной (для нового элемента)
    int choice = -1; // выбор, куда добавлять
    while ((choice != 0) && (choice != 1)){
        cout <<"\n Куда добавить элемент?\n 0 - Перед заданным элементом\n 1 - После заданного элемента\n\n Введите номер команды: ";
        choice = failure(); //ввод номера команды c проверкой на ошибку
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int i = -1; // i - индикатор для поиска (пока элемент не будет найден, пользователь будет вводить новые значения)
        if (choice == 0) { // ДОБАВЛЕНИЕ ПЕРЕД ЗАДАННЫМ ЭЛЕМЕНТОМ
            if (!isListEmpty()) {
                while (i == -1){
                    Current = Head -> right; //установка Current в адрес первого реального элемента
                    cout << "\n Введите значение элемента, ПЕРЕД КОТОРЫМ вы хотите добавить новый элемент: "; cin.clear(); getline(cin, _value);
                    while ((Current != Head) && (Current -> value != _value))
                        Current = Current -> right;
                    if (Current != Head) {
                        i++;
                        Temp -> right = Current;
                        Temp -> left = Current -> left;
                        (Current -> left) -> right = Temp;
                        Current -> left = Temp;
                    }
                    else cout << " Строка " << _value << " не найдена. Попробуйте ввести другое значение\n";
                }
            }
            else {cout << "\nОПЕРАЦИЮ 'ДОБАВИТЬ ПЕРЕД' НЕЛЬЗЯ ПРИМЕНИТЬ ДЛЯ ПУСТОГО СПИСКА. ВЫБЕРИТЕ ДРУГУЮ КОМАНДУ\n"; choice = -1; }
        }
        else if (choice == 1) { // ДОБАВЛЕНИЕ ПОСЛЕ ЗАДАННОГО ЭЛЕМЕНТА
            if (!isListEmpty()){
                while (i == -1) {
                    Current = Head -> right; //установка Current в адрес первого реального элемента
                    cout << "\n Введите значение элемента, ПОСЛЕ КОТОРОГО вы хотите добавить новый элемент: "; cin.clear(); getline(cin, _value);
                    while ((Current != Head) && (Current -> value != _value))
                        Current = Current -> right;
                    if (Current != Head) {
                        i++;
                        Temp -> right = Current -> right;
                        Temp -> left = Current;
                        (Current -> right) -> left = Temp;
                        Current -> right = Temp;
                    }
                    else cout << " Строка " << _value << " не найдена. Попробуйте ввести другое значение\n";
                }
            }
            else { //иначе - просто добавить первым элементом
//                cout << "\nList is empty\n";
                Temp -> right = Head; Temp -> left = Head;
                Head -> right = Temp; Head -> left = Temp;
            }
        }
        else { cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ\n"; choice = -1; }
    }
    cout << "\n Введите добавляемую строку: "; cin.clear(); getline(cin, _value);
    Temp -> value = _value; num1++; cout << "\n Элемент успешно добавлен! \n";
}

//Удаление элемента из списка
void pop(){
    if (!isListEmpty()){
        string _value;
        Dynamic2List *Current; //ввод вспомогательной ссылочной переменной
        Current = Head -> right; //установка Current в адрес первого реального элемента
        int i = -1; // i - индикатор для поиска (пока элемент не будет найден, пользователь будет вводить новые значения)
        showList();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (i == -1) {
            cout << "\n Введите значение элемента, который хотите удалить: "; cin.clear(); getline(cin, _value);
            while ((Current != Head) && (Current -> value != _value))
                Current = Current -> right;
            if (Current != Head) {
                i++; cout << " Строка " << _value << " найдена \n";
                (Current -> left) -> right = Current -> right; // меняем правый указатель у левого соседа удаляемого элемента
                (Current -> right) -> left = Current -> left; // меняем левый указатель у правого соседа
                delete Current; //обработать удаленный элемент, например - освободить занимаемую им память
                num1--;
                cout << "\nЭлемент '" << Current -> value << "' удален из списка. Теперь в списке " << num1 <<" элементов\n";
            }
            else cout << " Строка " << _value << " не найдена\n";
        }
    }
    else cout << "\nУДАЛЯТЬ НЕЧЕГО. СПИСОК ПУСТ.\n";
}

//Поиск элемента с заданной информационной частью
void find() {
    if (!isListEmpty()){ //проверить возможности удаления (в списке есть элементы?)
        string _value;
        cout << "\n Введите строку, которую хотите найти: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, _value);
        int choice = -1, i; // choice - выбор, куда добавлять, i - индекс найденного элемента
        Dynamic2List *Current; //ввод вспомогательной ссылочной переменной
        while ((choice != 0) && (choice != 1)){
            cout <<"\n В каком направлении произвести поиск элемента?\n 0 - В прямом\n 1 - В обратном\n\n Введите номер команды: ";
            choice = failure(); //ввод номера команды c проверкой на ошибку
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice == 0) {
                i = 1;
                Current = Head -> right; //установка Current в адрес первого реального элемента
                while ((Current != Head) && (Current -> value != _value)){
                    Current = Current -> right;
                    i++;
                }
                if (Current != Head) cout << " Строка " << _value << " найдена под номером "<< i << "\n";
                else cout << " Строка " << _value << " не найдена\n";
            }
            else if (choice == 1){
                i = num1;
                Current = Head -> left; //установка Current в адрес последнего реального элемента
                while ((Current != Head) && (Current -> value != _value)){
                    Current = Current -> left;
                    i--;
                }
                if (Current != Head) cout << " Строка " << _value << " найдена под номером "<< i << "\n";
                else cout << " Строка " << _value << " не найдена\n";
            }
            else {
                cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ\n"; choice = -1;
            }
        }
    }
    else {
        cout << "\nИСКАТЬ НЕЧЕГО. СПИСОК ПУСТ.\n";
    }
}

//Очистка списка перед завершением работы программы (освобождение памяти)
inline void ClearList(){
    cout << "\nВЫПОЛНЯЕТСЯ ОЧИСТКА СПИСКА...\n";
    Dynamic2List *Current; //ввод вспомогательной ссылочной переменной
    (Head -> left) -> right = NULL; //заносим в указалель right последнего элемента NULL, чтобы пройти по всему списку
    while (Head != NULL) { //пока указатель right заголовка не будет указывать на него самого (т.е. список пуст)
        Current = Head;
        Head = Head -> right;
        delete Current; //особождение памяти
    }
    cout << "\nСПИСОК ОЧИЩЕН...\n";
}

void menu() {
    int number;
    string value;
    while (true) {
        cout << "___________________________________________________________\n";
        cout << "\nВыберите команду из списка:\n";
        cout << "1. Вывод текущего состояния списка на экран\n";
        cout << "2. Проверка пустоты списка\n";
        cout << "3. Добавить элемент в список\n";
        cout << "4. Удалить элемент из списка\n";
        cout << "5. Поиск элемента с заданной информационной частью\n";
        cout << "6. Очистить список\n";
        cout << "0. Завершить работу программы\n";
        cout <<"Номер команды: ";
        number = failure();
        if (number == 1) showList(); //1. Вывод текущего состояния списка на экран
        else if (number == 2){ //2. Проверка пустоты списка
            if (isListEmpty() == 1) cout << "\nПРОВЕРКА СПИСКА НА ПУСТОТУ... СПИСОК ПУСТОЙ\n";
            else cout << "\nПРОВЕРКА СПИСКА НА ПУСТОТУ... СПИСОК НЕ ПУСТОЙ\n";
        }
        else if (number == 3) push(); //3. Добавить элемент в список
        else if (number == 4) pop(); //4. Удалить элемент из списка
        else if (number == 5) find(); //5. Поиск элемента с заданной информационной частью
        else if (number == 6) { //6. Очистить список
            ClearList();
            initList(); //повторная инициалиция, создание пустого списка
        }
        else if (number == 0) {//0. Завершить работу
            ClearList(); //очистка списка
            cout << "\nВЫХОД ИЗ ПРОГРАММЫ...\n\n";
            break;
        }
        else cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ\n";
    }
}

int main() {
    initList(); //инициализация пустого списка
    menu(); //организация диалогового цикла с пользователем
    //system("read -n1 -p ' ' key"); //system("pause");
    return 0;
}