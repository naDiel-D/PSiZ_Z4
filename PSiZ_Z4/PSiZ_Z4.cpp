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
    double err;
    double qty;
};

uint8_t hammingDistance(uint8_t n1, uint8_t n2) // Obliczenie BER
{
    uint8_t x = n1 ^ n2;
    uint8_t setBits = 0;
    while (x > 0)
    {
        setBits += x & 1;
        x >>= 1;
    }
    return setBits;
}

resultsBER calculate(string path1, string path2) // Podanie scieżek dwóch plików i obliczenie BER pomiędzy nimi
{
    fstream f1, f2;
    resultsBER outcome;

    outcome.czas1 = 0;
    outcome.czas2 = 0;
    outcome.BER = 0;
    outcome.err = 0;
    outcome.qty = 0;

    f1.open(path1.c_str(), ios::binary | ios::in);
    f2.open(path2.c_str(), ios::binary | ios::in);
    char a = 0x00;
    char b = 0x00;
    outcome.czas1 = clock();

    while (!f1.eof())
    {
        f1 >> a;
        f2 >> b;
        if (!f1.eof())
        {
            outcome.err += hammingDistance(a, b);
            outcome.qty += 8;
        }
    }
    outcome.BER = (float)outcome.err / outcome.qty;
    outcome.czas2 = clock();
    return outcome;
}

void displayResults(resultsBER outcome) // WYciągnięcie wyników ze struct BER
{
    stringstream wiad;
    wiad << "Program wykonal obliczenia z tymi wynikami: " << endl;
    wiad << "Bit Error Rate: " << outcome.BER << endl;
    wiad << "Ilosc bitow: " << outcome.qty << endl;
    wiad << "Ilosc bledow: " << outcome.err << endl;
    wiad << "Czas obliczen: " << ((float)outcome.czas2 - outcome.czas1) / CLOCKS_PER_SEC << " sec " << endl;
    saveLog(wiad.str());
}

int main(int argc, char* argv[])
{
    string path1;
    string path2;
    resultsBER outcome;

    openLog("log.txt");

    if (argc != 3)
    {
        char wybor;
        while (true) // Definicja menu
        {
            cout << " Wcisnij cyfre aby okreslic nastepny krok: " << endl << endl
                << " 1: Oblicz BER podajac sciezki plikow utworzonych przez Ciebie." << endl
                << " 2: Wykonaj test 1 z zadania IV. " << endl
                << " 3: Wykonaj test 2 z zadania IV. " << endl
                << " 4: Wykonaj test 3 z zadania IV. " << endl
                << " 0: Nie, nie chce mi sie! " << endl << endl;

            wybor = _getch();

            switch (wybor)
            {
            case '1':
            {
                cout << " Podaj sciezke do 1ego pliku: ";
                cin >> path1;
                cout << " Podaj sciezke do 2go pliku: ";
                cin >> path2;

                saveLog("Obliczanie danych dla podanych plikow.");
                outcome = calculate(path1, path2);
                displayResults(outcome);
            }
            break;

            case '2':
            {
                // Test numer 1
                createFile("t1_plik1.bin", 100, 0x55);
                createFile("t1_plik2.bin", 100, 0x55);
                saveLog("Obliczanie danych dla podanych plikow.");
                outcome = calculate("t1_plik1.bin", "t1_plik2.bin");
                displayResults(outcome);
            }
            break;

            case '3':
            {
                // Test numer 2
                createFile("t2_plik3.bin", 100, 0x55);
                createFile("t2_plik4.bin", 100, 0x55);
                saveLog("Obliczanie danych dla podanych plikow.");
                outcome = calculate("t2_plik3.bin", "t2_plik4.bin");
                displayResults(outcome);
            }
            break;

            case '4':
            {
                // Test numer 3
                createFile("t3_plik5.bin", 419430400, 0x55);
                createFile("t3_plik6.bin", 419430400, 0x50);
                saveLog("Obliczanie danych dla podanych plikow.");
                outcome = calculate("t3_plik5.bin", "t3_plik6.bin");
                displayResults(outcome);
            }
            break;

            case '0':
                closeLog();
                exit(0);
                break;

            default: cout << "Wybrales niemozliwa opcje. Sprawdz czy jestes w dobrym Multiversie." << endl;
            }
            cout << endl << endl;
            cout << "Cokolwiek wcisniesz - wyladujesz na powrot w menu glownym" << endl;
            _getch();
            system("cls");
        }
    }
    else
    {
        path1 = argv[1];
        path2 = argv[2];

        saveLog("Obliczanie danych dla podanych plikow.");
        outcome = calculate(path1, path2);
        displayResults(outcome);
        closeLog();
        return 0;
    }
}