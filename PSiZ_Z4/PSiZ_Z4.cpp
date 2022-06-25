/* Daniel Flis

    PSiZ_Z4 */

#pragma warning(disable : 4996)
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

fstream logPlik;

void saveLog(string msg) // Zapisz info o logu
{
    string t;
    time_t currentTime = time(NULL);
    string txttime = (string)asctime(localtime(&currentTime));
    txttime = txttime.substr(0, txttime.length() - 1);
    t = (string)"T: " + txttime + " M: " + msg + "\n";
    logPlik << t.c_str();
    logPlik.flush();
    cout << t.c_str();
    cout.flush();
}

void openLog(string fileName) // Otworz log
{
    logPlik.open(fileName.c_str(), ios_base::app);
    if (!logPlik.good() == true)
    {
        cout << "Nie mozna otworzyc logow." << endl;
    }
    saveLog("Plik z logami otwoarto.");
}