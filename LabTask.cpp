#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

void checkValidInput() 
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
void checkValidContInput()
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw "Incorrect input, entered value must be a number";
    }
}
void checkParams(int n) 
{
    if (n <= 1)
        throw "Incorrect input, n must be > 1";
}

double calculate(double& x, int n) 
{
    double y = 0;
    if (x >= 0)
    {
        for (int i = 0; i <= n; i++)
        {
            double a = 1;
            for (int j = 1; j < n + 2; j++)
            {
                a *= (9 * i - j + (j * j * j)) * (9 * i - j + (j * j * j));
            }
            y += a;
        }
    }
    else
    {
        for (int i = 3; i < n + 3; i++)
        {
            y += 1.0 / (2 * i) + 1.0 / x;
        }
        y *= (x + 3);
    }
    cout << "x = " << x << " y = " << y << endl;
    return y;
}


int main()
{
    int loop = 1;
    int readfile = 0;
    int writefile = 0;
    int n = 0;
    double x = 0;
    double xMax = 0;
    double step = 0;
    double y = 0;
    cout << "WARNING! WHEN INPUTING DATA DO NOT USE SPACES, CHARACTERS OR COMMAS! THIS CAN LEAD TO INCORRECT RESULTS \n" << endl;
    while (loop == 1)
    {
        ofstream outFile;
        cout << "Do you want to read data from file? (enter 1 if yes)" << "\n" << "If you saved invalid data in the file the results may be incorrect" << endl;
        cin >> readfile;
        checkValidInput();
        cout << "Do you want to save data to file? (enter 1 if yes)" << "\n" << "Don't worry, previous results will not be deleted" << endl;
        cin >> writefile;
        checkValidInput();

        if (readfile != 1)
        {
            while (true) 
            {
                try 
                {
                    cout << "\nEnter n (must be a natural number) \nif you input a non natural number it will be rounded down! \nn must be > 1" << endl;
                    cin >> n;
                    checkValidContInput();
                    checkParams(n);
                }
                catch (const char* msg)
                {
                    cout << msg << endl;
                    continue;
                }
                break;
            }
            while (true) 
            {
                try
                {
                    cout << "Enter starting x (must be a number)" << endl;
                    cin >> x;
                    checkValidContInput();
                }
                catch (const char* msg)
                {
                    cout << msg << endl;
                    continue;
                }
                break;
            }
            while (true) {
                try
                {
                    cout << "Enter maximum x (must be a number, must be >= x)" << endl;
                    cin >> xMax;
                    checkValidContInput();
                }
                catch (const char* msg)
                {
                    cout << msg << endl;
                    continue;
                }
                if (xMax < x) 
                {
                    cout << "You entered an invalid value, maximum x must be bigger or equal to x" << endl;
                    continue;
                }
                break;
            }     
            while (true) {
                try
                {
                    cout << "Enter step (must be a number, must be > 0)" << endl;
                    cin >> step;
                    checkValidContInput();
                }
                catch (const char* msg)
                {
                    cout << msg << endl;
                    continue;
                }
                if (step <= 0) 
                {
                    cout << "You entered an invalid value, step must be bigger than 0" << endl;
                    continue;
                }
                break;
            }
        }
        else 
        {
            ifstream Nfile("N.txt");
            ifstream Xfile("X.txt");
            ifstream XMfile("XMax.txt");
            ifstream Sfile("Step.txt");
            if (!(Nfile && Xfile && XMfile && Sfile)) 
            {
                cout << "Create the file before trying to open it";
                return 1;  
            }
            Xfile >> x;
            Nfile >> n;
            XMfile >> xMax;
            Sfile >> step;
            cout << "Range: from " << x << " to " << xMax << "\nstep: " << step << "\nn: " << n << endl;
        }
        if (writefile == 1) 
            outFile.open("result.txt", ios::app);
        cout << "The results are: " << endl;
        while (x <= xMax) 
        {
            y = calculate(x, n);
            if (writefile == 1) 
                outFile << "x = " << x << " y = " << y << endl;
            y = 0;
            x += step;
        }
        outFile.close();
        cout << "Do you want to enter other values? (enter 1 if yes)" << endl;
        cin >> loop;
        checkValidInput();
    }
    return 0;
}
