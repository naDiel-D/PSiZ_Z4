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

void closeLog(void) // Zamknij log
{
    saveLog("Zamknieto plik z logami.");
    logPlik.close();
}

void createFile(const string fileName, const int counter, const char values) // Stworzenie pliku + zmiana 10 bitów dla drugiego testu
{
    srand(time(NULL));
    ifstream myFile;

    const char diffCharacter = 0x35;
    int lM[10] = {};
    bool kk = false;
    int temp = {};
    int k = 0;

    myFile.open(fileName);
    if (myFile)
    {
        saveLog("Ten plik " + fileName + " juz istnieje!\n");
    }
    else {

        ofstream aFile(fileName);

        if (fileName == "t2_plik4.bin") // Zamiana 10 bitow dla pliku 4 dla drugiego testu
        {
            for (size_t i = 0; i < 10; i++)
            {
                do
                {
                    temp = rand() % counter + 1;
                    for (size_t j = 0; j < 10; j++)
                    {
                        if (temp == lM[j]) {
                            kk = true;
                        }
                        else kk = false;
                    }

                } while (kk);
                lM[i] = temp;
            }
            sort(lM, lM + 10);

            for (size_t i = 0; i < 10; i++)
            {
                cout << lM[i] << ", ";
            }

            for (size_t i = 0; i < 11; i++)
            {
                if (i < 10) {
                    for (k; k < lM[i]; k++)
                    {
                        aFile << values;
                    }

                    aFile << diffCharacter;
                    k++;
                }
                else {
                    for (k; k < counter; k++)
                    {
                        aFile << values;
                    }
                }
            }
        }
        else
        {
            for (size_t i = 0; i < counter; i++)
            {
                aFile << values;
            }
        }

        string log = "Plik: " + fileName + " zostal stworzony\n";

        saveLog(log);
        system("cls");

    }

}

struct resultsBER // Struct dla BER
{
    clock_t czas1;
    clock_t czas2;
    float BER;
    double bledy;
    double ilosc;
};