#include <bits/stdc++.h>
#include "SndPoly.h"

SndPoly::SndPoly(const SndPoly& poly) {
    this->dense = poly.dense;
    this->sparse = poly.sparse;
    this->is_ordered = poly.is_ordered;
}

SndPoly::SndPoly(const SndPolyTerm& term) {
    this->dense.clear();
    this->dense.push_back(term);
    //?Update sparse?
}

//***STREAM OPERATIONS***

std::ostream& operator<<(std::ostream& os, const SndPoly& poly) {
    for(int i = 0; i < (int)poly.sparse.size(); i++) {
        os << poly.sparse[i];
        if(i < (int)poly.sparse.size() - 1) {
            os << " + ";
        }
    }
    return os;
}

SndPoly SndPoly::operator=(std::string str) {
    this->clear();
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, ' ')) {
        tokens.push_back(token);
    }

    int n = tokens.size();
    if(tokens.size() % 3 != 0)
        throw std::invalid_argument("Invalid input format for polynomial parsing (must be divisible by 3)");

    bool existing_poly;
    for(int i = 0; i < n; i += 3) {
        SndPolyTerm newTerm;
        PolyTerm auxTerm;
        newTerm.exp = std::stoi(tokens[i + 2]); // y's exponent
        auxTerm.coeff = tokens[i];
        auxTerm.exp = std::stoi(tokens[i + 1]);
        existing_poly = false;

        Polynomial tempPoly;
        tempPoly.sparse.push_back(auxTerm);

        for(int j = 0; j < (int)this->sparse.size(); j++) {
            //*In case there's already a term with y^exp
            if(newTerm.exp == this->sparse[j].exp) {
                existing_poly = true;
                // std::cout << "ENTER 1: Adding to existing y^" << newTerm.exp << "\n";
                this->sparse[j].poly = this->sparse[j].poly + tempPoly;
                break;
            }
        }
        
        if(!existing_poly) {
            // std::cout << "ENTER 2: Creating new y^" << newTerm.exp << "\n";
            newTerm.poly = tempPoly;
            this->sparse.push_back(newTerm);
        }
    }

    this->order_poly();

    return *this;
}


//***UTILS***

void SndPoly::order_poly() {
    if(is_ordered) return;

    std::sort(sparse.begin(), sparse.end(),
        [](const SndPolyTerm& a, const SndPolyTerm& b) {
            return a.exp > b.exp;
        });

    is_ordered = true;
}

void SndPoly::clear() {
    this->sparse.clear();
    this->dense.clear();
    this->is_ordered = false;
}

bool SndPoly::isZero() {
    for(const SndPolyTerm& term : this->sparse) {
        if(!term.poly.isZero()){
            return false;
        }
    }
    return true;
}

//***ARITHMETIC OPERATIONS***

SndPoly SndPoly::operator+(const SndPoly& other) const {
    int j = 0, i = 0, this_size = sparse.size(), other_size = other.sparse.size();
    SndPoly result;
    
    while((i < this_size) && (j < other_size))
    {
        if(sparse[i].exp > other.sparse[j].exp) {
            result.sparse.push_back(sparse[i]);
            i++;
        }
        else if (sparse[i].exp == other.sparse[j].exp) {
            SndPolyTerm newTerm;
            newTerm.poly = sparse[i].poly + other.sparse[j].poly;
            if(!newTerm.poly.isZero()) {
                newTerm.exp = sparse[i].exp;
                result.sparse.push_back(newTerm);
            }
            i++;
            j++;
        }
        else if (sparse[i].exp < other.sparse[j].exp){
            result.sparse.push_back(other.sparse[j]);
            j++;
        }
    }

    //*Include the trailing polynomial terms that were not included because
    //*one of the two polynomials has been completely traversed over.
    if(i < this_size) {
        while (i < this_size) {
            result.sparse.push_back(sparse[i]);
            i++;
        }
    }
    else if(j < other_size) {
        while (j < other_size) {
            result.sparse.push_back(other.sparse[j]);
            j++;
        }
    }

    if(result.isZero()) {
        result.clear();
        result.sparse.push_back(SndPolyTerm(Polynomial(PolyTerm(0, 0)), 0));
    }

    return result;
}

SndPoly SndPoly::operator-() const {
    SndPoly result = *this;

    for(int i = 0; i < (int)result.sparse.size(); i++) {
        result.sparse[i].poly = -result.sparse[i].poly;
    }

    return result;
}

SndPoly SndPoly::operator-(const SndPoly& other) const {
    return *this + (-other);
}

SndPoly operator*(const SndPoly& sndPoly, const SndPolyTerm& term) {
    SndPoly result;
    if(term.poly.isZero()) {
        result.sparse.push_back(SndPolyTerm(term.poly, 0));
        return result;
    }

    for(int i = 0; i < (int)sndPoly.sparse.size(); i++) {
        Polynomial auxPoly = sndPoly.sparse[i].poly * term.poly;
        result.sparse.push_back(SndPolyTerm(auxPoly, sndPoly.sparse[i].exp + term.exp));
    }

    return result;
}

Integer SndPoly::getUnit() {
    if(this->sparse[0].poly.get_leading_coefficient() >= 0)
        return Integer(1);
    else
        return Integer(-1);
}

Polynomial SndPoly::getCont() {
    int sparse_size = (int)this->sparse.size();
    if(sparse_size == 0)
        throw std::invalid_argument("Sparse is empty");
    if(sparse_size == 1) 
        return this->sparse[0].poly;
    
    Polynomial gcd = Polynomial::monicPolyGCD(this->sparse[0].poly, this->sparse[1].poly);
    std::cout << "gcd: " << this->sparse[0].poly << " and " << this->sparse[1].poly << " is: " << gcd << "\n";
    for(int i = 2; i < sparse_size; i++) {
        std::cout << "gcd: " << gcd << " and " << this->sparse[i].poly;
        gcd = Polynomial::monicPolyGCD(gcd, this->sparse[i].poly);
        std::cout << " is: " << gcd << "\n";

    }

    return gcd;
}

SndPoly SndPoly::gcd(const SndPoly& lhs, const SndPoly& rhs) {

}