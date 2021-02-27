// wk3Sequence.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Carter Welke CIST004B Spring 2020

#include <iostream>

int mainTest();
int mainExam();

int main()
{
    std::cout << "Carter Welke CIST 4B Spring 2020\n\n";
    //gives user choice of running sequencetest or sequenceexam
    int choice;
    std::cout << "Test or Exam?(0 for test/1 for exam): ";
    std::cin >> choice;
    if (choice == 0)
        mainTest();
    else
        mainExam();

    return 0;
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
