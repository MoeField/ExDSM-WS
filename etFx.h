#pragma once

#ifndef ET_FX
#define ET_FX 

#include <sstream>
#include <iomanip>
#include <iostream>

#include <functional>
#include <random>

#include <chrono>
#include <time.h> 
using namespace std;

extern std::string create_uuid();
extern std::string combine(const char[], const char[]);
extern int checkPwd(string& , int);

extern string getRT();
extern string _getRT();

#endif