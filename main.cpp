//
//  main.cpp
//  Project3
//
//  DAV210004
//  Created by Daniel Vayman on 11/1/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "BinTree.h"
#include "Term/Term.h"
#include "Node.h"

using namespace std;

struct Integral
{
    BinTree<Node<Term>> polynomial;
    int upperBound = 0;
    int lowerBound = 0;
};

Integral parseLine(string polynomial);

int main()
{
    vector<Integral> integrals;
    string fileName;
    cout << "What's the filename? ";
    cin >> fileName;

    ifstream file;
    file.open(fileName);

    string polynomial = "";
    while(getline(file, polynomial))
    {
        Integral tempPolynomial = parseLine(polynomial);
        integrals.push_back(tempPolynomial);
    }

}

Integral parseLine(string polynomial)
{
    Integral temp;

    //----integral boundaries-----//


    string lower = polynomial.substr(0, polynomial.find(" "));
    polynomial.erase(polynomial.find(lower), lower.length());

    bool negative = false;
    
    if(lower[0] == '|')
    {
        temp.lowerBound = NULL;
    }
    else
    {
        if(lower[0] == '-')
        {
            negative = true;
            lower.erase(0,1);
        }
        temp.lowerBound = stoi(lower) * (negative ? -1 : 1);
        negative = false;
    }

    polynomial.erase(0,1);
    if(polynomial[0] == '|')
    {
        polynomial.erase(0,2);
        string upper = polynomial.substr(0, polynomial.find(" "));
        polynomial.erase(polynomial.find(lower), lower.length() + 1);

        if(upper[0] == '-')
        {
            negative = true;
            upper.erase(0,1);
        }
        temp.upperBound = stoi(upper) * (negative ? -1 : 1);
        negative = false;
    }
    else
    {
        polynomial.erase(0,2);
    }

    //-------Main integral---------//

    


}

