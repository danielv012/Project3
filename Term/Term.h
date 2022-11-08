//
//  Term.h
//  Project3
//
//  Created by Daniel Vayman on 11/1/22.
//

#ifndef Term_h
#define Term_h

using namespace std;

class Term
{
    private:
        double coeff;
        double expon;
        string coeffStr;
        string exponStr;
        bool first;
    public:
        Term();
        Term(Term &obj);

        void Integrate();

        void SetCoeff(double num) {coeff = num;}
        double GetCoeff() {return coeff;}

        void SetExpon(double num) {expon = num;}
        double GetExpon() {return expon;}

        void SetCoeffStr(string str) {coeffStr = str;}
        string GetCoeffStr() {return coeffStr;}

        void SetExponStr(string str) {exponStr = str;}
        string GetExponStr() {return exponStr;}


        void SetFirst(bool check) {first = check;}
        bool IsFirst() {return first;}

        //-----Overloaed Operators-----//

        bool operator==(const Term &right);
        bool operator>(const Term &right);
        bool operator<(const Term &right);
        Term& operator=(const Term &obj);

};

#endif /* Term_h */
