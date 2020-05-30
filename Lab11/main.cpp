//Лабораторная работа №11 (Раздел 1, Тема 5, Номер 3) - ОБРАБОТКА ПРОИЗВОЛЬНЫХ ДВОИЧНЫХ ДЕРЕВЬЕВ

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
    Tp *Left; //ссылочная переменная-указатель на левый элемент
    Tp *Right; //ссылочная переменная-указатель на правый элемент
} *pRoot, *pParent; // pRoot - указатель на корень дерева,
                                  // pParent - указатель на родительскую вершину, глобальные переменные

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

//ПОИСК ВЕРШИНЫ С ЗАДАННЫМ ЗНАЧЕНИЕМ ИНФОРМАЦИОННОЙ ЧАСТИ
void Find(Tp *pCurrent, int _value) {
//    founded = false;
    if (!founded)
        if (pCurrent != NULL) {
            if (pCurrent -> value == _value) {
                founded = true;
                pParent = pCurrent;
            }
            else {
                Find (pCurrent -> Left, _value); // поиск в левом поддереве
                Find (pCurrent -> Right, _value); // поиск в  правых поддереве
            }
        }
}

//ПОИСК ВЕРШИНЫ С ЗАДАННЫМ ЗНАЧЕНИЕМ ИНФОРМАЦИОННОЙ ЧАСТИ (ДИАЛОГОВАЯ ФУНКЦИЯ)
void FindDialog() {
    int _value;
    cout <<"\n ВВЕДИТЕ ЗНАЧЕНИЕ ВЕРШИНЫ, КОТОРУЮ ХОТИТЕ НАЙТИ: "; _value = failure();
    founded = false;
    Find(pRoot, _value);
    if (founded){
        cout <<" ЭЛЕМЕНТ '" << _value << "' НАЙДЕН\n";
        founded = false;
    }
    else
        cout <<" ЭЛЕМЕНТ '" << _value << "' НЕ НАЙДЕН\n";
}

//ПОСТРОЧНЫЙ ВЫВОД ДЕРЕВА
void show(){
    cout <<"\n СОСТОЯНИЕ ДЕРЕВА:";
    if (pRoot != NULL) {
        cout <<"\n\n ПОСТРОЧНЫЙ ВЫВОД В ПРЯМОМ ПОРЯДКЕ:\n\n";
        Forward(pRoot, 0);
        cout <<"\n ПОСТРОЧНЫЙ ВЫВОД В СИММЕТРИЧНОМ ПОРЯДКЕ:\n\n";
        Symmetric(pRoot, 0);
        cout <<"\n ПОСТРОЧНЫЙ ВЫВОД В ОБРАТНО-СИММЕТРИЧНОМ ПОРЯДКЕ:\n\n";
        BackSymmetric(pRoot, 0);
    }
    else {
        cout <<" ДЕРЕВО ПУСТОЕ\n\n";
    }
}

//ДОБАВЛЕНИЕ ВЕРШИНЫ
Tp *AddTp(Tp *pTemp, int _value) {
    pTemp = new Tp;
    pTemp -> Left = pTemp -> Right = NULL; //у новой вершины еще нет левого и правого потомков
    pTemp -> value = _value;
    return pTemp; //возвращаем адрес созданного корня
}

//ДОБАВЛЕНИЕ ВЕРШИНЫ (ДИАЛОГОВАЯ ФУНКЦИЯ)
void AddNode() {
    int _value, n;
    if (pRoot != NULL) { //если дерево непустое
        cout <<"\n ВВЕДИТЕ ЗНАЧЕНИЕ ВЕРШИНЫ-РОДИТЕЛЯ ДЛЯ НОВОГО ЭЛЕМЕНТА: "; _value = failure();
        founded = false;
        Find(pRoot, _value); //ищем вершину-родитель для нового элемента
        if (founded) {
            founded = false;
            if (pParent -> Left == NULL || pParent -> Right == NULL) { //ПРОВЕРКА ЧИСЛА ПОТОМКОВ У НАЙДЕННОЙ РОДИТЕЛЬСКОЙ ВЕРШИНЫ
                cout <<"\n ВВЕДИТЕ ЗНАЧЕНИЕ, КОТОРОЕ ХОТИТЕ ПРИСВОИТЬ ВЕРШИНЕ: "; _value = failure();
            }
            if (pParent -> Left == NULL && pParent -> Right == NULL) {
                cout <<"\n ВЕРШИНА НЕ ИМЕЕТ НИ ОДНОГО ПОТОМКА. КАКУЮ ВЕРШИНУ (1 - ЛЕВЫЙ ПОТОМОК; 2 - ПРАВЫЙ ПОТОМОК) ДОБАВИТЬ?\n ВАШ ВЫБОР: ";
                n = failure();
                while ((n != 1) && (n != 2)) {
                    cout <<" ТАКОЙ КОМАНДЫ НЕ СУЩЕСТВУЕТ. ПОВТОРИТЕ ВВОД: "; n = failure();
                }
                if (n == 1) {
                    pParent -> Left = AddTp(pParent->Left, _value);
                    cout <<" ВЕРШИНА УСПЕШНО ДОБАВЛЕНА КАК ЛЕВЫЙ ПОТОМОК РОДИТЕЛЬСКОЙ ВЕРШИНЫ \n";
                }
                if (n == 2) {
                    pParent -> Right = AddTp(pParent->Right, _value);
                    cout <<" ВЕРШИНА УСПЕШНО ДОБАВЛЕНА КАК ПРАВЫЙ ПОТОМОК РОДИТЕЛЬСКОЙ ВЕРШИНЫ \n";
                }
            }
            else if (pParent -> Left == NULL) {
                pParent -> Left = AddTp(pParent->Left, _value);
                cout <<" ВЕРШИНА УСПЕШНО ДОБАВЛЕНА КАК ЛЕВЫЙ ПОТОМОК РОДИТЕЛЬСКОЙ ВЕРШИНЫ \n";
            }
            else if (pParent -> Right == NULL) {
                pParent -> Right = AddTp(pParent->Right, _value);
                cout <<" ВЕРШИНА УСПЕШНО ДОБАВЛЕНА КАК ПРАВЫЙ ПОТОМОК РОДИТЕЛЬСКОЙ ВЕРШИНЫ \n";
            }
            else { cout <<" ДОБАВЛЕНИЕ НЕВОЗМОЖНО: ВЕРШИНА-РОДИТЕЛЬ УЖЕ ИМЕЕТ ДВУХ ПОТОМКОВ  \n"; return;}
            show();
        }
        else cout <<" ВЕРШИНА-РОДИТЕЛЬ '"<< _value<<"' НЕ НАЙДЕНА \n";
    }
    else { //если дерево пустое, то создать корень дерева
        pRoot = new Tp;
        cout <<"\n ВВЕДИТЕ ЗНАЧЕНИЕ ВЕРШИНЫ-КОРНЯ, КОТОРУЮ ХОТИТЕ ДОБАВИТЬ: "; _value = failure();
        pRoot -> Left = pRoot -> Right = NULL;
        pRoot -> value = _value;
        cout <<" КОРЕНЬ ДЕРЕВА '"<< pRoot -> value<<"' УСПЕШНО СОЗДАН \n";
    }
}

//ОЧИСТКА ПАМЯТИ (УДАЛЕНИЕ ВЕРШИН ДЕРЕВА)
void delTp(Tp *pCurrent) {
    if (pCurrent != NULL) {
        delTp(pCurrent -> Left); // сначала удалять все элементы с левого конца
        delTp(pCurrent -> Right); // потом удалять все элементы с правого конца
        delete pCurrent; // в конце удалить сам элемент-корень
        cout << " ПОДДЕРЕВО СО ЗНАЧЕНИЕМ КОРНЕВОЙ ВЕРШИНЫ '" << pCurrent -> value << "' УДАЛЕНО\n";
    }
};

int main() {
    pRoot = NULL; // создать пустое дерево
    int n = -1;
    while (true) {
        n = -1;
        cout << " ___________________________________________________________\n\n";
        cout <<" ВЫБЕРИТЕ ДЕЙСТВИЕ ИЗ СПИСКА\n";
        cout <<" 1 - ПОИСК ВЕРШИНЫ С ЗАДАННЫМ ЗНАЧЕНИЕМ ИНФОРМАЦИОННОЙ ЧАСТИ\n";
        cout <<" 2 - ДОБАВЛЕНИЕ ЛЕВОГО ИЛИ ПРАВОГО ПОТОМКА ДЛЯ ЗАДАННОЙ ВЕРШИНЫ\n";
        cout <<" 3 - ПОСТРОЧНЫЙ ВЫВОД ДЕРЕВА С ПОМОЩЬЮ ОСНОВНЫХ ПРАВИЛ ОБХОДА\n";
        cout <<" 4 - УНИЧТОЖЕНИЕ ВСЕГО ДЕРЕВА\n";
        cout <<" 5 - ВЫХОД ИЗ ПРОГРАММЫ\n";
        cout <<" ВАШ ВЫБОР: "; n = failure();
        while ((n <= 0) || (n > 5)) {
            cout <<" ТАКОЙ КОМАНДЫ НЕ СУЩЕСТВУЕТ. ПОВТОРИТЕ ВВОД: ";
            n = failure();
        }
        if (n == 1)
            FindDialog();
        else if (n == 2)
            AddNode();
        else if (n == 3)
            show();
        else if (n == 4) {
            cout << "\n УНИЧТОЖЕНИЕ ВСЕГО ДЕРЕВА (ОЧИСТКА ПАМЯТИ)...\n";
            delTp(pRoot);
            pRoot = NULL; //ИНИЦИИРУЕМ УКАЗАТЕЛЬ КОРНЕВОЙ ВЕРШИНЫ ПУСТЫМ ЗНАЧЕНИЕМ ДЛЯ ПОВТОРНОГО СОЗДАНИЯ ДЕРЕВА С НОВОЙ КОРНЕВОЙ ВЕРШИНОЙ
        }
        else if (n==5)
            break;
    }
    cout << "\n ОЧИСТКА ПАМЯТИ...\n";
    delTp(pRoot); //    pRoot = NULL;
    cout << "\n ВЫХОД ИЗ ПРОГРАММЫ...\n\n ";
    return 0;
}
