//Лабораторная работа №8 (Раздел 1, Тема 4, Номер 3) - СПИСОК СПИСКОВ

#include <iostream>
#include <cstdlib>

using namespace std;

int num1; //кол-во списков списков, ИСКЛЮЧИТЕЛЬНО ДЛЯ ВЫВОДА ИНФОРМАЦИИ ПОЛЬЗОВАТЕЛЮ, в функциях важной роли не играет

//ОПИСАНИЕ СТРУКТУРЫ ЭЛЕМЕНТОВ ВСПОМОГАТЕЛЬНОГО (ДИНАМИЧЕСКОГО) СПИСКА
struct SubList {
    string value; //строка-значение
    SubList *next; //ссылочная переменная-указатель на следующий элемент
}; //Head не нужен, т.к заголовгом вспомогательного списка будет элемент основного списка

//СТРУКТУРА ЭЛЕМЕНТОВ ОСНОВНОГО (ДИНАМИЧЕСКОГО) СПИСКА
struct MainList {
    MainList *nextMain; //ссылочная переменная-указатель на следующий элемент
    SubList *firstSub; //ссылочная переменная-указатель на адрес первого элемент всп.списка
} *HeadMain; //Head - заголовок базового списка

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

//инициализация-создание пустого ОСНОВНОГО списка
inline void initList() {
    HeadMain = new MainList(); //выделяем память под заголовок ОСНОВНОГО СПИСКА
    HeadMain -> nextMain = NULL;// занесение в ссылочную часть заголовка пустого указателя null
    HeadMain -> firstSub = NULL;
    num1 = 0; // счетчик числа элементов, ИСКЛЮЧИТЕЛЬНО ДЛЯ ВЫВОДА ИНФОРМАЦИИ ПОЛЬЗОВАТЕЛЮ, в функциях важной роли не играет
}

// Проверка пустоты главного списка
bool isMainListEmpty(){
    if (HeadMain -> nextMain == NULL)  //если ссылочную часть next у заголовка по прежнему null (c момента инициализации)
        return 1;
    else
        return 0;
}

// Проверка пустоты связанного списка
bool isSubListEmpty(MainList *CurrentMain){
    if (CurrentMain -> firstSub -> next == NULL)  //если ссылочную часть next у заголовка по прежнему null (c момента инициализации)
        return 1;
    else
        return 0;
}

//Проход по списку и вывод состояния
void showList() {
    cout << "\nСостояние списка: ";
    if (!isMainListEmpty()) { //проверить, есть ли в главном списке элементы?
        cout << "в списке " << num1 << " списков списков\n";
        MainList *MainCurrent = HeadMain -> nextMain; //установка Current в адрес первого реального элемента
        while (MainCurrent != NULL) {
            std::cout << "Содержимое элемента " << MainCurrent -> firstSub -> value << " основного списка:\n";
            int i = 1;
            if (!isSubListEmpty(MainCurrent)) {
                SubList *SubCurrent = MainCurrent -> firstSub -> next;
                while (SubCurrent != NULL) {
                    cout << "   " << i << ") " << SubCurrent -> value << "\n";
                    SubCurrent = SubCurrent -> next;
                    i++;
                }
            }
            else std::cout << "   " << "<Пусто>\n";
            MainCurrent = MainCurrent -> nextMain;
        }
    }
    else
        cout << "ГЛАВНЫЙ СПИСОК ПУСТОЙ\n";
}

//добавление нового элемента в список с пустым связанным списком
void pushInMain() {
    string _value;
    MainList *Current = nullptr; //ввод вспомогательной ссылочной переменной
    MainList *Temp = new MainList; //ввод вспомогательной ссылочной переменной (для нового элемента)
    Temp -> firstSub = new SubList;
    int choice = -1; // выбор, куда добавлять
    while ((choice != 0) && (choice != 1)){
        cout <<"\n Куда добавить элемент-список?\n 0 - Перед заданным элементом\n 1 - После заданного элемента\n\n Введите номер команды: ";
        choice = failure(); //ввод номера команды c проверкой на ошибку
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int i = -1; // i - индикатор для поиска (пока элемент не будет найден, пользователь будет вводить новые значения)
        if (choice == 0) { // ДОБАВЛЕНИЕ ПЕРЕД ЗАДАННЫМ ЭЛЕМЕНТОМ
            if (!isMainListEmpty()){
                MainList *Pred = HeadMain; //ввод вспомогательной ссылочной переменной (предшествующей Current) и установка в заголовок (тогда как current идет с первого РЕАЛЬНОГО элемента)
                while (i == -1){
                    Current = HeadMain -> nextMain; //установка Current в адрес первого реального элемента
                    cout << "\n Введите значение элемента, ПЕРЕД КОТОРЫМ вы хотите добавить новый элемент: "; cin.clear(); getline(cin, _value);
                    while (Current != NULL) {
                        if (Current -> firstSub -> value == _value) break;
                        Current = Current -> nextMain;
                        Pred = Pred -> nextMain;
                    }
                    if (Current != NULL) i++;
                    else { cout << " Строка " << _value << " не найдена. Попробуйте ввести другое значение\n"; }
                }
                Temp -> nextMain = Current; //формирование полей нового элемента, в частности – настройка ссылочной части
                Temp -> firstSub -> next = NULL;
                Pred -> nextMain = Temp; //изменение ссылочной части элемента-предшественника на адрес нового элемента
            }
            else {
                cout << "\nОПЕРАЦИЮ 'ДОБАВИТЬ ПЕРЕД' НЕЛЬЗЯ ПРИМЕНИТЬ ДЛЯ ПУСТОГО СПИСКА. ВЫБЕРИТЕ ДРУГУЮ КОМАНДУ\n"; choice = -1;
            }
        }
        else if (choice == 1) { // ДОБАВЛЕНИЕ ПОСЛЕ ЗАДАННОГО ЭЛЕМЕНТА
            if (!isMainListEmpty()){
                while (i == -1) {
                    Current = HeadMain -> nextMain; //установка Current в адрес первого реального элемента
                    cout << "\n Введите значение элемента, ПОСЛЕ КОТОРОГО вы хотите добавить новый элемент: ";
                    cin.clear(); getline(cin, _value);
                    while ((Current != NULL) && (Current -> firstSub -> value != _value))
                        Current = Current -> nextMain;
                    if (Current != NULL) i++;
                    else { cout << " Строка " << _value << " не найдена. Попробуйте ввести другое значение\n"; }
                }

                Temp -> nextMain = Current -> nextMain; //формирование полей нового элемента, в частности – настройка ссылочной части
                Temp -> firstSub -> next = NULL;
                Current -> nextMain = Temp; //изменение ссылочной части текущего элемента на адрес нового элемента
            }
            else { //иначе - просто добавить первым элементом
                Temp -> nextMain = NULL;
                Temp -> firstSub -> next = NULL;
                HeadMain -> nextMain = Temp;
            }
        }
        else {
            cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ\n"; choice = -1;
        }

    }
    cout << "\n Введите название элемента главного списка: "; cin.clear(); getline(cin, _value);

    Temp -> firstSub -> value = _value; num1++;

    cout << "\n Элемент успешно добавлен в базовый список! \n";
}

//Добавление нового элемента в связанный список
void pushInSub(){
    if (!isMainListEmpty()){
        string _value;
        MainList *CurrentMain = nullptr; //ввод вспомогательной ссылочной переменной
        int i = -1; // i - индикатор для поиска (пока элемент не найден, вводить новые значения)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (i == -1) {
            CurrentMain = HeadMain -> nextMain; //установка Current в адрес первого реального элемента
            cout << "\n Введите название заголовка связанного списка, в который хотите добавить новый элемент: ";
            cin.clear(); getline(cin, _value);
            while ((CurrentMain != NULL) && (CurrentMain -> firstSub -> value != _value))
                CurrentMain = CurrentMain -> nextMain;
            if (CurrentMain != NULL) i++;
            else { cout << " Строка " << _value << " не найдена. Попробуйте ввести другое значение\n"; }
        }
        SubList *Head = CurrentMain -> firstSub; //указатель на заголовок связанного списка (первый элемент)
        SubList *CurrentSub = nullptr; //ввод вспомогательной ссылочной переменной
        SubList *Temp = new SubList; //ввод вспомогательной ссылочной переменной (для нового элемента)
        int choice = -1; // выбор, куда добавлять
        while ((choice != 0) && (choice != 1)){
            cout <<"\n Куда добавить элемент?\n 0 - Перед заданным элементом\n 1 - После заданного элемента\n\n Введите номер команды: ";
            choice = failure(); //ввод номера команды c проверкой на ошибку
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice == 0) { // ДОБАВЛЕНИЕ ПЕРЕД ЗАДАННЫМ ЭЛЕМЕНТОМ
                if (!isSubListEmpty(CurrentMain)) {
                    SubList *Pred = Head; //ввод вспомогательной ссылочной переменной (предшествующей Current) и установка в заголовок (тогда как current идет с первого РЕАЛЬНОГО элемента)
                    i = -1;
                    while (i == -1){
                        CurrentSub = Head -> next; //установка Current в адрес первого реального элемента
                        cout << "\n Введите значение элемента, ПЕРЕД КОТОРЫМ вы хотите добавить новый элемент: "; cin.clear(); getline(cin, _value);
                        while (CurrentSub != NULL) {
                            if (CurrentSub -> value == _value) break;
                            CurrentSub = CurrentSub -> next;
                            Pred = Pred -> next;
                        }
                        if (CurrentSub != NULL) i++;
                        else { cout << " Строка " << _value << " не найдена. Попробуйте ввести другое значение\n"; }
                    }
                    Temp -> next = CurrentSub; //формирование полей нового элемента, в частности – настройка ссылочной части
                    Pred -> next = Temp; //изменение ссылочной части элемента-предшественника на адрес нового элемента
                }
                else {
                    cout << "\nОПЕРАЦИЮ 'ДОБАВИТЬ ПЕРЕД' НЕЛЬЗЯ ПРИМЕНИТЬ ДЛЯ ПУСТОГО СПИСКА. ВЫБЕРИТЕ ДРУГУЮ КОМАНДУ\n"; choice = -1;
                }
            }
            else if (choice == 1) { // ДОБАВЛЕНИЕ ПОСЛЕ ЗАДАННОГО ЭЛЕМЕНТА
                if (!isSubListEmpty(CurrentMain)) {
                    i = -1;
                    while (i == -1) {
                        CurrentSub = Head -> next; //установка Current в адрес первого реального элемента
                        cout << "\n Введите значение элемента, ПОСЛЕ КОТОРОГО вы хотите добавить новый элемент: "; cin.clear(); getline(cin, _value);
                        while ((CurrentSub != NULL) && (CurrentSub -> value != _value))
                            CurrentSub = CurrentSub -> next;
                        if (CurrentSub != NULL) i++;
                        else { cout << " Строка " << _value << " не найдена. Попробуйте ввести другое значение\n"; }
                    }
                    Temp -> next = CurrentSub -> next; //формирование полей нового элемента, в частности – настройка ссылочной части
                    CurrentSub -> next = Temp; //изменение ссылочной части текущего элемента на адрес нового элемента
                }
                else {
                    Temp -> next = NULL;
                    Head -> next = Temp;
                }
            }
            else {
                cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ\n"; choice = -1;
            }
        }
        cout << "\n Введите добавляемую строку: "; cin.clear(); getline(cin, _value);
        cout << "\n Элемент успешно добавлен! \n"; Temp -> value = _value;
    }
    else {
        cout << "\nЧТОБЫ ДОБАВИТЬ ЭЛЕМЕНТ В СВЯЗАННЫЙ СПИСОК, СНАЧАЛА НУЖНО СОЗДАТЬ ХОТЯ БЫ ОДИН СВЯЗАННЫЙ СПИСОК (КОМАНДА 3)\n";
    }
}

//Удаление элемента из главного списка (и всех содержащихся в нем элементов)
void popFromMain(){
    if (!isMainListEmpty()){
        string _value;
        MainList *MainCurrent = nullptr; //ввод вспомогательной ссылочной переменной
        MainList *MainPred = nullptr; //ввод вспомогательной ссылочной переменной (предшествующей Current)
        SubList *SubCurrent; //ввод вспомогательной ссылочной переменной
        int i = -1; // i - индикатор для поиска (пока элемент не найден, вводить новые значения)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (i == -1) {
            MainCurrent = HeadMain -> nextMain; //установка Current в адрес первого реального элемента
            MainPred = HeadMain; //установка в заголовок (тогда как current идет с первого РЕАЛЬНОГО элемента)
            cout << "\n Введите название заголовка связанного списка, чтобы удалить его: ";
            cin.clear(); getline(cin, _value);
            while (MainCurrent != NULL) {
                if (MainCurrent -> firstSub -> value == _value) break;
                MainCurrent = MainCurrent -> nextMain;
                MainPred = MainPred -> nextMain;
            }
            if (MainCurrent != NULL) { i++; cout << " СТРОКА " << _value << " НАЙДЕНА. ПРОИЗВОДИТСЯ УДАЛЕНИЕ... \n"; }
            else { cout << " СТРОКА " << _value << " НЕ НАЙДЕНА. ПОПРОБУЙТЕ ВВЕСТИ ДРУГОЕ ЗНАЧЕНИЕ\n"; }
        }
        //удаление элементов внутри связанного списка
        while (MainCurrent -> firstSub -> next != NULL) {
            SubCurrent = MainCurrent -> firstSub;
            MainCurrent -> firstSub = MainCurrent -> firstSub -> next;
            delete SubCurrent;
        }

        delete MainCurrent -> firstSub;
        cout << " ВСПОМОГАТЕЛЬНЫЙ СПИСОК '" << MainCurrent -> firstSub -> value <<  "' УДАЛЕН\n";

        MainPred -> nextMain = MainCurrent -> nextMain; //изменение связующей части элемента-предшественника на значение связующей части удаляемого элемента
        delete MainCurrent; //обработать удаленный элемент, например - освободить занимаемую им память
        cout << " ЭЛЕМЕНТ ГЛАВНОГО СПИСОК УДАЛЕН\n";
    }
    else {
        cout << " УДАЛЯТЬ НЕЧЕГО. СПИСОК ПУСТ.\n";
    }
}

//Удаление элемента из вспомогательного списка
void popFromSub(){
    if (!isMainListEmpty()){
        showList();
        string _value;
        MainList *CurrentMain = nullptr; //ввод вспомогательной ссылочной переменной
        int i = -1; // i - индикатор для поиска (пока элемент не найден, вводить новые значения)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (i == -1) {
            CurrentMain = HeadMain -> nextMain; //установка Current в адрес первого реального элемента
            cout << "\n Введите значение заголовка связного списка, в котором хотите удалить элемент: ";
            cin.clear(); getline(cin, _value);
            while ((CurrentMain != NULL) && (CurrentMain -> firstSub -> value != _value))
                CurrentMain = CurrentMain -> nextMain;
            if (CurrentMain != NULL) i++;
            else { cout << " Строка " << _value << " не найдена. Попробуйте ввести другое значение\n"; }
        }
        if (!isSubListEmpty(CurrentMain)) {
            SubList *Head = CurrentMain -> firstSub; //указатель на заголовок связанного списка (первый элемент)
            SubList *Current = nullptr; //ввод вспомогательной ссылочной переменной
            SubList *Pred = nullptr; //ввод вспомогательной ссылочной переменной (предшествующей Current)
            i = -1;
            while (i == -1) {
                Current = Head -> next; //установка Current в адрес первого реального элемента
                Pred = Head; //установка в заголовок (тогда как current идет с первого РЕАЛЬНОГО элемента)
                cout << "\n Введите значение элемента, который хотите удалить: "; cin.clear(); getline(cin, _value);
                while (Current != NULL) {
                    if (Current -> value == _value) break;
                    Current = Current -> next;
                    Pred = Pred -> next;
                }
                if (Current != NULL) { i++; cout << " Строка " << _value << " найдена под номером "<< i << ")\n"; }
                else { cout << " Строка " << _value << " не найдена\n"; }
            }
            Pred -> next = Current -> next; //изменение связующей части элемента-предшественника на значение связующей части удаляемого элемента
            cout << "\nЭлемент '" << Current -> value << "' удален из связанного списка '" << CurrentMain -> firstSub -> value <<  "' \n";
            delete Current; //обработать удаленный элемент, например - освободить занимаемую им память
        }
        else {
            cout << "\n УДАЛЯТЬ НЕЧЕГО. СВЯЗАННЫЙ СПИСОК ПУСТ.\n";
        }
    }
    else {
        cout << "\n УДАЛЯТЬ НЕЧЕГО. СПИСОК ПУСТ.\n";
    }
}

//Поиск элемента с заданной информационной частью
void find() {
    if (!isMainListEmpty()){ //проверить,есть ли в списке элементы
        showList();
        string _value;
        cout << "\n Введите строку, которую хотите найти: ";
        cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); getline(cin, _value);
        int j = 0; //счетчик, найдена ли строка вообще
        MainList *CurrentMain = HeadMain -> nextMain; //установка Current в адрес первого реального элемента
        while (CurrentMain != NULL) {
            std::cout << "\n Поиск среди элементов списка " << CurrentMain -> firstSub -> value << "... ";
            if (!isSubListEmpty(CurrentMain)) {
                int i = 1; //номер найденного для данного связанного списка
                SubList *SubCurrent = CurrentMain -> firstSub -> next;
                while ((SubCurrent != NULL) && (SubCurrent -> value != _value)) {
                    SubCurrent = SubCurrent -> next;
                    i++;
                }
                if (SubCurrent != NULL) { cout << " СТРОКА '" << _value << "' НАЙДЕНА\n"; j++;}
                else cout << " СТРОКА НЕ НАЙДЕНА\n";
            }
            else {
                cout << " СВЯЗАННЫЙ СПИСОК '" << CurrentMain -> firstSub -> value << "' ПУСТ\n";
            }
            CurrentMain = CurrentMain -> nextMain;
        }
        if (j==0) cout << "\n РЕЗУЛЬТАТ: СТРОКА '" << _value << "' НИГДЕ НЕ НАЙДЕНА\n";
        else cout << "\n РЕЗУЛЬТАТ: НАЙДЕНО " << j << " ЭЛЕМЕНТОВ\n";
    }
    else {
        cout << "\nИСКАТЬ НЕЧЕГО. СПИСОК ПУСТ.\n";
    }
}

//Очистка главного списка и всех вспомогательных (освобождение памяти)
inline void ClearList(){
    cout << "\nВЫПОЛНЯЕТСЯ ОЧИСТКА СПИСКА...\n";
    MainList *MainCurrent; //установка Current в адрес первого реального элемента
    SubList *SubCurrent; //ввод вспомогательной ссылочной переменной
    MainCurrent = HeadMain;
    while (HeadMain != NULL) {
        MainCurrent = HeadMain;
        while (MainCurrent -> firstSub != NULL) {
            SubCurrent = MainCurrent -> firstSub;
            MainCurrent -> firstSub = MainCurrent -> firstSub -> next;
            delete SubCurrent;
        }
        HeadMain = MainCurrent -> nextMain;
        delete MainCurrent;
    }
    cout << "\nСПИСОК ОЧИЩЕН...\n";
}

void menu() {
    int number;
    while (true) {
        cout << "___________________________________________________________\n";
        cout << "\nВыберите команду из списка:\n";
        cout << "1. Вывод текущего состояния списка на экран\n";
        cout << "2. Проверка пустоты главного списка\n";
        cout << "3. Добавить элемент в список с пустым связанным списком\n";
        cout << "4. Добавить элемент в связанный список\n";
        cout << "5. Удалить элемент из базового списка\n";
        cout << "6. Удалить элемент из связанного списка\n";
        cout << "7. Поиск элемента с заданной информационной частью\n";
        cout << "8. Очистить список списков\n";
        cout << "0. Завершить работу программы\n";
        cout <<"Номер команды: ";
        number = failure();
        if (number == 1) showList(); //1. Вывод текущего состояния списка на экран
        else if (number == 2){ //2. Проверка пустоты главного списка
            if (isMainListEmpty() == 1) cout << "\nПРОВЕРКА ГЛАВНОГО СПИСКА НА ПУСТОТУ... ГЛАВНЫЙ СПИСОК ПУСТОЙ\n";
            else cout << "\nПРОВЕРКА ГЛАВНОГО СПИСКА НА ПУСТОТУ... ГЛАВНЫЙ СПИСОК НЕ ПУСТОЙ\n";
        }
        else if (number == 3) pushInMain(); //3. Добавить элемент в список с пустым связанным списком
        else if (number == 4) pushInSub(); //4. Добавить элемент в связанный список
        else if (number == 5) popFromMain(); //5. Удалить элемент из базового списка
        else if (number == 6) popFromSub(); //6. Удалить элемент из связанного списка
        else if (number == 7) find(); //7. Поиск элемента с заданной информационной частью
        else if (number == 8) { //8. Очистить список
            ClearList(); //очистка памяти
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