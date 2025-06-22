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

    return result;
}

