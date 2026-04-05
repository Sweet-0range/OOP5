#include "iostream"
#include "string"
#include <windows.h>

class BaseClass
{
public:
    BaseClass()
    {
        std::cout << "Конструктор предка\n";
    }
    virtual ~BaseClass()
    {
        std::cout << "Деструктор предка\n";
    }
    void method1()
    {
        std::cout << "VМетод1 предка\nВызываем метод2\n";
        method2();
    }
    void method2()
    {
        std::cout << "Метод2 предка\n";
    }
    void method3()
    {
        std::cout << "Метод3 предка\n";
        method4();
    }
    virtual void method4()
    {
        std::cout << "Метод4 предка\n";
    }
    virtual std::string classname()
    {
        return "BaseClass";
    }
    virtual bool isA(std::string name)
    {
        return name == "BaseClass";
    }
};


class HeirClass : public BaseClass
{
public:
    HeirClass()
    {
        std::cout << "Конструктор потомка\n";
    }
    ~HeirClass() override 
    {
        std::cout << "Деструктор потомка\n";
    }
    /*
    void method1()
    {
        std::cout << "Метод1 потомка\n";
    };
    */
    void method2()
    {
         std::cout << "Метод2 потомка\n";
    }
    /*
    void method3()
    {
         std::cout << "Метод3 потомка\n";
    };
    */
    void method4() override
    {
         std::cout << "Метод4 потомка\n";
    }
    bool isA(std::string name) override
    {
        return name == "HeirClass" || BaseClass::isA(name);
    }
    std::string classname() override
    {
        return "HeirClass";
    }
};

void foo1()
{
    std::cout << "============================================================\n";
    std::cout <<"\nfoo1\nМетод1 у родителя и вызывает Метод2 не виртуальный\n";
    std::cout << "Создание обьектов статически\nРодитель:\n";
    BaseClass BC;
    std::cout << "Потомок:\n";
    HeirClass HC;

    std::cout << "Вызов метода1 у родителя:\n";
    BC.method1();
    std::cout << "Вызов метода1 у потомка:\n";
    HC.method1();
    std::cout << "============================================================\n";
}

void foo2()
{
    std::cout << "============================================================\n";
    std::cout <<"\nfoo2\nМетод1 у родителя и вызывает Метод2 не виртуальный\n";
    std::cout << "Создание обьектов диномически BaseClass = new BaseClass\n";
    BaseClass* BC1 = new BaseClass;
    std::cout << "Создание обьектов диномически BaseClass = new HeirClass\n";
    BaseClass* BC2 = new HeirClass;
    std::cout << "Создание обьектов диномически HeirClass = new HeirClass\n";
    HeirClass* HC = new HeirClass;

    std::cout << "Вызов метода1 у BaseClass = new BaseClass\n";
    BC1->method1();

    std::cout << "Вызов метода1 у BaseClass = new HeirClass\n";
    BC2->method1();

    std::cout << "Вызов метода1 у HeirClass = new HeirClass:\n";
    HC->method1();


    std::cout << "Деструктор BaseClass = new BaseClass\n";
    delete BC1;
    std::cout << "Деструктор BaseClass = new HeirClass\n";
    delete BC2;
    std::cout << "Деструктор HeirClass = new HeirClass:\n";
    delete HC;
    std::cout << "============================================================\n";
}

void foo3()
{
    std::cout << "============================================================\n";
    std::cout <<"\nfoo3\nМетод3 у родителя и вызывает Метод4 виртуальный\n";
    std::cout << "Создание обьектов статически\nРодитель:\n";
    BaseClass BC;
    std::cout << "Потомок:\n";
    HeirClass HC;

    std::cout << "Вызов метода1 у родителя:\n";
    BC.method3();
    std::cout << "Вызов метода1 у потомка:\n";
    HC.method3();
    std::cout << "============================================================\n";
}

void foo4()
{
    std::cout << "============================================================\n";
    std::cout <<"\nfoo4\nМетод3 у родителя и вызывает Метод4 виртуальный\n";
    std::cout << "Создание обьектов диномически BaseClass = new BaseClass\n";
    BaseClass* BC1 = new BaseClass;
    std::cout << "Создание обьектов диномически BaseClass = new HeirClass\n";
    BaseClass* BC2 = new HeirClass;
    std::cout << "Создание обьектов диномически HeirClass = new HeirClass\n";
    HeirClass* HC = new HeirClass;

    std::cout << "Вызов метода1 у BaseClass = new BaseClass\n";
    BC1->method3();

    std::cout << "Вызов метода1 у BaseClass = new HeirClass\n";
    BC2->method3();

    std::cout << "Вызов метода1 у HeirClass = new HeirClass:\n";
    HC->method3();


    std::cout << "Деструктор BaseClass = new BaseClass\n";
    delete BC1;
    std::cout << "Деструктор BaseClass = new HeirClass\n";
    delete BC2;
    std::cout << "Деструктор HeirClass = new HeirClass:\n";
    delete HC;
    std::cout << "============================================================\n";
}

void foo5()
{
    std::cout << "============================================================\n";
    std::cout << "Создание обьектов диномически BaseClass = new BaseClass\n";
    BaseClass* BC1 = new BaseClass;
    std::cout << "Создание обьектов диномически BaseClass = new HeirClass\n";
    BaseClass* BC2 = new HeirClass;
    std::cout << "Создание обьектов диномически HeirClass = new HeirClass\n";
    HeirClass* HC = new HeirClass; 

    std::cout << "Вызов classname у BaseClass = new BaseClass\n" << BC1->classname();

    std::cout << "Вызов classname у BaseClass = new HeirClass\n" << BC2->classname();

    std::cout << "Вызов classname у HeirClass = new HeirClass:\n" << HC->classname();


    std::cout << "Проверка isA(BaseClass) у BaseClass = new BaseClass:\n" << BC1->isA("BaseClass");

    std::cout << "Проверка isA(BaseClass) у BaseClass = new HeirClass:\n"<<BC2->isA("BaseClass");

    std::cout << "Проверка isA(BaseClass) у HeirClass = new HeirClass:\n"<<HC->isA("BaseClass");

    
    std::cout << "Проверка isA(HeirClass) у BaseClass = new BaseClass:\n"<<BC1->isA("HeirClass");

    std::cout << "Проверка isA(HeirClass) у BaseClass = new HeirClass:\n"<<BC2->isA("HeirClass");

    std::cout << "Проверка isA(HeirClass) у HeirClass = new HeirClass:\n"<<HC->isA("HeirClass");

    std::cout <<"Приведение типов\nСоздание BaseClass = new HeirClass\n";
    BaseClass* obj = new HeirClass;

    std::cout <<"Проверка что обьект HeirClass\n";
    if (obj->isA("HeirClass"))
    {
        std::cout <<"Результат проверки if (obj->isA(HeirClass)):" << obj->isA("HeirClass") << std::endl;
        std::cout <<"Приведение через dynamic_cast<HeirClass*> и вызов метода2\n";
        dynamic_cast<HeirClass*>(obj)->method2();
    }

    std::cout << "Деструктор BaseClass = new BaseClass\n";
    delete BC1;
    std::cout << "Деструктор BaseClass = new HeirClass\n";
    delete BC2;
    std::cout << "Деструктор HeirClass = new HeirClass:\n";
    delete HC;

    std::cout << "Деструктор у BaseClass = new HeirClass обьекта, который приводили тип:\n";
    delete obj;
    std::cout << "============================================================\n";
}
int main() {
    SetConsoleOutputCP(CP_UTF8);                                             
    SetConsoleCP(CP_UTF8);

    std::cout << "Метод1 у родителя и вызывает переопределённый Метод2 не виртуальный\n";
    foo1();
    foo2();
    std::cout << "Метод3 у родителя и вызывает переопределённый Метод2 виртуальный\n";
    foo3();
    foo4();
    std::cout << "Вызов classname и isA\n";
    foo5();
    return 0;
}