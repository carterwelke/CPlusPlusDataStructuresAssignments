// MinMaxMeanMedianMode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Carter Welke CIST 004B Spring 2020

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

bool myLess(int i, int j) { return i < j; }

int main() {
    cout << "Carter Welke\t\tCIST 004B Spring 2020\n";
	cout << "Min Max Mean Median Mode Calculator with multimodal support" << endl;

	int numInputs;
	do {
		cout << "How many numbers are in your list?(1-100): ";
		cin >> numInputs;
		if (numInputs < 1 || numInputs > 100)
			cout << "Dude, please enter a valid list count" << endl;
	} while (numInputs < 1 || numInputs > 100);

	cout << "\nYour list may have numbers between 1 and 1000.\n";
	
	vector<int> inputVect(numInputs);

	int inputNum = 0;	
	int min,max,median;
	double mean;
	int sum = 0;

	for (int i = 1; i <= numInputs; ++i) {
		do {
			cout << "Enter the " << setw(2) << i;
			
			if (i < 14 && i > 10)
			{
				cout << "th ";
			}
			else 
			{
				switch (i % 10) {
				case 1:
					cout << "st ";
					break;
				case 2:
					cout << "nd ";
					break;
				case 3:
					cout << "rd ";
					break;
				default:
					cout << "th ";
					break;
				}
			}
			cout << "number: ";
			cin >> inputNum;
			if (inputNum < 1 || inputNum > 1000)
				cout << "come on man, please enter a valid number" << endl;
		} while (inputNum < 1 || inputNum > 1000);
		inputVect[i-1] = inputNum;
		sum += inputNum;
	}
	
	sort(inputVect.begin(), inputVect.end(), myLess);

	min = inputVect.front();
	max = inputVect.back();
	mean = static_cast<double>(sum) / numInputs;
	median = inputVect[(numInputs) / 2];

	vector<int> instVect(max+1);
	vector<int> modeVect;
	int maxInst = 0;

	for (auto num : inputVect) {
		++instVect.at(num);
		if (maxInst < instVect.at(num))
			maxInst = instVect.at(num);
	}

	for (int index = 0; index < instVect.size(); ++index)
		if (maxInst == instVect.at(index))
			modeVect.emplace_back(index);

	cout << "\nThe list of numbers has the following characteristics:\n";
	cout << setw(16) << "The Minimum is: " << min << endl
		 << setw(16) << "The Maximum is: " << max << endl
		<< setw(16) << "The Mean is: " << mean << endl
		<< setw(16) << "The Median is: " << median << endl;

	if (modeVect.size() > 1)
	{
		cout << "The list is multimodal. The list has " << modeVect.size() << " modes." << endl;
		cout << "The modes are: ";

		for (int i = 0; i < modeVect.size(); ++i)
		{
			switch (modeVect.size() - i) {
			case 1:
				cout << modeVect.at(i);
				break;
			case 2:
				cout << modeVect.at(i) << " and ";
				break;
			default:
				cout << modeVect.at(i) << ", ";
				break;
			}
		}
	}
	else
	{
		cout << setw(16) << "The Mode is: " << modeVect.front() << endl;
	}
	cout << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
