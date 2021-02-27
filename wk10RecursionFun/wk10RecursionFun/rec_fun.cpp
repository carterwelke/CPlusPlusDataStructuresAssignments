#include "rec_fun.h"
#include <cassert>
#include <chrono>
#include <iomanip>

//Carter Welke CIST 004A Spring 2020

using namespace std::chrono;

void displayDots(std::ostream& outs, unsigned int n) {
    for (unsigned int i = 0; i < n; ++i) {
        outs << "*";
    }
    outs << "\n";
    return;
}

// Precondition: m <= n
  // Postcondition: The function has printed a pattern of 2*(n-m+1) lines
  // to the output stream outs. The first line contains m asterisks, the next
  // line contains m+1 asterisks, and so on up to a line with n asterisks.
  // Then the pattern is repeated backwards, going n back down to m.
void triangle(std::ostream& outs, unsigned int m, unsigned int n)
{
	assert(m <= n);
    if (m == n) { 
        displayDots(outs,n);
        displayDots(outs,n);
        return; 
    }
    else {
        displayDots(outs, m);
        triangle(outs, m + 1, n);
        displayDots(outs, m);
    }
    
}

void numbers(std::ostream& outs, const std::string& prefix, unsigned int levels) {
    if (levels == 0){
        outs << prefix << "\n";
    }
    else {
        std::string s = "";
        char c;
        for (int i = 1; i <= 9; ++i) {
            c = 48 + i;
            s = (prefix + c) + '.';
            numbers(outs, s, levels - 1);
        }
    }
    
}

bool bears(int n) {
    // Postcondition: A true return value means that it is possible to win(42 bears)
    // the bear game by starting with n bears. A false return value means that
    // it is not possible to win the bear game by starting with n bears.
    if (n < 42) { return false; }
    if (n == 42) { return true; }

    bool solution = false;

    if (!solution && n % 5 == 0){
        solution = bears(n - 42);
    }
    if (!solution && (n % 3 == 0 || n % 4 == 0)) {
        if (n - ((n % 10) * ((n % 100) / 10)) != n) {
            solution = bears(n - ((n % 10) * ((n % 100) / 10)));
        }
    }
    if (!solution && n % 2 == 0) {
        solution = bears(n / 2);
    }
    return solution;
}

int fibR(int n) {
    if (n == 0) { return 0; }
    if (n == 1) { return 1; }
    return fibR(n - 1) + fibR(n - 2);
}

int fibI(int n) {
    if (n == 1 || n == 2)
        return 1;
    int A[2][2] = { { 1, 1 },{ 1, 0 } };
    int B[2][2] = { { 1, 1 },{ 1, 0 } };
    int temp[2][2];
    while (n >= 2) {
        for (int i = 0; i < 2; i++)
            for (int k = 0; k < 2; k++) {
                temp[i][k] = 0;
                for (int j = 0; j < 2; j++)
                    temp[i][k] += A[i][j] * B[j][k];
            }
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                B[i][j] = temp[i][j];
        n--;
    }
    return B[0][1];
}

int mainRecursion(){

    std::cout << "Triangle\n";
	triangle(std::cout, 3, 5);
    
    std::cout << "\nSection Number Printer\n";
    numbers(std::cout, "PREFIX",2);
    
    std::cout << "\nBears:\n";
    std::cout << "Enter starting number: ";
    int n;
    std::cin >> n;
    std::cout << n << " is " << std::boolalpha << bears(n) << "\n";

    std::cout << "\nFibonacci\n" << std::fixed;
    std::cout << std::setw(4) << "n"<< std::setw(16) <<"Recursive" << std::setw(16) << "time(s) R" 
                                 << std::setw(16) << "Iterative" << std::setw(16) << "time(s) I" << std::endl;

    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;
    int fib;
    for (int i = 1; i <= 45; ++i) {
        std::cout << std::setw(4) << i;

        //Recursive
        t1 = high_resolution_clock::now();
        fib = fibR(i);
        t2 = high_resolution_clock::now();
        std::cout << std::setw(16) << fib;

        duration<double> time_span = t2 - t1;
        std::cout << std::setw(16) << time_span.count();

        //Iterative
        t1 = high_resolution_clock::now();
        fib = fibI(i);
        t2 = high_resolution_clock::now();
        std::cout << std::setw(16) << fibI(i);

        time_span = t2 - t1;
        std::cout << std::setw(16) << time_span.count();

        std::cout << std::endl;
    }
    

	return 0;
}