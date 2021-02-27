// File: queens.cxx
// Written by: Michael Main (main@colorado.edu) Nov 20, 2002
//
// This is a solution to the n-queens problem from Chapter 7
// of "Data Structures and Other Objects Using C++".
// This solution varies a bit from the problem in that the 
// top of the Stack will be the column choice for row 1.
// Below that is the column choice for row 2, and so on.
// For example, with n set to 5, the solution shown in the book is:
// Q - - - -
// - - Q - -
// - - - - Q
// - Q - - -
// - - - Q -
// My Stack would record this solution as:
// [Bottom of Stack] 4 2 5 3 1 [Top of Stack].
// So, I don't actually record the choices of the row numbers, and
// furthermore, it's not possible to ever have two queens in the same row.
// Each time I push a new number on top of the Stack, the other rows get
// shifted to the next higher row number.

#include <cassert>
#include <iostream>
#include "stack3.h" // Provides the Stack class with a peek(i) function.
using namespace std;
using namespace main_savitch_7A;

void print_solution(Stack<unsigned int> choices)
{
    size_t maxSize {choices.size( )};
    
    cout << "Solution for n = " << choices.size( ) << endl;
    for (size_t i = 1 ; i < maxSize; i++ ) cout << "=="; cout <<"="<<endl;

    for (size_t i = 1 ; !choices.empty( ); i++)
    {
        unsigned int col = choices.pop( );
        for ( unsigned int r=1 ; r<=maxSize ; r++)
            cout << (r == col? "Q " : "- ");
        cout << " Queen in row " << i << ", column " << col << endl;
    }

    for (size_t i = 1 ; i < maxSize; i++ ) cout << "=="; cout <<"="<<endl;
}

bool is_conflict(/*const*/ Stack<unsigned int>& choices)
{
    unsigned int i;
    unsigned int newqueen = choices.top( );
    unsigned int other;
    
    //std::cout << "Checking against, New Queen Column: "<<newqueen <<std::endl;
    for (i = 2; i <= choices.size( ); ++i)
    {   // Check whether queen on top of the Stack (which is in row 1)
        // conflicts with the queen in row number i.  If so, then return
        // true right away because we found a conflict.
        other = choices.peek(i);
        //std::cout<<"\tAgainst col: "<<other<<std::endl;
        if ((newqueen == other)          // Queens in the same column
            || (newqueen+(i-1) == other) // Diagonal left-to-right
            || (newqueen-(i-1) == other) // Diagonal right-to-left
            ){
            //std::cout <<"Conflict" << std::endl;
            return true;
        }
    }
    //std::cout <<"No conflict"<<std::endl;
    return false;
}

void queens(unsigned int nQueens)
{
    Stack<unsigned int> choices;
    bool success = false;
    assert (nQueens >= 1);
    
    choices.push(1);    // Start with 1st column (pushed) in the 1st row (last popped)
    
    while (!success && !choices.empty( ))
    {
        if (is_conflict(choices))
        {
        // Your code goes here
            unsigned int temp = choices.pop() + 1;
            while (temp > nQueens && !choices.empty()) {
                temp = choices.pop() + 1;
            }
            if(temp <= nQueens) choices.push(temp);
        }
        else if (choices.size( ) == nQueens)
            success = true;     // All queens placed
        else
            choices.push(1);    // Start at 1 for the next row
    }
    
    if (success)
        print_solution(choices);
    else
        cout << "No solutions were found." << endl;
}

int mainQueen( )
{
    unsigned int n;
    
    cout << "Please enter n for the n-queens problem (n >= 1): ";
    cin >> n;
    queens(n);
    
    return 0;
}
