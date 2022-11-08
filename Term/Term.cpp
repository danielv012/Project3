//
//  Term.cpp
//  Project3
//
//  Created by Daniel Vayman on 11/1/22.
//
#include <stdio.h>
#include "Term.h"

void Term::Integrate()
{
    this->SetExpon(this->GetExpon() + 1);
    this->SetCoeff(this->GetCoeff() / this->GetExpon());
    
}

/**
 * @brief Returns true if the terms are like terms, false if not
 * 
 * @param right term object compared to
 * @return true 
 * @return false 
 */
bool Term::operator==(Term &right)
{
    if(this->GetExpon() == right.GetExpon()) return true;
    return false;
}