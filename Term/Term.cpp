//
//  Term.cpp
//  Project3
//
//  Created by Daniel Vayman on 11/1/22.
//
#include <stdio.h>
#include "Term.h"

//---------Constructors-------//

Term::Term()
{
    coeff = 0;
    expon = 0;
}

Term::Term(Term &obj)
{
    this->coeff = obj.GetCoeff();
    this->expon = obj.GetExpon();
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
        this->SetCoeff(this->GetCoeff() / this->GetExpon());
    }
}



Term& Term::operator=(const Term &obj)
{
    this->coeff = obj.coeff;
    this->expon = obj.expon;
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

