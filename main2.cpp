#include <iostream>
#include <windows.h>
#include <memory>

using namespace std;

class Base
{
public:
    Base()
    {
        cout << "Base(): конструктор\n";
    }

    Base(const Base& obj)
    {
        cout << "Base(const Base&): копирование\n";
    }

    virtual ~Base()
    {
        cout << "~Base(): деструктор\n";
    }
};

class Desc : public Base
{
public:
    Desc()
    {
        cout << "Desc(): конструктор\n";
    }

    Desc(const Desc& obj) : Base(obj)
    {
        cout << "Desc(const Desc&): копирование\n";
    }

    ~Desc()
    {
        cout << "~Desc(): деструктор\n";
    }
};

void func1(Base obj)
{
    cout << "func1(Base obj) - передача по значению\n";
}

void func2(Base* obj)
{
    cout << "func2(Base* obj) - передача указателя\n";
}

void func3(Base& obj)
{
    cout << "func3(Base& obj) - передача ссылки\n";
}


Base ret1()
{
    cout << "ret1(): возврат по значению (локальный объект)\n";
    Base obj;
    return obj; // OK
}

/*
Base* ret2()
{
    cout << "ret2(): возврат указателя на локальный объект (ОШИБКА)\n";
    Base obj;
    return &obj; //Удаляется
}
*/
/*
Base& ret3()
{
    cout << "ret3(): возврат ссылки на локальный объект (ОШИБКА)\n";
    Base obj;
    return obj; //Удаляется
}
*/
Base ret4()
{
    cout << "ret4(): возврат по значению (dynamic)\n";
    Base* obj = new Base;
    return *obj; //утечка памяти
}

Base* ret5()
{
    cout << "ret5(): возврат указателя (dynamic)\n";
    return new Base;//ОК
}

Base& ret6()
{
    cout << "ret6(): возврат ссылки (dynamic)\n";
    return *(new Base); //утечка памяти
}


void func_unique(unique_ptr<Base> ptr)
{
    cout << "func_unique: получили unique_ptr\n";
}

unique_ptr<Base> create_unique()
{
    cout << "create_unique: создаём unique_ptr\n";
    return make_unique<Base>();
}


void func_shared(shared_ptr<Base> ptr)
{
    cout << "func_shared: получили shared_ptr\n";
    cout << "use_count = " << ptr.use_count() << endl;
}

shared_ptr<Base> create_shared()
{
    cout << "create_shared: создаём shared_ptr\n";
    return make_shared<Base>();
}


void foo1()
{
    cout << "============================================================\n";
    cout << "ПЕРЕДАЧА ОБЪЕКТОВ В ФУНКЦИИ\n";

    Base b;
    Desc d;

    cout << "\n--- func1 (по значению) ---\n";
    func1(b);
    func1(d); //передатся только родитель без потомка

    cout << "\n--- func2 (указатель) ---\n";
    func2(&b);
    func2(&d);

    cout << "\n--- func3 (ссылка) ---\n";
    func3(b);
    func3(d);

    cout << "============================================================\n";
}

void foo2()
{
    cout << "============================================================\n";
    cout << "ВОЗВРАТ ЛОКАЛЬНЫХ ОБЪЕКТОВ\n";

    Base a = ret1();
    cout << "ret2() и ret3() в коментариях, так как выдают ошибку\n";
    //Base* b = ret2(); 
    //Base& c = ret3(); 


    cout << "============================================================\n";

    cout << "ВОЗВРАТ ДИНАМИЧЕСКИХ ОБЪЕКТОВ\n";

    Base d = ret4();   // утечка
    Base* e = ret5();  //нужно delete
    Base& f = ret6();  //утечка

    delete e;

    cout << "============================================================\n";
}

void foo3()
{
    cout << "============================================================\n";
    cout << "УМНЫЕ УКАЗАТЕЛИ\n";

    // ========================================================
    cout << "\nUNIQUE_PTR\n";

    unique_ptr<Base> p1 = make_unique<Base>();
    cout << "Создан p1\n";

    cout << "Передача unique_ptr в функцию (перемещение)\n";
    func_unique(move(p1)); // p1 станет nullptr

    if (!p1)
        cout << "p1 теперь nullptr\n";

    cout << "Создание через возврат функции\n";
    unique_ptr<Base> p2 = create_unique();

    cout << "Выход из области -> объект удалится автоматически\n";

    // ========================================================
    cout << "\nSHARED_PTR\n";

    shared_ptr<Base> s1 = make_shared<Base>();
    cout << "Создан s1, use_count = " << s1.use_count() << endl;

    {
        shared_ptr<Base> s2 = s1;
        cout << "Создан s2, use_count = " << s1.use_count() << endl;

        func_shared(s2);

        cout << "Выход из внутреннего блока\n";
    }

    cout << "После удаления s2, use_count = " << s1.use_count() << endl;

    cout << "Создание через возврат функции\n";
    shared_ptr<Base> s3 = create_shared();
    cout << "s3 use_count = " << s3.use_count() << endl;

    cout << "Выход из области -> объект удалится, когда счетчик = 0\n";

    cout << "============================================================\n";
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    foo1();
    foo2();
    foo3();

    return 0;
}