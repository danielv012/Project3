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