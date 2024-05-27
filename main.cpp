#include <iostream>
#include <vector>

using namespace std;

#include "povara.h"
#include "FunctionBD.h"
#include "sqlite3.h"

ActionOfCooker::ActionOfCooker()
{
    WearingGlasses = bool (rand() % 2);
    ColorOfClothes = bool (rand() % 2);
    Race = RaceCooker::Unknown;

    bool Vacation;
    bool Cooking;
    int Skill;
    string Sex;
    string Post;
}

CookerContainer::CookerContainer(int maxSize) // конструктор контейнера с поварами (1)
{
    CookerBox = new CookerPtr[maxSize];
    for(int i = 0; i < MaxSize; i++)
    {
        CookerBox[i] = NULL;
    }
    CookerCount = 0;
    MaxSize = maxSize;
}

CookerContainer::~CookerContainer() // деструктор контейнера с поварами (1)
{
    for(int i=0; i<MaxSize; i++)
    {
        if(CookerBox[i] != NULL)
        {
            delete CookerBox[i];
            CookerBox[i] = NULL;
        }
    }

    delete[] CookerBox;
}

void ActionOfCooker::CookOff() // описание функции окончания готовки
{
    wcout << L"Дело сделано!" << endl;
    Cooking = false;
    if (Skill >= 100)
    {
        Skill = 100;
    }
    else
    {
        Skill +=10;
    }
}


wstring PrintCookerType(const Cooker type) // описание типа повара
{
    switch(type)
    {
        case Cooker::Mouse: return L"Мышь";
        case Cooker::Cat: return L"Кот";
        case Cooker::Robot: return L"Робот";
        case Cooker::WheelchairUser: return L"Колясочник";
        default: return L"Неизвестно";
    }
}

wstring PrintRaceCookerType(const RaceCooker race) // описание расы повара
{
    switch(race)
    {
        case RaceCooker::African: return L"Негроид";
        case RaceCooker::European: return L"Европеец";
        case RaceCooker::Asian: return L"Азиат";
        default: return L"Неизвестно";
    }
}

void CookerContainer::AddCooker(CookerPtr newCooker) // создание нового повара
{
    CookerBox[CookerCount++] = newCooker;
}

void OutPut(CookerContainer *cookerBox) //функция для вывода поваров
{
    for(int i=0; i<cookerBox->GetCount(); i++)
    {
        const CookerPtr outCook  = cookerBox->GetByIndex(i);
        wcout << i << L" (" << PrintCookerType(outCook->GetCooker()) << L")" << endl;
    }
}

void Vaccation (CookerContainer *cookerBox) // отправили всех поварят колясочников в отпуск
{
    for(int i=0; i<cookerBox->GetCount(); i++)
    {
        const CookerPtr outCook  = cookerBox->GetByIndex(i);
        if(outCook->GetCooker() == Cooker::WheelchairUser)
        {
            outCook->VacON();
        }

    }
    wcout << L"Все поварята отправлены в отпуск" << endl;
}

void OutPut_iterator(Iterator<CookerPtr> *iter) // функция для вывода всех поваров через итератор
{
    for(iter->First(); !iter->IsDone(); iter->Next())
    {
        const CookerPtr outCook = iter->CurrentItem();
        wcout << L" (" << PrintCookerType(outCook->GetCooker()) << L")" << endl;
    }
}

void HaveGlasses(Iterator<CookerPtr> *iter)
{
    for(iter->First(); !iter->IsDone(); iter->Next())
    {
        const CookerPtr outCook = iter->CurrentItem();

        wcout<<PrintCookerType(outCook->GetCooker())<<L" = ";
        wcout<<(outCook->WearGlasses() ? L" Очки есть" : L" Очков нет")<<endl;
    }
}

void ColorCloth(Iterator<CookerPtr> *iter)
{
    for(iter->First(); !iter->IsDone(); iter->Next())
    {
        const CookerPtr outCook = iter->CurrentItem();

        wcout<<PrintCookerType(outCook->GetCooker())<<L" = ";
        wcout<<(outCook->ColClothes() ? L" Цвет фартука черный" : L" Цвет фартука белый")<<endl;
    }
}

void RCooker(Iterator<CookerPtr> *iter)
{
    for(iter->First(); !iter->IsDone(); iter->Next())
    {
        const CookerPtr outCook = iter->CurrentItem();

        wcout<<PrintCookerType(outCook->GetCooker())<<L" = ";
        wcout<<PrintRaceCookerType(outCook->GetRace()) << endl;
    }
}

ActionOfCooker *CreateCookerType(const Cooker type) //фабричный метод
{
    switch(type)
    {
        case Cooker::Mouse: return new Mouse;
        case Cooker::Cat: return new Cat;
        case Cooker::Robot: return new Robot;
        case Cooker::WheelchairUser: return new WheelchairUser;
        default: return NULL;
    }
}

ActionOfCooker *ActionOfCooker::CreateCooker(Cooker type)
{
    return CreateCookerType(type);
}

int main()
{
    int a;
    setlocale(LC_ALL, "Russian");
    wcout << L"Введите количество поваров" << endl;
    cin >> a;
    //CookerContainer cookerBox(a); // создание a поваров (циклом for, повара помещаются в 1-й контейнер)
    //CookerContainerV2 cookerBox; // создание поваров (циклом for, повара помещаются во 2-й контейнер)
    CookerBD cookerBox;

    for(int i=0; i<a; i++)
    {
        cookerBox.AddCooker(CreateCookerType(Cooker(rand() % 4)));
    }

    /*for(int i=0; i<=(a/10); i++)
    {
        cookerBox.AddCooker(new Cat());
    }

    for(int i=0; i<=10; i++)
    {
        cookerBox.AddCooker(new Robot());
    }

    for(int i=0; i<=(a/50); i++)
    {
        cookerBox.AddCooker(new WheelchairUser());
    }*/

    //Iterator<CookerPtr> *iter = cookerBox.GetIterator();

    //Iterator<CookerPtr> *iter = new FirstDecorator(cookerBox.GetIterator(), true);
    //HaveGlasses(iter);
    //ColorCloth(iter);

    Iterator<CookerPtr> *iter = new ThirdDecorator( new FirstDecorator(cookerBox.GetIterator(), true),RaceCooker::European);
    RCooker(iter);

    //OutPut_iterator(iter);
    delete iter;
    //OutPut(&cookerBox);
    //Vaccation(&cookerBox);

    return 0;
}
