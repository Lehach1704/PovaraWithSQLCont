#include <string>
#include <iostream>

using namespace std;

#include "povara.h"
#include "Patterns.h"
#include "sqlite3.h"

CookerBD::CookerBD()
{
    sqlite3 *CookerPtr;
    int openBD = sqlite3_open("Povara.db", &CookerPtr);
    if (openBD != SQLITE_OK)
    {
        wcout << L"Open error in const" << endl;
    }
    else
    {
        wcout << L"Open success in const" << endl;
    }

    char *errmsg;
    int createBD = sqlite3_exec(CookerPtr, "DROP TABLE IF EXISTS povara;"
                                           "CREATE TABLE povara ("
                                           "Cooker INTEGER NOT NULL,"
                                           "Race INTEGER NOT NULL,"
                                           "ColorClothes INTEGER NOT NULL,"
                                           "Glasses INTEGER NOT NULL);",
                                           NULL, NULL, &errmsg);

    if (createBD != SQLITE_OK)
    {
        wcout << L"Error on create DB" << endl;
    }

}

CookerBD::~CookerBD()
{
    sqlite3 *CookerPtr;
    int openBD = sqlite3_open("Povara.db", &CookerPtr);
    /*if (openBD != SQLITE_OK)
    {
        wcout << L"Error in destr" << endl;
    }
    else
    {
        wcout << L"Success in destr" << endl;
    }*/

    sqlite3_close(CookerPtr);
}

void CookerBD::AddCooker(CookerPtr newCooker)
{
    sqlite3 *CookerPtr;
    int openBD = sqlite3_open("Povara.db", &CookerPtr);
    /*if (openBD != SQLITE_OK)
    {
        wcout << L"Open error in create" << endl;
    }
    else
    {
        wcout << L"Open success in create" << endl;
    }*/

    char *errmsg;
    string reqest = "INSERT INTO povara (Cooker, Race, ColorClothes, Glasses) VALUES ('" + to_string(static_cast <int> (newCooker->GetCooker())) + "', '" + to_string(static_cast <int>(newCooker->GetRace())) + "', '" + to_string(static_cast <bool> (newCooker->ColClothes())) + "', '" + to_string(static_cast <bool> (newCooker->WearGlasses())) + "');";
    int addCooker = sqlite3_exec(CookerPtr, reqest.c_str(), NULL, NULL, &errmsg);
}

int CookerBD::GetCount() const
{
    sqlite3 *CookerPtr;
    int openBD = sqlite3_open("Povara.db", &CookerPtr);
    /*if (openBD != SQLITE_OK)
    {
        wcout << L"Open error in count" << endl;
    }
    else
    {
        wcout << L"Open success in count" << endl;
    }*/

    int schet = 0;
    sqlite3_stmt *forschet;
    string rec = "SELECT COUNT (*) FROM povara;";
    int forgetCount = sqlite3_prepare_v2(CookerPtr, rec.c_str(), -1, &forschet, NULL);

    int countget = sqlite3_step(forschet);
    if (countget == SQLITE_ROW)
    {
        schet = sqlite3_column_int64(forschet, 0);
    }
    sqlite3_finalize(forschet);
}

bool ThirdContIterator::IsDone() const
{
    sqlite3 *CookerPtr;
    int openBD = sqlite3_open("Povara.db", &CookerPtr);
    /*if (openBD != SQLITE_OK)
    {
        wcout << L"Open error in Done" << endl;
    }
    else
    {
        wcout << L"Open success in Done" << endl;
    }*/

    sqlite3_stmt *forschet;
    string rec = "SELECT COUNT (*) FROM povara;";
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
    /*if (openBD != SQLITE_OK)
    {
        wcout << L"Open error in CItem" << endl;
    }
    else
    {
        wcout << L"Open success in CItem" << endl;
    }*/

    sqlite3_stmt *forschet1;
    string rc = "SELECT povara.Cooker, povara.Race, povara.ColorClothes, povara.Glasses, rowid FROM povara WHERE rowid =" + to_string(Position) + ";";
    int forgetCount = sqlite3_prepare_v2(CookerPtr, rc.c_str(), -1, &forschet1, NULL);
    /*if (forgetCount != SQLITE_OK)
    {
        wcout << L"Zapros na vivod" << endl;
        string err = sqlite3_errstr(forgetCount);
        cout << err << endl;
        const char* errmsg = sqlite3_errmsg(CookerPtr);
        wcout << errmsg << endl;
    }*/

    while(true)
	{

		int stepResult = sqlite3_step(forschet1);
        if (stepResult != SQLITE_ROW)
		{
		    wcout << L"end string" << endl;
		    //sqlite3_finalize(forschet1);
			break;
		}

		Cooker type = Cooker(sqlite3_column_int64(forschet1,0));
		RaceCooker race = RaceCooker(sqlite3_column_int64(forschet1,1));
		int colorOfClothes = sqlite3_column_int64(forschet1,2);
		int wearingGlasses = sqlite3_column_int64(forschet1,3);

		switch(type)
        {
            case Cooker::Mouse: return new Mouse(type, race, colorOfClothes, wearingGlasses);
            case Cooker::Cat: return new Cat(type, race, colorOfClothes, wearingGlasses);
            case Cooker::Robot: return new Robot(type,race, colorOfClothes, wearingGlasses);
            case Cooker::WheelchairUser: return new WheelchairUser(type, race, colorOfClothes, wearingGlasses);
            default: return NULL;
        }

		sqlite3_finalize(forschet1);
	}
}
