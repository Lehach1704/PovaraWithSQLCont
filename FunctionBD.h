#include <string>
#include <iostream>

using namespace std;

#include "povara.h"
#include "sqlite3.h"

CookerBD::CookerBD()
{
    sqlite3 *CookerPtr;
    int openBD = sqlite3_open("Povara.db", &CookerPtr);
    if (openBD != SQLITE_OK)
    {
        wcout << L"Open error" << endl;
    }
    else
    {
        wcout << L"Open success" << endl;
    }
    char *errmsg;
    int createBD = sqlite3_exec(CookerPtr, "CREATE TABLE povara (" // создаем таблицу
                                           "Cooker TEXT NOT NULL, "
                                           "skill INTEGER NOT NULL,"
                                           "Race TEXT NOT NULL, "
                                           "ColorClothes TEXT NOT NULL, "
                                           "Glasses BOOLEAN NOT NULL,", NULL, NULL, &errmsg);
    if (createBD != SQLITE_OK)
    {
        wcout << L"Open error" << endl;
    }

}

// написать деструктор но пока хз как

void CookerBD::AddCooker(CookerPtr newCooker)
{
    sqlite3 *CookerPtr;
    int openBD = sqlite3_open("Povara.db", &CookerPtr);
    if (openBD != SQLITE_OK)
    {
        wcout << L"Open error" << endl;
    }
    else
    {
        wcout << L"Open success" << endl;
    }
    char *errmsg;
    string reqest = "INSERT INTO povara (Cooker, skill, Race, ColorClothes, Glasses) VALUES ('" + to_string(static_cast <int> (newCooker->GetCooker())) + "', '" + to_string(newCooker->Skill) + "', '" + to_string(static_cast <int>(newCooker->GetRace())) + "', '" + to_string(newCooker->ColClothes()) + "', '" + to_string(newCooker->WearGlasses()) + "');";
    int addCooker = sqlite3_exec(CookerPtr, reqest.c_str(), NULL, NULL, &errmsg);
}

int CookerBD::GetCount() const
{
    sqlite3 *CookerPtr;
    int openBD = sqlite3_open("Povara.db", &CookerPtr);
    if (openBD != SQLITE_OK)
    {
        wcout << L"Open error" << endl;
    }
    else
    {
        wcout << L"Open success" << endl;
    }

    //int schet = 0;
    sqlite3_stmt *forschet;
    string rec = "SELECT COUNT (*) FROM povara";
    int forgetCount = sqlite3_prepare_v2(CookerPtr, rec.c_str(), -1, &forschet, NULL);

    /*int countget = sqlite3_step(forschet);
    if (countget == SQLITE_ROW)
    {
        schet = sqlite3_column_int64(forschet, 0);
    }*/
    sqlite3_finalize(forschet);
}

bool ThirdContIterator::IsDone() const
{
    sqlite3 *CookerPtr;
    int openBD = sqlite3_open("Povara.db", &CookerPtr);
    if (openBD != SQLITE_OK)
    {
        wcout << L"Open error" << endl;
    }
    else
    {
        wcout << L"Open success" << endl;
    }

    sqlite3_stmt *forschet;
    string rec = "SELECT COUNT (*) FROM povara";
    int forgetCount = sqlite3_prepare_v2(CookerPtr, rec.c_str(), -1, &forschet, NULL);

    int schet = 0;
    int countget = sqlite3_step(forschet);
    if (countget == SQLITE_ROW)
    {
        schet = sqlite3_column_int64(forschet, 0);
    }
    return Position == schet;
}

CookerPtr ThirdContIterator::CurrentItem() const
{
    sqlite3 *CookerPtr;
    int openBD = sqlite3_open("Povara.db", &CookerPtr);
    if (openBD != SQLITE_OK)
    {
        wcout << L"Open error" << endl;
    }
    else
    {
        wcout << L"Open success" << endl;
    }

    sqlite3_stmt *forschet1;
    string rc = "SELECT Cooker, skill, Race, ColorClothes, Glasses FROM povara WHERE ROWID = " + to_string(Position) + ");";
    int forgetCount = sqlite3_prepare_v2(CookerPtr, rc.c_str(), -1, &forschet1, NULL);

    while(true)
	{

		int stepResult = sqlite3_step(forschet1);
		if (stepResult != SQLITE_ROW)
		{
		    sqlite3_finalize(forschet1);
			break;
		}

		Cooker type = Cooker(sqlite3_column_int64(forschet1,0));
		int skill = sqlite3_column_int64(forschet1,1);
		RaceCooker race = RaceCooker(sqlite3_column_int64(forschet1,2));
		bool clothes = sqlite3_column_int64(forschet1,3);
		bool glasses = sqlite3_column_int64(forschet1,4);

		switch(type)
        {
            case Cooker::Mouse: return new Mouse;
            case Cooker::Cat: return new Cat;
            case Cooker::Robot: return new Robot;
            case Cooker::WheelchairUser: return new WheelchairUser;
            default: return NULL;
        }

		sqlite3_finalize(forschet1);
	}
}
