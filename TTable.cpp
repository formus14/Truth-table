#include <iostream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <string>
using namespace std;

// Number of factors
unsigned long const n = 14;
unsigned long const nBits = 1 << n;

// Number of avilable loads
double loads[n] = { 1,2,3,0.05,1,2,3,0.5,1,2,3,3,1,2 };
double Rtot[nBits] = { 0 };
string s[nBits] = { "" };
int powerOf2 = 1;
int bit;

int BB;
double R;
int index;

fstream txt;

void print_table() {

	int arr[nBits][n];

	// Printing the truth table in the array
	for (int i = 0; i < n; ++i) // n
	{
		for (int bitNum = 0; bitNum < nBits; ++bitNum) // 2^n
		{
			bit = 1 - bitNum / powerOf2 % 2;
			arr[bitNum][i] = bit;
		}
		powerOf2 *= 2;
	}

	// *****_____*****_____*****______*****_____


	for (int j = 0; j < nBits; ++j)// 2^n
	{
		for (int i = 0; i < n; ++i) // n
		{
			BB = arr[j][i];
			s[j] += " " + std::to_string(BB);
			//cout << arr[j][i] << ' ';
			//txt << arr[j][i] << ' ';

			R = loads[i];
			Rtot[j] += (BB / R);

			if (i == n - 1) {
				Rtot[j] = 1 / Rtot[j];
				//cout << " = " << Rtot[j] << ' ';
				//txt << " = " << Rtot[j] << ' ' << endl;

			}
		}

		cout << endl;
	}

	std::vector<double> myvector1(Rtot, Rtot + nBits);
	std::vector<double> myvector2(Rtot, Rtot + nBits);

	std::sort(myvector1.begin(), myvector1.end());
	std::vector<double>::iterator it2 = myvector2.begin();

	for (std::vector<double>::iterator it1 = myvector1.begin(); it1 != myvector1.end(); ++it1) {
		// printing sorted Rtot
		std::cout << ' ' << *it1<<' ';
		txt <<' ' << *it1 << ' ';
		it2 = std::find(myvector2.begin(), myvector2.end(), *it1);
		if (it2 != myvector2.end()) {
			index = it2 - myvector2.begin();
			std::cout << s[index] << '\n';
			txt << s[index] << '\n';
		}
	}

}

int main()
{
	cout << "R_Load      1,2,3,0.05,1,2,3,0.5,1,2,3,3,1,2\n";
	cout << "____________________________________________ \n";

	txt.open("test.txt", std::fstream::in | std::fstream::out | std::ofstream::trunc);// std::fstream::app);

	if (txt.is_open())
	{
		txt << "R_Load      1,2,3,0.05,1,2,3,0.5,1,2,3,3,1,2\n";
		txt << "____________________________________________\n";

		print_table();
		txt.close();
	}
	else
	{
		std::cout << "Error opening file";
	}


}
