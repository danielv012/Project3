//
//  main.cpp
//  Project3
//
//  DAV210004
//  Created by Daniel Vayman on 11/1/22.
//

//TODO: account for + in polynomial and fix insert function

#include <iostream>
#include <fstream>
#include <iomanip>
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
void displayIntegrals(vector<Integral> integrals);
double evaluate(Integral integral);
void removeSpaces(string &str);

int main()
{
    vector<Integral> integrals;
    string fileName;
    cout << "What's the filename? ";
    //cin >> fileName;
    fileName = "sample.txt";
    cout << endl;

    ifstream file;
    file.open(fileName);

    string polynomial = "";
    while(getline(file, polynomial))
    {
        if(polynomial.size() == 0) break;
        Integral tempPolynomial = parseLine(polynomial);
        integrals.push_back(tempPolynomial);
    }

    displayIntegrals(integrals);

}

Integral parseLine(string polynomial)
{
    Integral temp;

    //----integral boundaries-----//
    string bounds1 = polynomial.substr(0, polynomial.find('|'));
    polynomial.erase(0, bounds1.size());
    removeSpaces(bounds1);

    string bounds2 = polynomial.substr(polynomial.find('|'), polynomial.find(' '));
    polynomial.erase(0, bounds2.size() + 1);

    string bounds = bounds1 + bounds2;

    string upper = bounds.substr(0, bounds.find("|"));
    bounds.erase(bounds.find(upper), upper.length());

    bool negative = false;
    
    if(upper.size() == 0) //if there is no upper bound
    {
        temp.indefinite = true; //set integral to indefinite
        bounds.erase(0,1);
    }
    else
    {
        if(upper[0] == '-') //if the upperbound is negative
        {
            negative = true;
            upper.erase(0,1);
        }
        temp.upperBound = stoi(upper) * (negative ? -1 : 1);
        negative = false;
    }

    if(bounds[0] == '|' && !temp.indefinite)
    {
        bounds.erase(0,1);
        string lower = bounds;

        if(lower[0] == '-')
        {
            negative = true;
            lower.erase(0,1);
        }
        if(lower.length() != 0) temp.lowerBound = stoi(lower) * (negative ? -1 : 1);
        negative = false;
    }

    //-------Main integral---------//
    removeSpaces(polynomial);

    BinTree<Term> tempPoly;

    while(polynomial.length() > 0)
    {   
        Term tempTerm;

        string value = "";
        string bit = polynomial.substr(0, polynomial.find('d'));
        if(bit.find('x') == string::npos)
        {
            char checkChar = polynomial[0];
            while(checkChar != '-' && checkChar != '+' && checkChar != 'd')
            {
                value += checkChar;
                polynomial.erase(0,1);
                checkChar = polynomial[0];
            }
            tempTerm.SetCoeff(stod(value));
            tempTerm.SetExpon(0);
        }
        else
        {
            string coefficient = polynomial.substr(0, polynomial.find("x"));
            polynomial.erase(polynomial.find(coefficient), coefficient.length());

            if(coefficient.size() == 0) tempTerm.SetCoeff(1);
            else tempTerm.SetCoeff(stod(coefficient));

        if(polynomial[0] != 'x')
        {
            tempTerm.SetExpon(0);
        }
        else if(polynomial[1] != '^')
        {
            tempTerm.SetExpon(1);
            polynomial.erase(0,1);
        }
        else
        {
        polynomial.erase(0,2);

        bool negative = false;
        if(polynomial[0] == '-')
        {
            negative = true;
            polynomial.erase(0,1);
        }
        string exponent = "";
        char checkChar = polynomial[0];
        while(checkChar != '-' && checkChar != '+' && checkChar != 'd')
        {
            exponent +=checkChar;
            polynomial.erase(0,1);
            checkChar = polynomial[0];
        }
        
        double exponentNum = stod(exponent);
        if(negative) exponentNum *= -1;
        tempTerm.SetExpon(exponentNum);

        }
        }
        

        tempTerm.Integrate();

        Node<Term> *tempNode = new Node<Term>(tempTerm);

        tempPoly.Insert(tempNode);

        if(polynomial[0] == 'd') break;
        else if(polynomial[0] == '+') polynomial.erase(0,1);

    }
    temp.polynomial = tempPoly;
    
    return temp;
}


void displayIntegrals(vector<Integral> integrals)
{

    for(Integral integral : integrals)
    {
        integral.polynomial.GetLeftmost()->GetData()->SetFirst(true);
        integral.polynomial.Print();
        if(integral.indefinite) cout << " + C" << endl;
        else
        {
            cout << ", " << integral.upperBound << "|" << integral.lowerBound << " = " << setprecision(3) << fixed << evaluate(integral) << endl;
        }
    }
}

double evaluate(Integral integral)
{
    double sum = integral.polynomial.Evaluate(integral.upperBound) - integral.polynomial.Evaluate(integral.lowerBound);
    return sum;
}

void removeSpaces(string &str)
{
    int count = 0;
 
    for (int i = 0; i < (int)str.size(); i++)
    {
        if (str[i] != ' ')
            str[count++] = str[i]; 
    }

    str.erase(count, str.size() + 1);
}