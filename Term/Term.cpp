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
    }
    else
    {
        this->SetExpon(this->GetExpon() + 1);
        this->SetExponStr(to_string((int)(this->GetExpon())));

        double oldCoeff = this->GetCoeff();
        this->SetCoeff(this->GetCoeff() / this->GetExpon());
        if(fmod(this->GetCoeff(),1) == 0)
        {
            this->SetCoeffStr(to_string((int)(this->GetCoeff())));
        }
        else
        {
        string coeffStr = "(" + to_string(oldCoeff).substr(0,to_string(oldCoeff).find('.'))  + "/" + to_string((int)(this->GetExpon())) + ")";
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

