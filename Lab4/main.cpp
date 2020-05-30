//Лабораторная работа №4 (Раздел 1, Тема 3, Номер 2) - МОДЕЛИРОВАНИЕ УПОРЯДОЧЕННОГО ЛИНЕЙНОГО СПИСКА С ПОМОЩЬЮ МАССИВА.

#include <iostream>
#include <cstdlib>

using namespace std;

const int arr_size = 10; //размер массива
int num; //кол-во элементов в списке

int failure();
inline void initList();
int sort();
bool isEmpty();
bool isFull();
void showList();
void push();
void pop();
void find();
inline void Clear();
void menu();

//метод обработки ошибок ввода команды (проверяет на то, чтобы были введены только цифры, без букв).
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

// описание Структуры "Линейный список"
struct SimpleList {
    string value; //строка-значение
} list[arr_size];

//инициализация, создание пустого списка
inline void initList() {
    for (int i = 0; i < arr_size; i++) list[i].value="";
    num = 0;
}

//сортировка элементов списка (по возрастанию)
int sort(){
    if (!isEmpty()){
        if (num == 1) return 2;
        else {
            string _value;
            for (int i = 0; i < num; i++) {
                for (int j = num - 1; j > i; j--) {
                    if (list[j - 1].value > list[j].value) {
                        _value = list[j-1].value;
                        list[j-1].value = list[j].value;
                        list[j].value = _value;
                    }
                }
            }
            return 1;
        }
    }
    else
        return 0;
}

// Проверка пустоты списка
bool isEmpty(){
    if (num == 0) return 1;
    else return 0;
}

// Проверка полноты списка
bool isFull(){
    if (num == arr_size) return 1;
    else return 0;
}

//Проход по списку и вывод состояния
void showList() {
    if (!isEmpty()) { //проверить возможности удаления (в списке есть элементы?)
        cout << "ЗАПОЛНЕНО " << num << " ИЗ " << arr_size << " ЯЧЕЕК СПИСКА:\n";
        for (int i = 0; i < num; i++)
            cout << i+1 << ") " << list[i].value << "\n";
    }
    else
        cout << "СПИСОК ПУСТОЙ\n";
}

//Добавление элемента в список
void push(){
    if (!isFull()) {
        bool a = 1;
        string _value;
        if (isEmpty()){
            cout << "\n СПИСОК ПУСТ. ЭЛЕМЕНТ БУДЕТ ДОБАВЛЕН ПЕРВЫМ";
            cout << "\n ВВЕДИТЕ СТРОКУ: ";
            cin.clear(); cin.ignore(32767, '\n'); getline(cin, _value);
            list[0].value = _value; //добавение первым элементом
            num++;
            return;
        }
        cout << " ВВЕДИТЕ СТРОКУ: ";
        cin.clear(); cin.ignore(32767, '\n'); getline(cin, _value);
        for (int i = 0; i < num; i++) {
            if (_value < list[i].value)
            {
                if (i == num) list[num].value = _value; //добавение в конец
                if (0 <= i < num){
                    for (int k = num; k>i; k--) //копирование(сдвиг) ячеек с конца списка
                        list[k].value=list[k-1].value;
                    list[i].value = _value; //записываем новый элемент в освободившуюся ячейку
                }
                a = 0;
                cout << " ЭЛЕМЕНТ ДОБАВЛЕН В ЯЧЕЙКУ ПОД НОМЕРОМ " << i+1 << "\n";
                break;
            }
        }
        if (a) {
            list[num].value = _value; //добавение в конец, если все элементы меньше заданного value (или в начало пустого списка)
            cout << "Добавлено в конец списка\n";
        }
        num++;
    }
    else
        cout << "ДОБАВЛЕНИЕ НЕВОЗМОЖНО. СПИСОК ПЕРЕПОЛНЕН\n";
}

//Удаление элемента из списка
void pop(){
    if (!isEmpty()){
        showList();
        string _value;
        cout << "\n ВВЕДИТЕ ИНФОРМАЦИОННУЮ ЧАСТЬ ЭЛЕМЕНТА, КОТОРЫЙ НУЖНО УДАЛИТЬ: ";
        cin.clear(); cin.ignore(32767, '\n'); getline(cin, _value);
        int k = -1;
        while (k == -1) {
            for (int i = 0; i < num; i++) {
                if (list[i].value == _value) { k++;
                    for (int k = i; k<num; k++) //сдвиг ячеек влево после удаления
                        list[k].value=list[k+1].value;
                    num--;
                    cout << "\nЭлемент '" << _value << "' удален из списка. Теперь в списке " << num <<" элементов\n";
                }
            }
            if (k == -1) cout << " В списке нет элемента с таким номером\n";
        }
    }
    else
        cout << "\nУДАЛЯТЬ НЕЧЕГО. СПИСОК ПУСТ.\n";
}

//Поиск элемента с заданной информационной частью
void find() {
    if (!isEmpty()){
        int count = 0;
        showList();
        string _value;
        cout << "Введите строку, которую хотите найти: ";
        cin.clear(); cin.ignore(32767, '\n'); getline(cin, _value);
        for (int i=0; i<num; i++)
            if (list[i].value == _value) count=i+1;
        if (count != 0) cout << "Строка " << _value << " найдена под номером " << count << "\n";
        else cout << "Строка " << _value << " не найдена\n";
    }
    else
        cout << "\nИСКАТЬ НЕЧЕГО. СПИСОК ПУСТ.\n";
}

//Очистка списка перед завершением работы программы
inline void Clear(){
    cout << "\nВЫПОЛНЯЕТСЯ ОЧИСТКА СПИСКА...\n";
    for (int i = 0; i < arr_size; i++) list[i].value="";
    num = 0;
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
        cout << "7. Отсортировать список\n";
        cout << "8. Очистить список\n";
        cout << "0. Завершить работу программы\n";
        cout <<"Номер команды: ";
        number = failure();
        if (number == 1) { //1. Вывод текущего состояния списка на экран
            cout << "\nСостояние списка: ";
            showList();
        }
        else if (number == 2){ //2. Проверка пустоты списка
            if (isEmpty() == 1) cout << "\nПРОВЕРКА СПИСКА НА ПУСТОТУ... СПИСОК ПУСТОЙ\n";
            else cout << "\nПРОВЕРКА СПИСКА НА ПУСТОТУ... СПИСОК НЕ ПУСТОЙ\n";
        }
        else if (number == 3){ //3. Проверка полноты списка
            if (isFull() == 1) cout << "\nПРОВЕРКА СПИСКА НА ПОЛНОТУ... СПИСОК ЗАПОЛНЕН\n";
            else cout << "\nПРОВЕРКА СПИСКА НА ПОЛНОТУ... СПИСОК НЕ ЗАПОЛНЕН\n";
        }
        else if (number == 4)  //4. Добавить элемент в список
            push();
        else if (number == 5)  //5. Удалить элемент из списка
            pop();
        else if (number == 6)  //6. Поиск элемента с заданной информационной частью
            find();
        else if (number == 7) { //7. Отсортировать список
            int act = -1;
            cout << "\n ВНИМАНИЕ! ПРИ СОРТРОВКЕ СПИСКА ЕГО ВИД БЕЗВОЗВРАТНО ИЗМЕНИТСЯ.\n ВЫ УВЕРЕНЫ? 1 - ДА, 0 - НЕТ, ВЕРНУТЬСЯ В МЕНЮ\n";
            while ((act != 0) && (act != 1)){
                cout << " ВАШ ВЫБОР: ";
                act = failure();
                if (act == 1) {
                    //                    sort(); //перед добавлением нужно осортировать список
                    if (sort() == 1) {
                        cout << " СОРТИРОВКА УСПЕШНО ПРОИЗВЕДЕНА\n";
                        break;
                    }
                    if (sort() == 2) {
                        cout << "\n В СПИСКЕ ТОЛЬКО ОДИН ЭЛЕМЕНТ. СОРТИРОВАТЬ НЕЧЕГО\n ЭЛЕМЕНТ БУДЕТ ДОБАВЛЕН В КОНЕЦ\n";
                        break;
                    }
                    if (sort() == 0) {
                        cout << "\n СОРТИРОВАТЬ НЕЧЕГО. СПИСОК ПУСТ.\n";
                        break;
                    }
                }
                else if (act == 0) return;
                else {
                    act = -1;
                    cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ\n";
                }
            }

        }
        else if (number == 8) //8. Очистить список
            Clear(); //очистка списка
        else if (number == 0) {//0. Завершить работу
            Clear(); //очистка списка
            cout << "\nВЫХОД ИЗ ПРОГРАММЫ...\n\n";
            break;
        }
        else
            cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД КОМАНДЫ\n";
    }
}

int main() {
    initList(); //инициализация пустого списка
    menu(); //организация диалогового цикла с пользователем
    return 0;
}