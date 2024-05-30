#ifndef PovaraH
#define PovaraH
#include <string>
#include <list>

using namespace std;

#include"Patterns.h"
#include"sqlite3.h"

enum class Cooker: int // перечисление поваров
{
    Mouse = 0,
    Cat = 1,
    Robot = 2,
    WheelchairUser = 3,
    Unknown = -1
};

enum class RaceCooker: int
{
    African,
    European,
    Asian,
    Unknown
};

class ActionOfCooker
{
protected:
     bool Cooking;
     string Sex;
     string Post;
     bool WearingGlasses;
     bool ColorOfClothes;
     Cooker Type;
     RaceCooker Race;
     ActionOfCooker();
public:
    int Skill;
    bool ColClothes() const {return ColorOfClothes;}
    bool WearGlasses() const {return WearingGlasses;}
    virtual ~ActionOfCooker() {};
    virtual void CookOff() = 0; // не готовка
    virtual void CookON() = 0; // готовка
    virtual void Dism() = 0; // увольнение
    virtual void VacON() = 0; // отправка в отпуск
    virtual void VacOff() = 0; // вернуть из отпуска
    virtual Cooker GetCooker() const = 0; // определение повара
    virtual RaceCooker GetRace() {return Race;}
    static ActionOfCooker *CreateCooker(Cooker type, RaceCooker race, bool colorOfClothes, bool wearingGlasses);
};

typedef ActionOfCooker * CookerPtr;

class Mouse: public ActionOfCooker
{
private:
    bool VacSleep;
    bool Cooking;
    string Sex;
    string Post;
public:
    int Skill;
    Mouse(Cooker type, RaceCooker race, bool colorOfClothes, bool wearingGlasses): ActionOfCooker() {Type=type; Race = race; ColorOfClothes = colorOfClothes; WearingGlasses = wearingGlasses;}
    Mouse();
    virtual ~Mouse() {};
    void CookON() {wcout << L"Ушел готовить пасту" << endl; Cooking = true;} // готовит пасту
    void CookOff() {}; // не готовит пасту
    void Dism() {wcout << L"Нашли таракана. Увольняют..." << endl; Skill = 0;} // таракан
    void VacON() {wcout << L"Ушел в отсып" << endl; Skill -=20; VacSleep = true;} // отправка в отпуск на отсыпание
    void VacOff() {wcout << L"Выспался и пришел на работу!" << endl; VacSleep = false;} // возврат из отпуска
    Cooker GetCooker() const {return Cooker::Mouse;} // определение типа повара
};

class Cat: public ActionOfCooker
{
private:
    bool VacKan;
    bool Cooking;
    string Sex;
    string Post;
public:
    int Skill;
    Cat(Cooker type, RaceCooker race, bool colorOfClothes, bool wearingGlasses): ActionOfCooker() {Type=type; Race = race; ColorOfClothes = colorOfClothes; WearingGlasses = wearingGlasses;}
    Cat();
    virtual ~Cat() {};
    void CookON() {wcout << L"Ушел готовить суши" << endl; Cooking = true;} // готовит суши
    void CookOff() {}; // не готовит суши
    void Dism() {wcout << L"Застали за курением. Увольняют..." << endl; Skill = 0;} // курение
    void VacON() {wcout << L"Улетел на Канары!" << endl; Skill -=20; VacKan = true;} // отправка в отпуск на Канары
    void VacOff() {wcout << L"Вернулся с Канар..." << endl; VacKan = false;} // возврат из отпуска
    Cooker GetCooker() const {return Cooker::Cat;}
};

class Robot: public ActionOfCooker
{
private:
    bool VacFam;
    bool Cooking;
    string Sex;
    string Post;
public:
    int Skill;
    Robot(Cooker type, RaceCooker race, bool colorOfClothes, bool wearingGlasses): ActionOfCooker() {Type=type; Race = race; ColorOfClothes = colorOfClothes; WearingGlasses = wearingGlasses;}
    Robot();
    virtual ~Robot() {};
    void CookON() {wcout << L"Ушел готовить десерт" << endl; Cooking = true;} // готовит карамель
    void CookOff() {}; // не готовит карамель
    void Dism() {wcout << L"Застали за взломом пентагона. Увольняют..." << endl; Skill = 0;} // взломал базу Пентагона
    void VacON() {wcout << L"На отпуск к семье!" << endl; Skill -=20; VacFam = true;} // отправка на отпуск к семье
    void VacOff() {wcout << L"Вернулся из отпуска!" << endl; VacFam = false;} // возврат из отпуска
    Cooker GetCooker() const {return Cooker::Robot;}
};

class WheelchairUser: public ActionOfCooker
{
private:
    bool VacKuba;
    bool Cooking;
    string Sex;
    string Post;
public:
    int Skill;
    WheelchairUser(Cooker type, RaceCooker race, bool colorOfClothes, bool wearingGlasses): ActionOfCooker() {Type=type; Race = race; ColorOfClothes = colorOfClothes; WearingGlasses = wearingGlasses;}
    WheelchairUser();
    virtual ~WheelchairUser() {};
    void CookON() {wcout << L"Ушла готовить котлету" << endl; Cooking = true;} // готовит котлету
    void CookOff() {}; // не готовит котлету
    void Dism() {wcout << L"Спалила кухню. Увольняют..." << endl; Skill = 0;} // спалил кухню
    void VacON() {wcout << L"На Кубу!" << endl; Skill -=20; VacKuba = true;} // отправка на Кубу
    void VacOff() {wcout << L"Вернулась из отпуска..." << endl; VacKuba = false;} // возврат из отпуска
    Cooker GetCooker() const {return Cooker::WheelchairUser;} //тип повара: колясочник
};

class FirstContIterator : public Iterator<CookerPtr> // итератор для первого контейнера
{
private:
    const CookerPtr *CookerBox;
    int Position;
    int Count;

public:
    FirstContIterator(const CookerPtr *cookerBox, int count)
    {
        CookerBox = cookerBox;
        Count = count;
        Position = 0;
    }

    void First() { Position = 0; }
    void Next() { Position++; }
    bool IsDone() const { return Position >= Count; }
    CookerPtr CurrentItem() const { return CookerBox[Position]; }
};

class SecondContIterator : public Iterator<CookerPtr> // итератор для второго контейнера
{
private:
    const list<CookerPtr> *CookerBox;
    list<CookerPtr>::const_iterator iter; //тот итератор, который не может изменить содержимое списка

public:
    SecondContIterator(const list<CookerPtr> *cookerBox)
    {
        CookerBox = cookerBox;
        iter = CookerBox->begin();
    }

    void First() { iter = CookerBox->begin(); }
    void Next() { iter++; }
    bool IsDone() const { iter == CookerBox->end(); }
    CookerPtr CurrentItem() const {  return *iter; }
};

class ThirdContIterator : public Iterator<CookerPtr>
{
private:
	sqlite3 *CookerBox;
	int Position = 1;
public:
	ThirdContIterator(sqlite3 *cookerBox)
	{
	    CookerBox = cookerBox;
	}
	void First() { Position = 1; }
	void Next() { Position++; }
	bool IsDone() const;
	CookerPtr CurrentItem() const;
};

class CookerContainer : public BaseContainer<CookerPtr>
{
private:
    CookerPtr *CookerBox;
    int CookerCount;
    int MaxSize;
public:
    CookerContainer(int maxSize);
    virtual ~CookerContainer();
    void AddItem(const CookerPtr &item) {AddCooker(item);}
    void AddCooker (CookerPtr newCooker);
    int GetCount() const {return CookerCount;}
    CookerPtr GetByIndex(int index) const {return CookerBox[index];}

    Iterator<CookerPtr> *GetIterator() // использование итератора
    {
        return new FirstContIterator(CookerBox, CookerCount);
    }

};

class CookerContainerV2 : public BaseContainer<CookerPtr> // контейнер номер 2
{
private:
    list<CookerPtr> CookerBox;

public:
    void AddCooker(CookerPtr newCooker) {CookerBox.push_back(newCooker);}
    void AddItem(const CookerPtr &item) {AddCooker(item);}
    int GetCount() const {return CookerBox.size();}

    Iterator<CookerPtr> *GetIterator()
    {
        return new SecondContIterator(&CookerBox);
    }
};

class CookerBD : public BaseContainer<CookerPtr>
{
private:
	sqlite3 *CookerBox;

public:
	void AddCooker(CookerPtr newCooker);
	void AddItem(const CookerPtr &item) {AddCooker(item);}
	int GetCount() const;
	CookerBD();
	virtual ~CookerBD();

	Iterator<CookerPtr>* GetIterator()
	{
		return new ThirdContIterator(CookerBox);
	};
};

class FirstDecorator : public Decorator <CookerPtr>
{
private:
    bool Glasses; // носит ли повар очки
public:
    FirstDecorator(Iterator<CookerPtr> *iter, bool glasses): Decorator(iter) { Glasses = glasses;}

    void First()
    {
        Iter->First();
        while (!Iter->IsDone() && Iter->CurrentItem()->WearGlasses() != Glasses)
        {
            Iter->Next();
        }
    }

    void Next()
    {
        do
        {
            Iter->Next();
        } while (!Iter->IsDone() && Iter->CurrentItem()->WearGlasses() != Glasses);
    }
};

class SecondDecorator : public Decorator <CookerPtr>
{
private:
    bool Clothes; // цвет фартука у повара
public:
    SecondDecorator(Iterator<CookerPtr> *iter, bool clothes): Decorator(iter) { Clothes = clothes;}

    void First()
    {
        Iter->First();
        while (!Iter->IsDone() && Iter->CurrentItem()->ColClothes() != Clothes)
        {
            Iter->Next();
        }
    }

    void Next()
    {
        do
        {
            Iter->Next();
        } while (!Iter->IsDone() && Iter->CurrentItem()->ColClothes() != Clothes);
    }
};

class ThirdDecorator : public Decorator <CookerPtr>
{
private:
    RaceCooker DesiredRace; // какой расы повар
public:
    ThirdDecorator(Iterator<CookerPtr> *iter, RaceCooker desiredRace): Decorator(iter) { DesiredRace = desiredRace;}

    void First()
    {
        Iter->First();
        while (!Iter->IsDone() && Iter->CurrentItem()->GetRace() != DesiredRace)
        {
            Iter->Next();
        }
    }

    void Next()
    {
        do
        {
            Iter->Next();
        } while (!Iter->IsDone() && Iter->CurrentItem()->GetRace() != DesiredRace);
    }
};

#endif // PovaraH
