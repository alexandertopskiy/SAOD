//Лабораторная работа №10 (Раздел 1, Тема 5, Номер 2) -
// ИДЕАЛЬНО СБАЛАНСИРОВАННОЕ ДВОИЧНОЕ ДЕРЕВО С НЕРЕКУРСИВНЫМ ВАРИАНТОМ СИММЕТРИЧНОГО ОБХОДА (ВСПОМОГАТЕЛЬНЫЙ СТЕК)

//СОЗДАЕМ ВСПОМОГАТЕЛЬНЫЙ СТЕК ДЛЯ ХРАНЕНИЯ ПОСЛЕДОВАТЕЛЬНОСТИ ПРОЙДЕННЫХ ВЕРШИН
// sОТ КОРНЯ ДО ТЕКУЩЕЙ ВЕРШИНЫ И УРОВНЯ ЭТИХ ВЕРШИН В ДЕРЕВЕ

#include <iostream>
#include <cstdlib>

using namespace std;

int N; //количество вершин в дереве, глобальная переменная

//метод обработки ошибок ввода (проверяет, чтобы были введены ТОЛЬКО цифры, без букв)
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

//ОПИСАНИЕ СТРУКТУРЫ ДЕРЕВА TreePoint
struct Tp {
    int value; //строка-значение
    Tp *Left; //ссылочная переменная-указатель на левый элемент
    Tp *Right; //ссылочная переменная-указатель на правый элемент
} *pRoot; //ссылочная переменная для адреса корневой вершины.

struct Stack {
    int level; //"уровень" вершины
    Tp *Point; //указатели на пройденную вершину дерева
    Stack *next; //указатели на следующий элемент стека
} *sp; // sp - указатель вершины главного стека

//инициализация, создание пустого стека
inline void initStack(Tp *pRoot) {
    sp = new Stack;
    sp -> Point = pRoot;
    sp -> level = -1;
    sp -> next = NULL;
}

// Проверка пустоты стека
bool isEmpty(){
    if (sp -> level < 0) return 1;
    else return 0;
}

Tp *AddNodes(Tp *pCurrent, int aN) { //ДОБАВЛЕНИЕ ВЕРШИН (ПОСТРОЕНИЕ ИСД)
    Tp *pTemp;
    int Nl, Nr;
    if (aN == 0)  // если нет вершин для размещения
        return NULL; // формируем пустую ссылку
    else {
        Nl = aN / 2; //число вершин слева
        Nr = aN - Nl - 1; //число вершин справа
        pTemp = new Tp; //создаем корень поддерева, выделяем память
        pTemp -> value = rand() % 100; //заносим в информационную часть случайное целое число в интервале от 0 до 99
        pTemp -> Left = AddNodes(pTemp -> Left, Nl); // уходим на создание левого поддерева
        pTemp -> Right = AddNodes(pTemp -> Right, Nr);
        pCurrent = pTemp;
        //        cout << "\n Вершина создана\n";
        return pTemp; //возвращаем адрес созданного корня
    }
}

//ПОСТРОЧНЫЙ ВЫВОД В ПРЯМОМ НАПРАВЛЕНИИ
void Forward(Tp *pCurrent, int level) {
    if (pCurrent != NULL) {
        string str; //обработка корневой вершины pCurrent
        for (int i = 0; i < level; i++)
            str+= "     ";
        cout << " " << str << pCurrent->value << "\n" ;
        Forward (pCurrent -> Left, level + 1); //обработка  всех левых поддеревьев
        Forward (pCurrent -> Right, level + 1); //обработка  всех правых поддеревьев
    }

}

//НЕРЕКУРСИВНЫЙ ВЫВОД В СИММЕТРИЧНОМ НАПРАВЛЕНИИ
void Nonrecursive() {
    initStack(pRoot);
    Tp *pCurrentTree = pRoot; //начинаем с корневой вершины дерева
    bool Stop = false;
    int level = 0;

    while (!Stop) {
        while (pCurrentTree != NULL) {
            Stack *item  = new Stack; //занести pCurrent в стек
            item -> level = level;
            item -> Point = pCurrentTree;
            item -> next = sp;
            sp = item;
            pCurrentTree = sp -> Point;
            pCurrentTree = pCurrentTree -> Left;
            level++;
        }
        if (isEmpty()) //если стек пуст
            Stop = true; //завершить основной цикл
        else { //обработка и вывод вершины
            level = sp -> level;
            pCurrentTree = sp -> Point;
            string str=""; //обработка корневой вершины pCurrent
            for (int i = 0; i < level; i++)
                str+= "     ";
            cout << " " << str << (pCurrentTree -> value) << "\n" ;
            Stack *current = sp;
            sp = sp->next;
            delete current;
            pCurrentTree = pCurrentTree -> Right;
            level++;
        }
    }
}

//ПОСТРОЧНЫЙ ВЫВОД В СИММЕТРИЧНОМ НАПРАВЛЕНИИ
void Symmetric (Tp *pCurrent, int level) {
    if (pCurrent != NULL) {
        Symmetric (pCurrent -> Left, level + 1); //обработка  всех левых поддеревьев
        string str; //обработка корневой вершины pCurrent
        for (int i = 0; i < level; i++)
            str+= "     ";
        cout << " " << str << pCurrent->value << "\n" ;
        Symmetric (pCurrent -> Right, level + 1); //обработка  всех правых поддеревьев
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

//ОЧИСТКА ПАМЯТИ (УДАЛЕНИЕ ВЕРШИН ДЕРЕВА)
void delTp(Tp *pCurrent) {
    if (pCurrent != NULL) {
        delTp(pCurrent -> Left); // сначала удалять все элементы с левого конца
        delTp(pCurrent -> Right); // потом удалять все элементы с правого конца
        delete pCurrent; // в конце удалить сам элемент-корень
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); //инициализация генератора псевдослучайных чисел rand
    while (true) {
        cout << " ___________________________________________________________\n\n"; N = -1;
        while (N <= 0) { //ПОСТРОЕНИЕ ИСД С ЗАДАННЫМ ЧИСЛОМ ВЕРШИН
            cout <<" СКОЛЬКО ВЕРШИН БУДЕТ В ИДЕАЛЬНО СБАЛАНСИРОВАННОМ ДВОИЧНОМ ДЕРЕВЕ?\n КОЛ-ВО ВЕРШИН: ";
            N = failure();
            if (N<=0) cout <<" ДЕРЕВО С НЕПОЛОЖИТЕЛЬНЫМ ЧИСЛОМ " << N << " ВЕРШИН ВЫВОДИТЬСЯ НЕ БУДЕТ. ПОВТОРИТЕ ВВОД\n";
            else {
                pRoot = AddNodes(pRoot, N);
                cout <<" ИДЕАЛЬНО СБАЛАНСИРОВАННОЕ ДЕРЕВО С ЧИСЛОМ ВЕРШИН '" << N << "' СОЗДАНО\n";
            }
        }
        cout <<"\n ПОСТРОЧНЫЙ ВЫВОД В ПРЯМОМ ПОРЯДКЕ:\n\n";
        Forward(pRoot, 0);
        cout <<"\n ПОСТРОЧНЫЙ ВЫВОД В СИММЕТРИЧНОМ ПОРЯДКЕ:\n\n";
        Symmetric(pRoot, 0);
        cout <<"\n НЕРЕКУРСИВНЫЙ ВАРИАНТ СИММЕТРИЧНОГО ОБХОДА:\n\n";
        Nonrecursive();
        cout <<"\n ПОСТРОЧНЫЙ ВЫВОД В ОБРАТНО-СИММЕТРИЧНОМ ПОРЯДКЕ:\n\n";
        BackSymmetric(pRoot, 0);
        cout << "\n ОЧИСТКА ПАМЯТИ...\n";
        delTp(pRoot);
    }
    return 0;
}