#include <iostream>
#include <fstream>		// for the txt file
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <string>
#include <stdlib.h>
#include <iomanip>      // just for std::setprecision
#include <sstream>
#include <map>

using namespace std;

// Number of factors
unsigned long long const n = 14;
unsigned long long const nBits = 1 << n;

// Number of avilable loads
float loads[n] = { 1,2,3,0.05,1,2,3,0.5,1,2,3,3,1,2 };
float Rtot[nBits] = { 0 };

string s[nBits] = { "" };	// for the truth table 0 and 1 
string print[nBits] = { "" };	 // for the loads values so its easier to read 
std::ostringstream stream; 

int powerOf2 = 1;
int bit;

int BB;
float R;
int index;

typedef map<float, float> floatmap;
floatmap mymap;

fstream txt;

// ****		Create 2 vectors ,one for a sorted Rtotal and the other is unsorted just to get an index to print the truth table with	***** //

std::vector<float> myvector1;
std::vector<float> myvector2;
std::vector<float> myvector3;
void Closest_value(float C);

void Init() {

	cout << "Enter a " << n << " load values \n";

	for (int i = 0; i < n; i++) {
		cout << "load " << i + 1 << " : ";
		cin >> loads[i];
	}
	
	txt << "R_Loads      ";
	for (int i = 0; i < n; i++) {
		txt << loads[i] << ",";
	}
	txt << "\n____________________________________________ \n";

	cout << "What Values are you searching for ? \n";
	float C;
	cin >> C;
	Closest_value(C);

}

void print_table() {

	int arr[nBits][n];

	// ****		Printing the truth table in the array	***** //
	for (int i = 0; i < n; ++i) // n
	{
		for (int bitNum = 0; bitNum < nBits; ++bitNum) // 2^n
		{
			bit = 1 - bitNum / powerOf2 % 2;
			arr[bitNum][i] = bit;
		}

		powerOf2 *= 2;
	}

	// ****		Saving the truth table in a string and while calculating Rtotal	***** //
	for (int j = 0; j < nBits; ++j)// 2^n
	{
		for (int i = 0; i < n; ++i) // n
		{
			BB = arr[j][i];
			s[j] += " " + std::to_string(BB);
			R = loads[i];
			Rtot[j] += (BB / R);
			
			if (BB == 1) {
			//print[j]+="" + setw(3)+std::to_string(loads[i])+"//";
				stream << std::setprecision(2) << R;
				string x = stream.str();
				print[j] += "" + x + "//";
				stream.str(std::string());
				stream.clear();
			}

			if (i == n - 1) {
				Rtot[j] = 1 / Rtot[j];
			}

		}

		cout << endl;
	}


	std::vector<float> myvector1(Rtot, Rtot + nBits);
	std::vector<float> myvector2(Rtot, Rtot + nBits);

	// ****		Sort vector 1 and set iterator on the second vector		***** //

	std::sort(myvector1.begin(), myvector1.end());
	std::vector<float>::iterator it2 = myvector2.begin();

	// ****		Remove duplicate of vector 1 ( the sorted one )		***** //

	auto last = std::unique(myvector1.begin(), myvector1.end());
	myvector1.erase(last, myvector1.end());

	for (std::vector<float>::iterator it1 = myvector1.begin(); it1 != myvector1.end(); ++it1) {
		
		// ****		printing sorted Rtot on cmd and the txt file		***** //
	
		//std::cout << ' ' << *it1<<' '<<"-> ";
		txt <<' ' << *it1 << ' ' << "-> ";
		
		// ****		set the iterator to search for the element of itrator 1 (the sorted vector) in the unsorted vecor and get me the index of the unsorted vector		***** //

		it2 = std::find(myvector2.begin(), myvector2.end(), *it1);
		if (it2 != myvector2.end()) {
			
			index = it2 - myvector2.begin();
			
			//std::cout << s[index] << '\n';
			//txt << s[index] << '\n';
						//std::cout << print[index] << '\n'<<endl;
						txt << print[index] << '\n'<<endl;
		}
	}
	//~myvector1();

}

void Closest_value(float C) {
	print_table();

	for (int j = 0; j < nBits; ++j)
		mymap.insert(make_pair(abs(Rtot[j] - C), Rtot[j]));
	
	float diff = mymap.begin()->first;
	float value = mymap.begin()->second;
	
	std::cout << "Difference to the required value : " << diff << "\n";
	std::cout << "Closest value:" << value <<" --> ";
	
	std::vector<float> myvector3(Rtot, Rtot + nBits);
	vector<float>::iterator it3 = myvector3.begin();
	it3 = std::find(myvector3.begin(), myvector3.end(), value);
	if (it3 != myvector3.end()) {
		int i = it3 - myvector3.begin();
		std::cout << print[i] << '\n' << endl;
	}

}

int main()
{
	txt.open("test.txt", std::fstream::in | std::fstream::out | std::ofstream::trunc);// std::fstream::app);

	if (txt.is_open())
	{
		Init();
		txt.close();
	}
	else
	{
		std::cout << "Error opening file";
	}

}
