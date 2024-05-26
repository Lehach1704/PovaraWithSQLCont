#include <iostream>

using namespace std;

#include "povara.h"

Mouse::Mouse()
{
    bool VacSleep = false;
    bool Cooking = false;
    int Skill = 100;
    string Sex = "Man";
    string Post = "Chef";
    Race = RaceCooker::Asian;
}

Cat::Cat()
{
    bool VacKan = false;
    bool Cooking = false;
    int Skill = 80;
    string Sex = "Man";
    string Post = "Assistant Chef";
    Race = RaceCooker::African;
}

Robot::Robot()
{
    bool VacFam = false;
    bool Cooking = false;
    int Skill = 50;
    string Sex = "Man";
    string Post = "Confectioner";
    Race = RaceCooker::European;
}

WheelchairUser::WheelchairUser()
{
    bool VacKuba = false;
    bool Cooking = false;
    int Skill = 30;
    string Sex = "Woman";
    string Post = "Kitchen boy";
    Race = RaceCooker::European;
}
