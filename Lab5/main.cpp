//Лабораторная работа №5 (Раздел 1, Тема 3, Номер 3) - ЛИНЕЙНЫЙ СПИСОК НА БАЗЕ МАССИВА С УКАЗАТЕЛЯМИ - ИНДЕКСАМИ

#include <iostream>
#include <cstdlib>

using namespace std;

const int arr_size = 11; //размер массива (c учетом того, что 0-й элемент - это заголовок)
int num; //кол-во элементов в списке

int failure();
inline void initList();
void sort();
bool isEmpty();
bool isFull();
void showList();
void push();
void pop();
void find();
int find(string _value, int act);
inline void Clear();
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
//    cin.ignore(32767, '\n');
    return a;
}

// описание Структуры "Линейный список c указателями-индексами"
struct LinkedList {
    string value; //строка-значение
    int next; //номер ячейки массива, в которой находится следующий за ним элемент
} list[arr_size];

//инициализация, создание пустого списка
inline void initList() {
    list[0].value = "HEAD"; //заголовок
    list[0].next = 0;
    for (int i = 1; i < arr_size; i++) list[i].next = -1; //все ячейки после заголовка отмечаются как свободные
    num = 0;
}

// Проверка пустоты списка
bool isEmpty(){
    if (list[0].next == 0) return 1; //если указатель next у заголовка указывает сам на себя
    else return 0;
}
// Проверка полноты списка
bool isFull(){
    if (num == arr_size-1) return 1;
    else return 0;
}

//Проход по списку и вывод состояния
void showList() {
    cout << "\nСостояние списка: ";
    if (!isEmpty()) { //проверить возможности удаления (в списке есть элементы?)
        cout << "ЗАПОЛНЕНО " << num << " ИЗ " << (arr_size-1) << " ЯЧЕЕК СПИСКА:\n";
        int i=1, current = list[0].next;
        while (current != 0) {
            cout << i << ") " << list[current].value << " (ячейка памяти: " << current << ")\n";
            current = list[current].next;
            i++;
        }
    }
    else {
        cout << "СПИСОК ПУСТОЙ\n";
    }
}

//Добавление элемента в список
void push(){
    if (!isFull()) {
        string _value;
        if (!isEmpty()){ //если в списке есть элементы помимо заголовка, то спросить, где вставить новый элемент
            int choice = -1, i = -1, j = 0, s = -1; // i - индекс найденного элемента; j - свободной ячейки (добавляемой ячейки); s - предшественник искомого i
            while ((choice != 0) && (choice != 1)){
                cout <<"\n Куда добавить элемент?\n 0 - Перед заданным элементом\n 1 - После заданного элемента\n\n Введите номер команды: ";
                choice = failure(); //ввод номера команды c проверкой на ошибку
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (choice == 0) { // ДОБАВЛЕНИЕ ПЕРЕД ЗАДАННЫМ ЭЛЕМЕНТОМ
                    i = -1; s = -1;
                    while ((i == -1) || (s == -1)){
                        cout << "\n Введите значение элемента, ПЕРЕД КОТОРЫМ вы хотите добавить новый элемент: "; cin.clear(); getline(cin, _value);
                        i = find(_value, 1); // i-индекс ячейки найденного элемента
                        s = find(_value, 0); // поиск предшествующего элемента
                        if ((i == -1) && (s == -1)) cout << "\n Строка " << _value << " не найдена. Повторите ввод\n";
                    }
                    j = list[0].next;
                    for (j=1; j<arr_size; j++) if(list[j].next == -1) break; //поиск свободной ячейки
                    list[j].next = i; // формирование связующей части нового элемента, т.е. занесение туда индекса i : StatList [ j ].next := i;
                    list[s].next = j; // изменение связующей части элемента-предшественника с индекса i на индекс j: StatList [ s ].next := j;
                }
                else if (choice == 1) { // ДОБАВЛЕНИЕ ПОСЛЕ ЗАДАННОГО ЭЛЕМЕНТА
                    i = -1;
                    while (i == -1) {
                        cout << "\n Введите значение элемента, ПОСЛЕ КОТОРОГО вы хотите добавить новый элемент: "; cin.clear(); getline(cin, _value);
                        i = find(_value, 1); // i-индекс ячейки найденного элемента
                        if (i == -1) cout << "\n Строка " << _value << " не найдена. Повторите ввод\n";
                    }
                    for (j=1; j<arr_size; j++) if(list[j].next == -1) break; //поиск свободной ячейки
                    list[j].next = list[i].next; //формирование связующей части нового элемента, т.е. занесение туда номера ячейки из связующей части элемента i
                    list[i].next = j; //изменение связующей части элемента i на номер j
                }
                else {
                    choice = -1;
                    cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ\n";
                }
            }
            cout << "\n Введите добавляемую строку: "; cin.clear(); getline(cin, _value);
            list[j].value = _value;
            cout << "\n Элемент успешно добавлен! \n";
        }
        else { //иначе - просто добавить первым элементом
            cout << "\n Введите добавляемую строку: ";
            cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); getline(cin, _value);
            list[1].value = _value;
            list[1].next = 0;
            list[0].next = 1;
            cout << "\n Элемент успешно добавлен! \n";
        }
        num++;
    }
    else {
        cout << "\n ДОБАВЛЕНИЕ НЕВОЗМОЖНО. СПИСОК ПЕРЕПОЛНЕН\n";
    }
}

//Удаление элемента из списка
void pop(){
    if (!isEmpty()){
        showList();
        string _value;
        int i=-1, s=-1; // i-индекс найденного элемента; j-индекс свободной ячейки, он же - адрес удаляемой ячейки; s-предшественник искомого i
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while ((i == -1) || (s == -1)){
            cout << "\n Введите значение элемента, который хотите удалить: "; cin.clear(); getline(cin, _value);
            i = find(_value, 1); // i-индекс ячейки найденного элемента
            s = find(_value, 0); // поиска предшествующего элемента
            if ((i == -1) || (s == -1)) cout << "\n Строка " << _value << " не найдена. Повторите ввод\n";
        }
        list[s].next = list[i].next; //изменение связующей части элемента-предшественника с индекса i на индекс-значение связующей части удаляемого элемента i
        list[i].next = -1; //после "обхода" ячейки она освобождается с включением ее в список свободных ячеек
        num--;
        cout << "\nЭлемент '" << list[i].value << "' удален из списка. Теперь в списке " << num <<" элементов\n";
    }
    else {
        cout << "\nУДАЛЯТЬ НЕЧЕГО. СПИСОК ПУСТ.\n";
    }
}

//Поиск элемента с заданной информационной частью
void find() {
    if (!isEmpty()){
        showList();
        string _value;
        cout << "\n Введите строку, которую хотите найти: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, _value);
        int i=1, current = list[0].next;
        while ((current != 0) && (list[current].value != _value)){
            current = list[current].next;
            i++;
        }
        if (current != 0) cout << " Строка " << _value << " найдена под номером "<< i << " (в ячейке памяти № " << (current++) << ")\n";
        else cout << " Строка " << _value << " не найдена\n";
    }
    else {
        cout << "\nИСКАТЬ НЕЧЕГО. СПИСОК ПУСТ.\n";
    }
}

//поиск для добавления (ничего не выводит. принимает строку и параметр act
// (искать сам элемент или предшествующий ему), возвращает индекс.)
int find(string _value, int mode) {
    int current = list[0].next;
    if (mode == 1)  //искать сам элемент
        while ((current != 0) && (list[current].value != _value)){
            current = list[current].next;
        }
    else if (mode == 0)//искать предшествующий элемент
    {
        int pred = 0; //этот счетчик будет идти, НАЧИНАЯ С САМОГО ЗАГОЛОВКА (тогда как current начинается с list[0].next)
        while (current != 0) {
            if (list[current].value == _value) break;
            current = list[current].next;
            pred = list[pred].next;
        }
        return pred;
    }
    if (current != 0) return current;
    else return -1;
}

//Очистка списка перед завершением работы программы
// (по факту - повторная инициализация c изменением всех полей next на -1)
inline void Clear(){
    cout << "\nВЫПОЛНЯЕТСЯ ОЧИСТКА СПИСКА...\n";
    initList();
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
        cout << "3. Проверка полноты списка\n";
        cout << "4. Добавить элемент в список\n";
        cout << "5. Удалить элемент из списка\n";
        cout << "6. Поиск элемента с заданной информационной частью\n";
        cout << "7. Очистить список\n";
        cout << "0. Завершить работу программы\n";
        cout <<"Номер команды: ";
        number = failure();
        if (number == 1) showList(); //1. Вывод текущего состояния списка на экран
        else if (number == 2){ //2. Проверка пустоты списка
            if (isEmpty() == 1) cout << "\nПРОВЕРКА СПИСКА НА ПУСТОТУ... СПИСОК ПУСТОЙ\n";
            else cout << "\nПРОВЕРКА СПИСКА НА ПУСТОТУ... СПИСОК НЕ ПУСТОЙ\n";
        }
        else if (number == 3){ //3. Проверка полноты списка
            if (isFull() == 1) cout << "\nПРОВЕРКА СПИСКА НА ПОЛНОТУ... СПИСОК ЗАПОЛНЕН\n";
            else cout << "\nПРОВЕРКА СПИСКА НА ПОЛНОТУ... СПИСОК НЕ ЗАПОЛНЕН\n";
        }
        else if (number == 4) push(); //4. Добавить элемент в список
        else if (number == 5) pop(); //5. Удалить элемент из списка
        else if (number == 6) find(); //6. Поиск элемента с заданной информационной частью
        else if (number == 7) Clear(); //7. Очистить список
        else if (number == 0) {//0. Завершить работу
            Clear(); //очистка списка
            cout << "\nВЫХОД ИЗ ПРОГРАММЫ...\n\n";
            break;
        }
        else cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ\n";
    }
}

int main() {
    initList(); //инициализация пустого списка
    menu(); //организация диалогового цикла с пользователем
    return 0;
}