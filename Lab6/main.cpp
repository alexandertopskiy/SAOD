//Лабораторная работа №6 (Раздел 1, Тема 3, Номер 5)
// ЛИНЕЙНЫЙ ДИНАМИЧЕСКИЙ СПИСОК + УДАЛЕНИЕ-ПЕРЕМЕЩЕНИЕ ВО ВСПОМОГАТЕЛЬНЫЙ СТЕК

#include <iostream>
#include <cstdlib>

using namespace std;

int num1, num2; //кол-во элементов в списке, ИСКЛЮЧИТЕЛЬНО ДЛЯ ВЫВОДА ИНФОРМАЦИИ ПОЛЬЗОВАТЕЛЮ,
                // в функциях важной роли не играет

int failure();
inline void initList(); inline void initStack();
bool isListEmpty(); bool isStackEmpty();
void showList(); void showStack();
void push(); void pop(); void find();
inline void ClearList(); inline void ClearStack();
void menu();

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
    return a;
}

//ОПИСАНИЕ СТРУКТУРЫ ДИНАМИЧЕСКИЙ СПИСОК
struct DynamicList {
    string value; //строка-значение
    DynamicList *next; //ссылочная переменная-указатель
} *Head, *StackTop; //Head- заголовок списка, StackTop - вершина стека

//инициализация-создание пустого списка
inline void initList() {
    Head = new DynamicList(); //заголовок
    Head -> next = NULL;// занесение в ссылочную часть заголовка пустого указателя null
    num1 = 0; // счетчик числа элементов, ИСКЛЮЧИТЕЛЬНО ДЛЯ ВЫВОДА ИНФОРМАЦИИ ПОЛЬЗОВАТЕЛЮ, в функциях важной роли не играет
}
//инициализация вспомогательного стека (пустого)
inline void initStack() {
    StackTop = new DynamicList();
    StackTop -> next = NULL; //создаем пустой вспомогательный список (стек)
    num2 = 0; // счетчик числа элементов, ИСКЛЮЧИТЕЛЬНО ДЛЯ ВЫВОДА ИНФОРМАЦИИ ПОЛЬЗОВАТЕЛЮ, в функциях важной роли не играет
}

// Проверка пустоты списка
bool isListEmpty(){
    if (Head->next == NULL)  //если ссылочную часть next у заголовка по прежнему null (c момента инициализации)
        return 1;
    else
        return 0;
}
// Проверка пустоты вспомогательного стека
bool isStackEmpty(){
    if (StackTop->next == NULL)  //если ссылочную часть next у вершины по прежнему null (c момента инициализации)
        return 1;
    else
        return 0;
}

//Проход по списку и вывод состояния
void showList() {
    cout << "\nСостояние списка: ";
    if (!isListEmpty()) { //проверить возможности удаления (в списке есть элементы?)
        cout << "в списке " << num1 << " элементов\n";
        DynamicList *Current; //ввод вспомогательной ссылочной переменной
        Current = Head -> next; //установка Current в адрес первого реального элемента
        int i = 1;
        string linkon; //на что ссылается (value следующего)
        while (Current != NULL) {
            if ((Current -> next) != NULL) linkon = (Current -> next) -> value;
            else linkon = "NULL";
            cout << i << ") " << Current -> value << ", ссылается на: " << linkon  << "\n";
            Current = Current -> next;
            i++;
        }
    }
    else
        cout << "СПИСОК ПУСТОЙ\n";
}
//Проход по вспомогательному стеку и вывод его состояния
void showStack() {
    cout << "\nСостояние стека удаленных элементов: ";
    if (!isStackEmpty()) { //проверить возможности удаления (в списке есть элементы?)
        cout << "в стеке " << num2 << " элементов\n";
        DynamicList *Current; //ввод вспомогательной ссылочной переменной
        Current = StackTop -> next; //установка Current в адрес первого реального элемента вспомогательного стека
        int i = 1;
        string linkon; //на что ссылается (value следующего)
        while (Current != NULL) {
            if ((Current -> next) != NULL) linkon = (Current -> next) -> value;
            else linkon = "NULL";
            cout << i << ") " << Current -> value << ", ссылается на: " << linkon  << "\n";
            Current = Current -> next;
            i++;
        }
    }
    else
        cout << "ВСПОМОГАТЕЛЬНЫЙ СТЕК ПУСТОЙ\n";
}

//Добавление элемента в список
void push(){
    string _value;
    DynamicList *Current = nullptr; //ввод вспомогательной ссылочной переменной
    DynamicList *Temp = new DynamicList; //ввод вспомогательной ссылочной переменной (для нового элемента)
    int choice = -1; // выбор, куда добавлять
    while ((choice != 0) && (choice != 1)){
        cout <<"\n Куда добавить элемент?\n 0 - Перед заданным элементом\n 1 - После заданного элемента\n\n Введите номер команды: ";
        choice = failure(); //ввод номера команды c проверкой на ошибку
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int i = -1; // i - индикатор для поиска (пока элемент не будет найден, пользователь будет вводить новые значения)
        if (choice == 0) { // ДОБАВЛЕНИЕ ПЕРЕД ЗАДАННЫМ ЭЛЕМЕНТОМ
            if (!isListEmpty()) {
                DynamicList *Pred; //ввод вспомогательной ссылочной переменной (предшествующей Current)
                Pred = Head; //установка в заголовок (тогда как current идет с первого РЕАЛЬНОГО элемента)
                while (i == -1){
                    Current = Head -> next; //установка Current в адрес первого реального элемента
                    cout << "\n Введите значение элемента, ПЕРЕД КОТОРЫМ вы хотите добавить новый элемент: "; cin.clear(); getline(cin, _value);
                    while (Current != NULL) {
                        if (Current -> value == _value) break;
                        Current = Current -> next;
                        Pred = Pred -> next;
                    }
                    if (Current != NULL) i++;
                    else { cout << " Строка " << _value << " не найдена. Попробуйте ввести другое значение\n"; }
                }
                Temp -> next = Current; //формирование полей нового элемента, в частности – настройка ссылочной части
                Pred -> next = Temp; //изменение ссылочной части элемента-предшественника на адрес нового элемента
            }
            else {
                cout << "\nОПЕРАЦИЮ 'ДОБАВИТЬ ПЕРЕД' НЕЛЬЗЯ ПРИМЕНИТЬ ДЛЯ ПУСТОГО СПИСКА. ВЫБЕРИТЕ ДРУГУЮ КОМАНДУ\n"; choice = -1;
            }
        }
        else if (choice == 1) { // ДОБАВЛЕНИЕ ПОСЛЕ ЗАДАННОГО ЭЛЕМЕНТА
            if (!isListEmpty()){
                while (i == -1) {
                    Current = Head -> next; //установка Current в адрес первого реального элемента
                    cout << "\n Введите значение элемента, ПОСЛЕ КОТОРОГО вы хотите добавить новый элемент: "; cin.clear(); getline(cin, _value);
                    while ((Current != NULL) && (Current -> value != _value))
                        Current = Current -> next;
                    if (Current != NULL) i++;
                    else { cout << " Строка " << _value << " не найдена. Попробуйте ввести другое значение\n"; }
                }
                Temp -> next = Current -> next; //формирование полей нового элемента, в частности – настройка ссылочной части
                Current -> next = Temp; //изменение ссылочной части текущего элемента на адрес нового элемента
            }
            else { //иначе - просто добавить первым элементом
                Temp -> next = NULL;
                Head -> next = Temp;
            }
        }
        else {
            cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ\n"; choice = -1;
        }
    }
    cout << "\n Введите добавляемую строку: "; cin.clear(); getline(cin, _value);
    cout << "\n Элемент успешно добавлен! \n"; Temp -> value = _value; num1++;
}

//Удаление элемента из списка
void pop(){
    if (!isListEmpty()){
        string _value;
        DynamicList *Current; //ввод вспомогательной ссылочной переменной
        DynamicList *Pred; //ввод вспомогательной ссылочной переменной (предшествующей Current)
        Current = Head -> next; //установка Current в адрес первого реального элемента
        Pred = Head; //установка в заголовок (тогда как current идет с первого РЕАЛЬНОГО элемента)
        int choice = -1; // выбор, куда добавлять
        int i = -1; // i - индикатор для поиска (пока элемент не будет найден, пользователь будет вводить новые значения)
        while ((choice != 0) && (choice != 1)){
            cout <<"\n Действительно удалить элемент или добавить во вспомогательный стек?\n 0 - Удалить с освобождением памяти\n 1 - Добавить во вспомогательный стек\n\n Введите номер команды: ";
            choice = failure(); //ввод номера команды c проверкой на ошибку
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            showList();
            while (i == -1) {
                cout << "\n Введите значение элемента, который хотите удалить: "; cin.clear(); getline(cin, _value);
                while (Current != NULL) {
                    if (Current -> value == _value) break;
                    Current = Current -> next;
                    Pred = Pred -> next;
                }
                if (Current != NULL) { i++; cout << " Строка " << _value << " найдена под номером "<< i << ")\n"; }
                else { cout << " Строка " << _value << " не найдена\n"; }
            }
            if (choice == 0) {
                Pred -> next = Current -> next; //изменение связующей части элемента-предшественника на значение связующей части удаляемого элемента
                delete Current; //обработать удаленный элемент, например - освободить занимаемую им память
                num1--;
                cout << "\nЭлемент '" << Current -> value << "' удален из списка. Теперь в списке " << num1 <<" элементов\n";
            }
            else if (choice == 1) {
                Pred -> next = Current -> next; //основной список: изменение связующей части элемента-предшественника на значение связующей части удаляемого элемента
                DynamicList *Temp = Current; //ввод вспомогательной ссылочной переменной (для нового элемента в стеке)
                Temp -> next = StackTop -> next;
                StackTop -> next = Temp;
                num1--; num2++;
                cout << "\nЭлемент '" << Current -> value << "' удален из списка. Теперь в основном списке " << num1 <<" элементов, а во вспомогательном - "<< num2 << " \n";
            }
            else {
                cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ\n"; choice = -1;
            }
        }
    }
    else {
        cout << "\nУДАЛЯТЬ НЕЧЕГО. СПИСОК ПУСТ.\n";
    }
}

//Поиск элемента с заданной информационной частью
void find() {
    if (!isListEmpty()){ //проверить возможности удаления (в списке есть элементы?)
        showList();
        string _value;
        cout << "\n Введите строку, которую хотите найти: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, _value);
        int i = 1;
        DynamicList *Current; //ввод вспомогательной ссылочной переменной
        Current = Head -> next; //установка Current в адрес первого реального элемента
        while ((Current != NULL) && (Current -> value != _value)){
            Current = Current -> next;
            i++;
        }
        if (Current != NULL) cout << " Строка " << _value << " найдена под номером "<< i << "\n";
        else cout << " Строка " << _value << " не найдена\n";
    }
    else {
        cout << "\nИСКАТЬ НЕЧЕГО. СПИСОК ПУСТ.\n";
    }
}

//Очистка списка перед завершением работы программы (освобождение памяти)
inline void ClearList(){
    cout << "\nВЫПОЛНЯЕТСЯ ОЧИСТКА СПИСКА...\n";
    DynamicList *Current; //ввод вспомогательной ссылочной переменной
    while (Head != NULL) { //особождение памяти, занятой под основной список
        Current = Head;
        Head = Head -> next;
        delete Current;
    }
    initList(); //повторная инициалиция, создание пустого списка
    cout << "\nСПИСОК ОЧИЩЕН...\n";
}
//Очистка вспомогательного стека перед завершением работы программы (освобождение памяти)
inline void ClearStack() {
    cout << "\nВЫПОЛНЯЕТСЯ ОЧИСТКА ВСПОМОГАТЕЛЬНОГО СТЕКА...\n";
    DynamicList *Current; //ввод вспомогательной ссылочной переменной
    while (StackTop != NULL) { //особождение памяти, занятой под вспомогательный список (стек)
        Current = StackTop;
        StackTop = StackTop -> next;
        delete Current;
    }
    initStack(); //повторная инициалиция, создание пустого вспомогательного стека
    cout << "\nСТЕК ОЧИЩЕН...\n";
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
        cout << "6. Вывод текущего состояния вспомогательного стека на экран\n";
        cout << "7. Очистить список\n";
        cout << "8. Очистить вспомогательный стек\n";
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
        else if (number == 6) showStack(); //6. Вывод текущего состояния вспомогательного стека на экран
        else if (number == 7) ClearList(); //7. Очистить список
        else if (number == 8) ClearStack(); //8. Очистить стек
        else if (number == 0) {//0. Завершить работу
            ClearList(); //очистка списка
            ClearStack(); //очистка стека
            cout << "\nВЫХОД ИЗ ПРОГРАММЫ...\n\n";
            break;
        }
        else cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ\n";
    }
}

int main() {
    initList(); //инициализация пустого списка
    initStack(); //инициализация пустого вспомогательного стека (удаляемых элементов)
    menu(); //организация диалогового цикла с пользователем
    return 0;
}