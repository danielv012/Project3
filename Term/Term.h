//
//  Term.h
//  Project3
//
//  Created by Daniel Vayman on 11/1/22.
//

#ifndef Term_h
#define Term_h

class Term
{
    private:
        double coeff;
        double expon;
    public:
        Term();
        Term(Term &obj);

        void Integrate();

        void SetCoeff(int num) {coeff = num;}
        int GetCoeff() {return coeff;}

        void SetExpon(int num) {expon = num;}
        int GetExpon() {return expon;}

        //-----Overloaed Operators-----//

        bool operator==(const Term &right);
        bool operator>(const Term &right);
        bool operator<(const Term &right);
        Term& operator=(const Term &obj);

};

#endif /* Term_h */
