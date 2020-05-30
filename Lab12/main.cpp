//Лабораторная работа №12 (Раздел 1, Тема 6, Номер 1) - ПОСТРОЕНИЕ И ОБРАБОТКА ДВОИЧНЫХ ДЕРЕВЬЕВ ПОИСКА

#include <iostream>
#include <cstdlib>

using namespace std;

bool founded = false; //признак успешности поиска, глобальная переменная

//метод обработки ошибок ввода (проверяет, чтобы были введены ТОЛЬКО цифры, без букв)
// возвращает ПРАВИЛЬНО ВВЕДЕННОЕ ЧИСЛО
int failure() {
    int a;
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "\n ОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД: ";
    }
    return a;
}

//ОПИСАНИЕ СТРУКТУРЫ ДЕРЕВА TreePoint
struct Tp {
    int value; //строка-значение
    int counter; //счетчик числа появлений данного ключа
    Tp *Left; //ссылочная переменная-указатель на левый элемент
    Tp *Right; //ссылочная переменная-указатель на правый элемент
} *pRoot=NULL, *pParent=NULL; // pRoot - указатель на корень дерева,
                                            // pParent - указатель на родительскую вершину, глобальные переменные

//ПОСТРОЧНЫЙ ВЫВОД В СИММЕТРИЧНОМ НАПРАВЛЕНИИ
void Symmetric (Tp *pCurrent) {
    if (pCurrent != NULL) {
        Symmetric (pCurrent -> Left); //вывод  всех левых поддеревьев
        cout << pCurrent->value << "("<<  pCurrent -> counter  <<"); " ;
        Symmetric (pCurrent -> Right); //вывод  всех правых поддеревьев
    }
}

//ПОСТРОЧНЫЙ ВЫВОД В ОБРАТНО-СИММЕТРИЧНОМ НАПРАВЛЕНИИ
void BackSymmetric (Tp *pCurrent, int level) {
    if (pCurrent != NULL) {
        BackSymmetric (pCurrent -> Right, level + 1); //обработка  всех правых поддеревьев
        string str; //обработка корневой вершины pCurrent
        for (int i = 0; i < level; i++)
            str+= "     ";
        cout << " " << str << pCurrent->value << "\n" ;
        BackSymmetric (pCurrent -> Left, level + 1); //обработка  всех левых поддеревьев
    }
}

//ПОИСК ВЕРШИНЫ С ЗАДАННЫМ ЗНАЧЕНИЕМ ИНФОРМАЦИОННОЙ ЧАСТИ
Tp *Find(int _value, int mode) {
    Tp *pCurrent = pRoot; //{начинаем поиск с корня дерева}
    pParent = NULL;
    bool Stop = false;
    while ((pCurrent != NULL) && (!Stop)) {
        if (_value < pCurrent->value) {
            pParent = pCurrent;
            pCurrent = pCurrent -> Left;
        }
        else if (_value > pCurrent -> value) {
            pParent = pCurrent;
            pCurrent = pCurrent -> Right;
        }
        else
            Stop = true;
    }
    if (mode == 0)
        return pCurrent;
    else
        return pParent;
}

//ПОИСК ВЕРШИНЫ С ЗАДАННЫМ ЗНАЧЕНИЕМ ИНФОРМАЦИОННОЙ ЧАСТИ (ДИАЛОГОВАЯ ФУНКЦИЯ)
void FindDialog() {
    int _value;
    cout <<"\n ВВЕДИТЕ ЗНАЧЕНИЕ КЛЮЧА, КОТОРЫЙ ХОТИТЕ НАЙТИ: "; _value = failure();
    Tp *pTemp = Find(_value, 0);
    if (pTemp != NULL)
        cout <<" ЭЛЕМЕНТ СО ЗНАЧЕНИЕМ КЛЮЧА '" << _value << "' НАЙДЕН. ЧИСЛО ПОЯВЛЕНИЙ: \n" << pTemp -> counter << "\n";
    else
        cout <<" ЭЛЕМЕНТ СО ЗНАЧЕНИЕМ КЛЮЧА '" << _value << "' НЕ НАЙДЕН\n";
}

//ПОСТРОЧНЫЙ ВЫВОД ДЕРЕВА
void show(int n){
    if (pRoot != NULL) {
        if (n==1)  {
            cout <<"\n ПОСТРОЧНЫЙ ВЫВОД ВСЕХ ВЕРШИН В ОДНУ СТРОКУ В СООТВЕТСТВИИ С ВОЗРАСТАНИЕМ ИХ КЛЮЧЕЙ (В СТРОКУ):\n\n";
            Symmetric(pRoot);
            cout << "\n";
        }
        if (n==2) {
            cout <<"\n ПОСТРОЧНЫЙ ВЫВОД В ОБРАТНО-СИММЕТРИЧНОМ ПОРЯДКЕ:\n\n";
            BackSymmetric(pRoot, 0);
            cout << "\n";
        }
    }
    else {
        cout <<" ДЕРЕВО ПУСТОЕ\n\n";
    }
}

//ДОБАВЛЕНИЕ ВЕРШИНЫ (РЕКУРСИВНЫЙ ВАРИАНТ)
Tp *AddRecursive(Tp *pCurrent, int _value) {
    if (pCurrent == NULL) //МЕСТО НАЙДЕНО, СОЗДАТЬ НОВУЮ ВЕРШИНУ
    {
        pCurrent = new Tp; //ПАРАМЕТР PCURRENT ОПРЕДЕЛЯЕТ АДРЕС НОВОЙ ВЕРШИНЫ
        pCurrent -> value = _value;
        pCurrent -> Left = pCurrent -> Right = NULL;
        pCurrent -> counter = 1;
    }
    else { //ПРОДОЛЖАЕМ ПОИСК В ЛЕВОМ ИЛИ ПРАВОМ ПОДДЕРЕВЕ
        if (_value < pCurrent -> value)
            pCurrent -> Left = AddRecursive(pCurrent -> Left, _value);
        else if (_value > pCurrent -> value)
            pCurrent -> Right = AddRecursive(pCurrent -> Right, _value);
        else
            pCurrent -> counter++; //КЛЮЧИ СОВПАЛИ, УВЕЛИЧИВАЕМ СЧЕТЧИК ПОЯВЛЕНИЙ
    }
    return pCurrent; //ВОЗВРАЩАЕМ АДРЕС СОЗДАННОГО КОРНЯ
}

//ДОБАВЛЕНИЕ ВЕРШИНЫ (НЕРЕКУРСИВНЫЙ ВАРИАНТ)
void AddNonRecursive(int _value) {
    if (pRoot == NULL) {
        pRoot = new Tp;
        pRoot -> Left = pRoot -> Right = NULL;
        pRoot -> value = _value;
        pRoot -> counter = 1;
    }
    else {
        Tp *pParent = NULL, *pCurrent = pRoot; //НАЧИНАЕМ ПОИСК С КОРНЯ ДЕРЕВА
        while (pCurrent != NULL ) {
            pParent = pCurrent; // ЗАПОМИНАЕМ АДРЕС РОДИТЕЛЬСКОЙ ВЕРШИНЫ
            if ( _value < pCurrent -> value)
                pCurrent = pCurrent -> Left;
            else if ( _value > pCurrent -> value)
                pCurrent = pCurrent -> Right;
            else {
                pCurrent = NULL; //ВЕРШИНА НАЙДЕНА, ДОБАВЛЯТЬ НЕ НАДО, ЗАКОНЧИТЬ ЦИКЛ
                pCurrent -> counter++;
            }
        }
        if ( _value < pParent -> value) {
            pCurrent = new Tp; //ДОБАВЛЯЕМ НОВУЮ ВЕРШИНУ СЛЕВА ОТ РОДИТЕЛЯ
            pCurrent -> Left = pCurrent -> Right = NULL;
            pCurrent -> counter = 1;
            pCurrent -> value = _value;
            pParent -> Left = pCurrent;
        }
        else if ( _value > pParent -> value) {
            pCurrent = new Tp; //ДОБАВЛЯЕМ НОВУЮ ВЕРШИНУ СПРАВА ОТ РОДИТЕЛЯ
            pCurrent -> Left = pCurrent -> Right = NULL;
            pCurrent -> counter = 1;
            pCurrent -> value = _value;
            pParent -> Right = pCurrent;
        }
    }
}

//ДОБАВЛЕНИЕ ВЕРШИНЫ (ДИАЛОГОВАЯ ФУНКЦИЯ)
void AddNode() {
    int _value, n;
    cout <<"\n ВВЕДИТЕ ЗНАЧЕНИЕ КЛЮЧА У НОВОЙ ВЕРШИНЫ: ";
    _value = failure();
    cout <<"\n КАКОЙ СПОСОБ ДОБАВЛЕНИЯ ИСПОЛЬЗОВАТЬ?\n 1 - РЕКУРСИВНЫЙ СПОСОБ\n 2 - НЕРЕКУРСИВНЫЙ СПОСОБ\n ВАШ ВЫБОР: ";
    n = failure();
    while ((n != 1) && (n != 2)) {
        cout <<" ТАКОЙ КОМАНДЫ НЕ СУЩЕСТВУЕТ. ПОВТОРИТЕ ВВОД: "; n = failure();}
    if (n == 1) {
        cout <<" ВЫБРАН РЕКУРСИВНЫЙ СПОСОБ ДОБАВЛЕНИЯ... \n";
        pRoot = AddRecursive(pRoot, _value);
    }
    if (n == 2) {
        cout <<" ВЫБРАН НЕРЕКУРСИВНЫЙ СПОСОБ ДОБАВЛЕНИЯ... \n";
        AddNonRecursive(_value);
    }
    cout <<" ВЕРШИНА С КЛЮЧОМ '"<< _value <<"' ДОБАВЛЕНА... \n";
}

//CОЗДАНИЕ ДЕРЕВА С ЗАДАННЫМ ЧИСЛОМ ВЕРШИН СО СЛУЧАЙНЫМИ КЛЮЧАМИ
void TreeCreator() {
    srand(static_cast<unsigned int>(time(0))); //ИНИЦИАЛИЗАЦИЯ ГЕНЕРАТОРА ПСЕВДОСЛУЧАЙНЫХ ЧИСЕЛ RAND
    int num = -1;
    while (num <= 0) {
        cout <<" СКОЛЬКО ВЕРШИН БУДЕТ В ДЕРЕВЕ?\n КОЛ-ВО ВЕРШИН: ";
        num = failure();
        if (num<=0) cout <<" НЕВОЗМОжНО СОЗДАТЬ ДЕРЕВО С НЕПОЛОЖИТЕЛЬНЫМ ЧИСЛОМ " << num << ". ПОВТОРИТЕ ВВОД\n";
        else {
            for (int i=0; i<num; i++)
                pRoot = AddRecursive(pRoot, rand() % 100); //ВЫЗЫВАЕЕМ ФУНКЦИЮ ДОБАВЛЕНИЯ, НАЧИНАЯ С ПУСТОГО КОРНЯ, ЗНАЧЕНИЯ - РАНДОМНЫЕ
            cout <<" ДВОИЧНОЕ ДЕРЕВО ПОИСКА С ЧИСЛОМ ВЕРШИН '" << num << "' СОЗДАНО\n";
        }
    }
}

//ОЧИСТКА ПАМЯТИ (УДАЛЕНИЕ ВЕРШИН ДЕРЕВА)
void delTp(Tp *pCurrent) {
    if (pCurrent != NULL) {
        delTp(pCurrent -> Left); // СНАЧАЛА УДАЛЯТЬ ВСЕ ЭЛЕМЕНТЫ С ЛЕВОГО КОНЦА
        delTp(pCurrent -> Right); // ПОТОМ УДАЛЯТЬ ВСЕ ЭЛЕМЕНТЫ С ПРАВОГО КОНЦА
        delete pCurrent; // В КОНЦЕ УДАЛИТЬ САМ ЭЛЕМЕНТ-КОРЕНЬ
        cout << " ПОДДЕРЕВО СО ЗНАЧЕНИЕМ КОРНЕВОЙ ВЕРШИНЫ '" << pCurrent -> value << "' УДАЛЕНО\n";
    }
};

//функция замены при удалении (заменитель вершины)
Tp *Changer(Tp *p) {
    if (p -> Right != NULL)
        p = Changer(p->Right);
    return p;
};
//функция удаления
Tp *DeleteNode(Tp *pCurrent, int _value){
    if (pCurrent == NULL)
        cout <<" УДАЛЯЕМАЯ ВЕРШИНА НЕ НАЙДЕНА\n"; // УДАЛЯЕМОЙ ВЕРШИНЫ НЕТ, НИЧЕГО НЕ ДЕЛАЕМ
    else if (_value < pCurrent -> value) //ИЩЕМ СЛЕВА
        pCurrent -> Left = DeleteNode(pCurrent -> Left, _value);
    else if (_value > pCurrent -> value) //ИЩЕМ СПРАВА
        pCurrent -> Right = DeleteNode(pCurrent -> Right, _value);
    else { //УДАЛЯЕМАЯ ВЕРШИНА НАЙДЕНА
        if (pCurrent -> counter > 1) //ЕСЛИ "КОЛИЧЕСТВО" ТАКИХ ВЕРШИН БОЛЬШЕ 1, ТО ПРОСТО УМЕНЬШАЕМ СЧЕТЧИК
            pCurrent -> counter--;
        else { //ЕСЛИ ТАКАЯ ВЕРШИНА ТОЛЬКО ОДНА
            Tp *pTemp = pCurrent;
            if (pTemp -> Right == NULL) //ПРАВЫЙ ПОТОМОК ПУСТОЙ
                pCurrent = pTemp -> Left;
            else if (pTemp -> Left == NULL) //ЛЕВЫЙ ПОТОМОК ПУСТОЙ
                pCurrent = pTemp -> Right;
            else if ((pTemp -> Right == NULL) && (pTemp -> Left == NULL)) //ВЕРШИНА НЕ ИМЕЕТ ПОТОМКОВ
                pCurrent = NULL; //ЧТОБЫ ВЕРНУТЬ NULL ПОСЛЕ УДАЛЕНИЯ
            else {//ДВА ПОТОМКА, ИЩЕМ ЗАМЕНИТЕЛЬ
                Tp *p = Changer(pCurrent -> Left); //ИЩЕМ ЗАМЕНИТЕЛЬ В ЛЕВОМ ПОДДЕРЕВЕ
                pParent = Find(p -> value, 1); //ИЩЕМ АДРЕС РОДИТЕЛЯ, ЧТОБЫ ПОСЛЕ СДЕЛАТЬ ЗАМЕНУ И НЕ ПОТЕРЯТЬ ЛЕВУЮ ВЕТКУ
                cout << " ЗНАЧЕНИЕ ЗАМЕНЯЕМОЙ ВЕРШИНЫ: "<< p->value << ", А РОДИТЕЛЯ: " << pParent->value;
//                pParent -> Right = p -> Left;
                pTemp -> value = p -> value; //ЗАМЕНЯЕМ ИНФ. ЧАСТЬ УДАЛЯЕМОЙ ВЕРШИНЫ
                pTemp = p; //pTEMP ТЕПЕРЬ ОПРЕДЕЛЯЕТ ВЕРШИНУ-ЗАМЕНИТЕЛЬ
//                p = p -> Left; //ВЫХОДНОЙ ПАРАМЕТР АДРЕСУЕТ ЛЕВОГО ПОТОМКА ЗАМЕНИТЕЛЯ
                if (pParent != pCurrent)
                    pParent -> Right = p -> Left;
                else
                    pParent -> Left = p -> Left;
            }
            delete pTemp;
//            cout << "\n Вершина " << pTemp -> value <<" Удалена";
        }
    }
    return pCurrent;
}
//Диалоговая функция удаления
void DelNode(){
    show(2);
    int _value;
    cout <<"\n ВВЕДИТЕ ЗНАЧЕНИЕ КЛЮЧА ВЕРШИНЫ, КОТОРУЮ ХОТИТЕ УДАЛИТЬ: "; _value = failure();
    pRoot = DeleteNode(pRoot, _value);
    cout <<"\n ВЕРШИНА С КЛЮЧОМ '"<< _value <<"' УДАЛЕНА...\n ТЕПЕРЬ ДЕРЕВО ПОИСКА ИМЕЕТ ВИД: \n";
    show(2);
}

int main() {
    srand(static_cast<unsigned int>(time(0))); //инициализация генератора псевдослучайных чисел rand
    pRoot = NULL; // создать пустое дерево
    int n = -1;
    while (true) {
        n = -1;
        cout << " ___________________________________________________________\n\n"
             <<" ВЫБЕРИТЕ ДЕЙСТВИЕ ИЗ СПИСКА\n"
             <<" 1 - CОЗДАНИЕ ДЕРЕВА С ЗАДАННЫМ ЧИСЛОМ ВЕРШИН СО СЛУЧАЙНЫМИ КЛЮЧАМИ\n"
             <<" 2 - ДОБАВЛЕНИЕ В ДЕРЕВО ОДНОЙ ВЕРШИНЫ С ЗАДАННЫМ ПОЛЬЗОВАТЕЛЕМ ЗНАЧЕНИЕМ КЛЮЧА\n"
             <<" 3 - ПОИСК В ДЕРЕВЕ ВЕРШИНЫ С ЗАДАННЫМ КЛЮЧОМ\n"
             <<" 4 - ВЫВОД ДЕРЕВА В НАГЛЯДНОМ ВИДЕ С ПОМОЩЬЮ ОБРАТНО-СИММЕТРИЧНОГО ОБХОДА\n"
             <<" 5 - ВЫВОД ВСЕХ ВЕРШИН В ПОРЯДКЕ ВОЗРАСТАНИЯ ИХ КЛЮЧЕЙ\n"
             <<" 6 - УДАЛЕНИЕ ВЕРШИНЫ С ЗАДАННЫМ ЗНАЧЕНИЕМ КЛЮЧА\n"
             <<" 0 - ВЫХОД ИЗ ПРОГРАММЫ\n"
             <<" ВАШ ВЫБОР: "; n = failure();
        while ((n < 0) || (n > 6)) {
            cout <<" ТАКОЙ КОМАНДЫ НЕ СУЩЕСТВУЕТ. ПОВТОРИТЕ ВВОД: ";
            n = failure();
        }
        if (n == 1) //1 - CОЗДАНИЕ ДЕРЕВА С ЗАДАННЫМ ЧИСЛОМ ВЕРШИН СО СЛУЧАЙНЫМИ КЛЮЧАМИ
            TreeCreator();
        else if (n == 2) //2 - ДОБАВЛЕНИЕ В ДЕРЕВО ОДНОЙ ВЕРШИНЫ С ЗАДАННЫМ ПОЛЬЗОВАТЕЛЕМ ЗНАЧЕНИЕМ КЛЮЧА
            AddNode();
        else if (n == 3) //3 - ПОИСК В ДЕРЕВЕ ВЕРШИНЫ С ЗАДАННЫМ КЛЮЧОМ
            FindDialog();
        else if (n == 4) //4 - ВЫВОД ДЕРЕВА В НАГЛЯДНОМ ВИДЕ С ПОМОЩЬЮ ОБРАТНО-СИММЕТРИЧНОГО ОБХОДА
            show(2);
        else if (n == 5) //5 - ВЫВОД ВСЕХ ВЕРШИН В ПОРЯДКЕ ВОЗРАСТАНИЯ ИХ КЛЮЧЕЙ
            show(1);
        else if (n == 6) //6 - УДАЛЕНИЕ ВЕРШИНЫ С ЗАДАННЫМ ЗНАЧЕНИЕМ КЛЮЧА
            DelNode();
        else if (n == 0) //0 - ВЫХОД ИЗ ПРОГРАММЫ
            break;
    }
    cout << "\n ОЧИСТКА ПАМЯТИ...\n";
    delTp(pRoot);
    cout << "\n ВЫХОД ИЗ ПРОГРАММЫ...\n\n ";
    return 0;
}