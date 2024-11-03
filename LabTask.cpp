#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

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
    while (loop == 1)
    {
        ofstream outFile;
        cout << "WARNING! WHEN INPUTING DATA DO NOT USE SPACES OR COMMAS! THIS CAN LEAD TO INCORRECT RESULTS \n" << endl;
        cout << "Do you want to read data from file? (enter 1 if yes)" << "\n" << "If you saved invalid data in the file the results may be incorrect" << endl;
        if (!(cin >> readfile)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Do you want to save data to file? (enter 1 if yes)" << "\n" << "Don't worry, previous results will not be deleted" << endl;
        if (!(cin >> writefile)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (readfile != 1)
        {
            cout << "Enter n (must be a natural number)" << "\n" << "if you input a non natural number it will be rounded down!" << "\n" << "n must be > 1" << endl;
            while (true) {
                if (!(cin >> n)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "You entered an invalid value, it must be a natural number" << "\n" << "if you input a non natural number it will be rounded down!" << "\n" << "n must be > 1" << endl;
                    continue;
                }
                if (n <= 1) {
                    cout << "n must be bigger than 1" << endl;
                    continue;
                }
                break;
            }
            cout << "Enter starting x (must be a number)" << endl;
            while (true) {
                if (!(cin >> x)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "You entered an invalid value, it must be a number" << endl;
                    continue;
                }
                break;
            }
            cout << "Enter maximum x (must be a number)" << endl;
            while (true) {
                if (!(cin >> xMax)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "You entered an invalid value, it must be a number" << endl;
                    continue;
                }
                if (xMax < x) {
                    cout << "You entered an invalid value, maximum x must be bigger or equal to x" << endl;
                    continue;
                }
                break;
            }
            cout << "Enter step (must be a number, must be > 0)" << endl;
            while (true) {
                if (!(cin >> step)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "You entered an invalid value, it must be a number" << endl;
                    continue;
                }
                if (step <= 0) {
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
            if (!(Nfile && Xfile && XMfile && Sfile)) {
                cout << "Create the file before trying to open it";
                return 1;  
            }
            Xfile >> x;
            Nfile >> n;
            XMfile >> xMax;
            Sfile >> step;
            cout << "Range: from " << x << " to " << xMax << "\nstep: " << step << "\nn: " << n << endl;
        }


        cout << "The results are: " << endl;
        if (writefile == 1) {
            outFile.open("result.txt", ios::app);
        }

        while (x <= xMax) {
            if (x >= 0)
            {
                for (int i = 0; i <= n; i++)
                {
                    double a = 1;
                    for (int j = 1; j < n + 2; j++)
                    {
                        a *= (9 * i - j + (j*j*j))*(9 * i - j + (j*j*j));
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
            if (writefile == 1) {
                outFile << "x = " << x << " y = " << y << endl;
            }

            y = 0;
            x += step;
        }
        outFile.close();

        cout << "Do you want to enter other values? (enter 1 if yes)" << endl;
        if (!(cin >> loop)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return 0;
/*I added this comment with an asci picture of a cat to demonstrate modification of a file
      /\_/\
 /\  / o o \
//\\ \~(*)~/
`  \/   ^ /
   | \|| ||
   \ '|| ||
    \)()-())
*/
}
