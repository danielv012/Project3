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
    BinTree<Term> polynomial;
    int upperBound = 0;
    int lowerBound = 0;
    bool indefinite = false;
};

Integral parseLine(string polynomial);

int main()
{
    vector<Integral> integrals;
    string fileName;
    cout << "What's the filename? ";
    //cin >> fileName;
    fileName = "sample.txt";

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


    string lower = polynomial.substr(0, polynomial.find("|"));
    polynomial.erase(polynomial.find(lower), lower.length());

    bool negative = false;
    
    if(lower.size() == 0)
    {
        temp.indefinite = true;
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


    if(polynomial[0] == '|')
    {
        polynomial.erase(0,1);
        string upper = polynomial.substr(0, polynomial.find(" "));
        polynomial.erase(polynomial.find(lower), lower.length() + 1);


        if(upper[0] == '-')
        {
            negative = true;
            upper.erase(0,1);
        }
        if(upper.length() != 0) temp.upperBound = stoi(upper) * (negative ? -1 : 1);
        negative = false;
    }

    cout << temp.upperBound << " " << temp.lowerBound;

    //-------Main integral---------//

    BinTree<Term> tempPoly;

    while(polynomial.length() > 0)
    {
    string term = polynomial.substr(0, polynomial.find(" "));
    polynomial.erase(polynomial.find(term), term.length() + 1);

    Term tempTerm;

    int coefficient = stoi(term.substr(0, term.find('x')));
    tempTerm.SetCoeff(coefficient);

    term.erase(0, term.find('x') + 1);

    int exponent = stoi(term);
    tempTerm.SetExpon(exponent);

    tempTerm.Integrate();

    Node<Term>* tempNode = new Node<Term>(tempTerm);

    tempPoly.Insert(tempNode);
    }
    
    return temp;
}

