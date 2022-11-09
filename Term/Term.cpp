//
//  Term.cpp
//  Project3
//
//  Created by Daniel Vayman on 11/1/22.
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "Term.h"

using namespace std;

//---------Constructors-------//

Term::Term()
{
    coeff = 0;
    expon = 0;
    coeffStr = "";
    exponStr = "";
    first = false;
}

Term::Term(Term &obj)
{
    this->coeff = obj.GetCoeff();
    this->expon = obj.GetExpon();
    this->coeffStr = obj.GetCoeffStr();
    this->exponStr = obj.GetExponStr();
    this->first = obj.IsFirst();
}



//----------------------------//

void Term::Integrate()
{
    if(this->GetExpon() == 0)
    {
        this->SetExpon(1);
        this->SetCoeffStr(to_string((int)(this->GetCoeff()) * (this->GetCoeff() < 0 ? -1 : 1)));
    }
    else
    {
        this->SetExpon(this->GetExpon() + 1);
        this->SetExponStr(to_string((int)(this->GetExpon())));

        int oldCoeff = (int)this->GetCoeff();
        this->SetCoeff(this->GetCoeff() / this->GetExpon());
        if(fmod(this->GetCoeff(),1) == 0)
        {
            this->SetCoeffStr(to_string((int)(this->GetCoeff()) * (this->GetCoeff() < 0 ? -1 : 1)));
        }
        else
        {
            string coeffStr = "";
        if(oldCoeff < 0 && this->GetExpon() < 0)
        {
            oldCoeff *= -1;
            coeffStr = Simplify(oldCoeff, ((int)(this->GetExpon()) * -1));
        }
        else if(oldCoeff < 0)
        {
            oldCoeff *= -1;
            coeffStr = Simplify(oldCoeff,((int)(this->GetExpon())));
        }
        else
        {
            coeffStr = Simplify(oldCoeff, ((int)(this->GetExpon()) * (this->GetExpon() < 0 ? -1 : 1)));
        }
        
        this->SetCoeffStr(coeffStr);
        }
    }
}



Term& Term::operator=(const Term &obj)
{
    this->coeff = obj.coeff;
    this->expon = obj.expon;
    this->coeffStr = obj.coeffStr;
    this->exponStr = obj.exponStr;
    return *this;
}

/**
 * @brief Returns true if the terms are like terms, false if not
 * 
 * @param right term object compared to
 * @return true 
 * @return false 
 */
bool Term::operator==(const Term &right)
{
    if(this->expon == right.expon) return true;
    return false;
}

bool Term::operator>(const Term &right)
{
    if(this->expon > right.expon) return true;
    return false;
}

bool Term::operator<(const Term &right)
{
    if(this->expon < right.expon) return true;
    return false;
}

string Term::Simplify(int num, int denom)
{
    string fraction = "";

    if(denom == 0
    || denom == 1
    || num == 0
    || num == 1)
    {
        fraction = "(" + to_string(num) + "/" + to_string(denom) + ")";
    }
    else
    {
        int gcdNum = gcd(num, denom);
        num /= gcdNum;
        denom /= gcdNum;
        fraction = "(" + to_string(num) + "/" + to_string(denom) + ")";
    }

    return fraction;
}

int Term::gcd(int x, int y)
{
    x = abs(x);
    y = abs(y);

    if(y == 0)
    {
        return x;
    }
    else if(x > y)
    {
        return gcd(y, x%y);
    }
    else if(x < y)
    {
        return gcd(x, y%x);
    }

    return x;
}