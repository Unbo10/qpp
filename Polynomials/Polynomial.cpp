#include <bits/stdc++.h>

#include "Polynomial.h"
#include "../include/Rational.h"

Polynomial::Polynomial() {}

Polynomial::Polynomial(const PolyTerm& term) {
    dense = std::vector<Rational>(term.exp + 1, Rational(0));
    degree = term.exp;
    sparse.push_back(term);
    if((term.coeff.getDenominator() != 1) || (term.coeff.getDenominator() != -1))
        is_rational = true;
    is_dense_valid = true;
    is_sparse_valid = true;
}

Polynomial::Polynomial(const std::string& str) { *this = str; }

Polynomial::Polynomial(const Polynomial& other) {
    this->dense = other.dense; 
    this->sparse = other.sparse;
    this->degree = other.degree;
    
    this->is_dense_valid = other.is_dense_valid;
    this->is_sparse_valid = other.is_sparse_valid;
    this->is_ordered = other.is_ordered;
    this->is_rational = other.is_rational;
}

// Print the polynomial in standard mathematical form
void Polynomial::printPolynomial() {
        // print only the nonzero coefficients in the dense representation
        // int degree = getDegree();
        // for (const auto& coeff : dense) {
        //     if (coeff != 0) {
        //         std::cout << coeff << " " << "x^" << degree--;
        //         if (degree >= 0) {
        //             std::cout << " + ";
        //         }
        //     }
        //     else {
        //         degree--;
        //     }
            
        // }
    std::cout << std::endl;
    int n = sparse.size();
    
    for(int i = 0; i < n; i++) {
        std::cout << sparse[i].coeff << "x^" << sparse[i].exp;
        if(i < n - 1) std::cout<< " + ";
    }
    std::cout << std::endl;



        // if (!is_sparse_valid) generateSparse();
        
        // if (sparse.empty()) {
        //     std::cout << "0" << std::endl;
        //     return;
        // }
        
        // std::cout << "Polynomial: ";
        // bool first = true;
        
        // for (const auto& term : sparse) {
        //     double coeff = term.first;
        //     int power = term.second;
            
        //     // Handle sign
        //     if (!first) {
        //         std::cout << (coeff >= 0 ? " + " : " - ");
        //         coeff = std::fabs(coeff);
        //     } else if (coeff < 0) {
        //         std::cout << "-";
        //         coeff = std::fabs(coeff);
        //     }
            
        //     // Handle coefficient
        //     if (power == 0 || coeff != 1) {
        //         std::cout << coeff;
        //     }
            
        //     // Handle variable and power
        //     if (power > 0) {
        //         std::cout << "x";
        //         if (power > 1) {
        //             std::cout << "^" << power;
        //         }
        //     }
            
        //     first = false;
        // }
        // std::cout << std::endl;
}
    
//***UTILS***

// Get maximum degree of the polynomial
int Polynomial::getDegree() { return degree; }

void Polynomial::clear() {
    dense.clear();
    sparse.clear();
    is_dense_valid = false;
    is_sparse_valid = false;
    degree = 0;
}

bool Polynomial::isZero() const {
    if(sparse.empty() && dense.empty()) return true;
    // if(is_dense_valid) {
    //     for(const auto& coeff : dense) {
    //         if(coeff != Rational(0)) return false;
    //     }
    // }
    // else {
    for(const PolyTerm& term : sparse) {
        if(term.coeff != 0){
            return false;
        } 
    }
    // }
    return true;
}

//*Sorts them in descending order (greatest to smallest exponent)
void Polynomial::order_poly() {
    if(is_ordered) return;

    std::sort(sparse.begin(), sparse.end(), 
        [](const PolyTerm& a, const PolyTerm& b) {
            return a.exp > b.exp;
        });

    this->is_ordered = true;
    if((int)this->sparse.size() > 0)
        this->degree = this->sparse[0].exp;
    else
        this->degree = 0;
}

Rational Polynomial::get_leading_coefficient() const { return this->sparse[0].coeff; }

//***OSTREAM AND ISTREAM***

Polynomial Polynomial::operator=(const Polynomial& other) {
    this->degree = other.degree;
    this->dense = other.dense;
    this->sparse = other.sparse;
    
    this->is_dense_valid = other.is_dense_valid;
    this->is_ordered = other.is_ordered;
    this->is_rational = other.is_rational;
    this->is_sparse_valid = other.is_sparse_valid;
    return *this;
}

Polynomial Polynomial::operator=(std::string str) {
    this->clear();
    if(str.find('/') != std::string::npos) is_rational = true;

    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, ' ')) {
        tokens.push_back(token);
    }

    PolyTerm term;
    std::string::size_type num_index;
    int num, den;
    int n = tokens.size();
    // for (const std::string& token : tokens) {
    //     std::cout << "Token: " << token << "\n";
    // }
    if(n % 2 == 1) throw std::invalid_argument("There must be one coefficient per each exponent");

    for(int i = 0; i < n; i += 2) {
        num_index = tokens[i].find('/');
        
        //*This part could be handled by the operator= of a PolyTerm
        if(is_rational) {
            //*Rational number
            if(num_index != std::string::npos) {
                num = std::stoi(tokens[i].substr(0, num_index));
                den = std::stoi(tokens[i].substr(num_index + 1));
            }
            else {
                num = std::stoi(tokens[i].substr(0));
                den = 1;
            }
        }
        else {
            //*Integer
            num = std::stoi(tokens[i]);
            den = 1;
        }
        Rational coeff(num, den);
        term.coeff = coeff;
        term.exp = std::stoi(tokens[i + 1]);
        sparse.push_back(term);
    }

    this->order_poly();
    this->update_dense();
    return *this;
}

Polynomial Polynomial::update_sparse(){
    sparse.clear();
    int n = dense.size();
    for(int i = 0; i < n; i++) {
        if(dense[i] != Rational(0)) {
            PolyTerm term;
            term.coeff = dense[i];
            term.exp = n - 1 - i;  // Convert index to exponent
            sparse.push_back(term);
        }
    }
    return *this;
}

Polynomial Polynomial::update_dense() {
    dense.clear();
    int n = sparse.size();
    if(n == 0) return *this;

    // Find the maximum exponent to determine the size of the dense vector
    degree = sparse[0].exp;
    dense.resize(degree + 1, Rational(0));

    for(int i = 0; i < n; i++) {
        if(sparse[i].exp >= 0 && sparse[i].exp <= degree) {
            dense[degree - sparse[i].exp] = sparse[i].coeff;  // Convert exponent to index
        }
    }
    is_dense_valid = true;
    return *this;
}

std::istream& operator>>(std::istream& is, Polynomial& poly) {
    std::string line;
    std::getline(is, line);
    if (!line.empty()) {
        poly = line;
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {

    // if(poly.is_dense_valid) {
    //     os << "Dense representation: ";
    //     for (const auto& coeff : poly.dense) {
    //         os << coeff << " ";
    //     }
    //     os << "\n";
    // }
    // else{
    int n = poly.sparse.size();

    for(int i = 0; i < n; i++) {
        os << poly.sparse[i];
        if(i < n - 1) os << " + ";
    }
    // }
    return os;
}

//***COMPARISON OPERATIONS***

// std::istream& operator>>(std::istream& is, const Polynomial& other) {

// }

//***ARITHMETIC OPERATIONS***

Polynomial Polynomial::multiply_by_single_term_poly(const PolyTerm& singleTerm) {
    this->order_poly();
    if((singleTerm.coeff == 0)) {
        Polynomial prod;
        prod.sparse.push_back(PolyTerm(0, 0));
        return prod;
    }
    if((singleTerm.coeff == 1) && (singleTerm.exp == 0)) return *this;

    int n = this->sparse.size();
    Polynomial prod;
    PolyTerm prodTerm;

    for(int i = 0; i < n; i++) {
        prodTerm = this->sparse[i] * singleTerm;
        prod.sparse.push_back(prodTerm);
    }
    prod.update_dense();
    prod.is_ordered = true;
    prod.degree = prod.sparse[0].exp;
    return prod;
}

Polynomial Polynomial::multiply_by_single_term_poly(const Polynomial& singleTerm) {
    if(singleTerm.sparse.size() != 1) throw std::invalid_argument("Polynomial is not a single-term polynomial; has " + std::to_string(singleTerm.sparse.size()) + " non-zero terms");

    return this->multiply_by_single_term_poly(singleTerm.sparse[0]);
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    int j = 0, i = 0, this_size = sparse.size(), other_size = other.sparse.size();
    Polynomial result;
    
    while((i < this_size) && (j < other_size))
    {
        if(sparse[i].exp > other.sparse[j].exp) {
            result.sparse.push_back(sparse[i]);
            i++;
        }
        else if (sparse[i].exp == other.sparse[j].exp) {
            PolyTerm newTerm;
            newTerm.coeff = sparse[i].coeff + other.sparse[j].coeff;
            if(newTerm.coeff != 0) {
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

    //*In case it is the zero polynomial
    if(result.isZero()) {
        PolyTerm zeroTerm;
        zeroTerm.coeff = 0;
        zeroTerm.exp = 0;
        result.sparse.push_back(zeroTerm);
    }

    result.order_poly();

    return result;
}

Polynomial operator+(const Polynomial& poly, PolyTerm& term) {
    Polynomial newPoly(term);
    return poly + newPoly;
}

Polynomial Polynomial::operator-() const {
    if(this->isZero())
        return *this;

    Polynomial result = *this;
    for(int i = 0; i < (int)this->sparse.size(); i++) {
        result.sparse[i].coeff = -result.sparse[i].coeff;
    }

    return result;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    return *this + (-other);
}

Polynomial Polynomial::operator*(const Polynomial& other) {
    Polynomial result;
    Polynomial oneProd;
    for(int i = 0; i < (int)other.sparse.size(); i++) {
        oneProd = this->multiply_by_single_term_poly(other.sparse[i]);
        result = result + oneProd;
    }

    result.order_poly();
    result.degree = result.sparse[0].exp;

    return result;
}

Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs) {
    return Polynomial(lhs).operator*(rhs);
}

Polynomial operator*(const Polynomial& poly, const Integer& num) {
    if(num == 0)
        return Polynomial(PolyTerm(0, 0));
    if(num == 1)
        return poly;
    if(num == -1)
        return -poly;

    Polynomial result(poly);
    for(int i = 0; i < (int)poly.sparse.size(); i++) {
        result.sparse[i].coeff = result.sparse[i].coeff * num;
    }
    result.update_dense();

    return result;
}

Polynomial Polynomial::operator/(const Polynomial& divisor) const {
    if(divisor.isZero()) throw std::invalid_argument("Cannot divide by zero polynomial");
    if(divisor.degree > this->degree) return Polynomial("0 0"); //*Return zero polynomial if divisor degree is greater than dividend degree
    
    Polynomial r(*this), q;
    q.dense.resize(this->degree - divisor.degree + 1, Rational(0, 1));
    
    // std::cout << "AAAA" << divisor.degree << " " << this->degree << "\n";
    r.update_dense();
    for(int i = 0; i <= this->degree - divisor.degree; i++){
        q.dense[i] = r.dense[i] / divisor.dense[0];
        for(int j = 0; j <= divisor.degree ; j++){
            r.dense[i + j] = r.dense[i+j] - (q.dense[i] * divisor.dense[j]);
        }
    }
    q.update_sparse();
    q.degree = q.sparse[0].exp;


    return q;
}

Polynomial operator^(const Polynomial& poly, int num) {
    if(num == 1)
        return poly;
    Polynomial result;
    if(num == 0){
        result.sparse.push_back(PolyTerm(1, 0));
        result.dense.push_back(1);
        result.degree = 0;
    }

    result = poly;
    for(int i = 1; i < num; i++) {
        result = result * poly;
    }

    //*Sparse and degree updated in *
    return result;
}

// Polynomial Polynomial::to_integer_poly() {
//     if(!is_rational) return *this;
    
//     // Find the LCM of all denominators
//     Integer lcm_den = 1;
//     int n = sparse.size();
    
//     for(int i = 0; i < n; i++) {
//         Integer current_den = sparse[i].coeff.getDenominator();
//         Integer gcd = Integer::gcd(lcm_den, current_den);
//         lcm_den = (lcm_den * current_den) / gcd;
//     }
    
//     Polynomial result;
//     for(int i = 0; i < n; i++) {
//         PolyTerm term = sparse[i];
//         Integer factor = lcm_den / term.coeff.getDenominator();
//         // std::cout << "FActor: " << factor << ", " << lcm_den << ", " << term.coeff.getDenominator() << "\n";
//         term.coeff = (term.coeff.getNumerator() * factor) / 1;
//         result.sparse.push_back(term);
//     }
    
//     result.is_ordered = is_ordered;
//     result.is_rational = true;  // It's still rational, just with common denominator
    
//     return result;
// }

//***INTEGER POLYNOMIALS***

Integer Polynomial::find_gcd_of_poly_terms() {
    if (sparse.size() < 2) return sparse[0].coeff.getNumerator();
    
    Integer gcd;
    gcd = Integer::gcd(sparse[0].coeff.getNumerator(), sparse[1].coeff.getNumerator());
    // std::cout << "GCD of " << sparse[0].coeff.getNumerator() << ", " << sparse[1].coeff.getNumerator() << " is " << gcd << ", " << sparse.size() << "\n";
    for(int i = 2; i < (int)sparse.size(); i++) {
        // std::cout << "GCD: " << gcd << "\n";
        gcd = Integer::gcd(gcd, sparse[i].coeff.getNumerator());
    }

    return gcd;
}

Integer Polynomial::find_lcm_of_poly_terms() {
    if (sparse.size() < 2) return sparse[0].coeff.getDenominator();
    
    Integer lcm = sparse[0].coeff.getDenominator();
    for(int i = 1; i < (int)sparse.size(); i++) {
        Integer current_den = sparse[i].coeff.getDenominator();
        Integer gcd = Integer::gcd(lcm, current_den);
        lcm = (lcm * current_den) / gcd;
    }

    return lcm;
}

//***RATIONAL POLYNOMIALS***

Polynomial Polynomial::remainder(const Polynomial& dividend, const Polynomial& divisor) {
    if(dividend.degree < divisor.degree)
        return dividend;

    Polynomial r(dividend), q;
    q.dense.resize(dividend.degree - divisor.degree + 1, Rational(0, 1));

    for(int i = 0; i <= dividend.degree - divisor.degree; i++){
        q.dense[i] = r.dense[i] / divisor.dense[0];
        for(int j = 0; j <= divisor.degree ; j++){
            r.dense[i + j] = r.dense[i+j] - (q.dense[i] * divisor.dense[j]);
        }
    }
    q.update_sparse();
    r.update_sparse();
    if (r.isZero()) {
        r.dense.clear();
        r.sparse.clear();
        r.dense.push_back(Rational(0));
        r.sparse.push_back(PolyTerm(Rational(0), 0));
        r.degree = 0;
    }
    r.degree = r.sparse[0].exp;
    return r;
}

Integer Polynomial::content(){
    Integer gcd = find_gcd_of_poly_terms();
    if(gcd == 0) return 1; // If all coefficients are zero, content is 1
    return gcd;
}

Polynomial Polynomial::primitive_part() {
    Integer content = this->content();
    PolyTerm term;
    if (this->dense[0] < Rational(0)) {
        content = -content; // Unit
    }
    term.coeff = Rational(1, content);
    term.exp = 0;
    Polynomial ret = this->multiply_by_single_term_poly(term);
    ret.update_sparse();
    ret.update_dense();
    // if((ret.sparse.size() == 0) && (ret.dense.size() == 0)) {
    //     ret.sparse.push_back(PolyTerm(Rational(0), 0));
    //     ret.dense.push_back(Rational(0));
    // }
    return ret;
}

Polynomial Polynomial::pseudoquotient(Polynomial u, Polynomial v) {
    Integer beta = u.find_lcm_of_poly_terms();
    Integer gamma = v.find_lcm_of_poly_terms();
    PolyTerm term1, term2;
    term1.coeff = Rational(beta, 1);
    term1.exp = 0;
    term2.coeff = Rational(gamma, 1);
    term2.exp = 0;

    Polynomial u_prime = u.multiply_by_single_term_poly(term1);
    Polynomial v_prime = v.multiply_by_single_term_poly(term2);

    Integer alpha = v_prime.sparse[0].coeff.getNumerator()^Integer(u.getDegree() - v.getDegree() + 1);

    PolyTerm term3;
    term3.coeff = Rational(alpha, 1);
    term3.exp = 0;

    Polynomial u_prime_scaled = u_prime.multiply_by_single_term_poly(term3);
    u_prime_scaled.update_dense();
    v_prime.update_dense();
    Polynomial q = u_prime_scaled / v_prime;

    PolyTerm term4;
    term4.coeff = Rational(gamma, beta * alpha);
    term4.exp = 0;

    //Polynomial q_scaled = q.multiply_by_single_term_poly(term4);
    return q;
}

Polynomial Polynomial::pseudoremainder(Polynomial u, Polynomial v) {
    Integer beta = u.find_lcm_of_poly_terms();
    Integer gamma = v.find_lcm_of_poly_terms();
    PolyTerm term1, term2;
    term1.coeff = Rational(beta, 1);
    term1.exp = 0;
    term2.coeff = Rational(gamma, 1);
    term2.exp = 0;

    Polynomial u_prime = u.multiply_by_single_term_poly(term1);
    Polynomial v_prime = v.multiply_by_single_term_poly(term2);

    Integer alpha = v_prime.sparse[0].coeff.getNumerator()^Integer(u.getDegree() - v.getDegree() + 1);

    PolyTerm term3;
    term3.coeff = Rational(alpha, 1);
    term3.exp = 0;

    Polynomial u_prime_scaled = u_prime.multiply_by_single_term_poly(term3);
    u_prime_scaled.update_dense();
    v_prime.update_dense();

    Polynomial r = Polynomial::remainder(u_prime_scaled, v_prime);
    r.update_sparse();
    r.update_dense();
    return r;
}

Polynomial Polynomial::primitivePolyGCD(Polynomial u, Polynomial v) {
    Integer u_content = u.content();
    Integer v_content = v.content();
    Polynomial u_primitive = u.primitive_part();
    Polynomial v_primitive = v.primitive_part();
    u_primitive.update_dense();
    v_primitive.update_dense();
    Integer c = Integer::gcd(u_content, v_content);
    std::cout << "U primitive: " << u_primitive << ", V pr: " << v_primitive << "\n";
    Polynomial r = Polynomial::pseudoremainder(u_primitive ,v_primitive);
    while ((v_primitive.getDegree() > 0)) {
        Polynomial r_primitive = r.primitive_part();
        u_primitive = v_primitive;
        v_primitive = r_primitive;

        u_primitive.update_sparse();
        v_primitive.update_sparse();
        u_primitive.update_dense();
        v_primitive.update_dense();

        std::cout << "U primitive: " << u_primitive << "\n";
        std::cout << "V primitive: " << v_primitive << "\n";
        std::cout << "deg: " << v_primitive.getDegree() << "\n";

        std::cout << "Remainder: " << r << "\n";
        r = Polynomial::pseudoremainder(u_primitive, v_primitive);
    }
    if (v_primitive.isZero()) {
        PolyTerm term4;
        term4.coeff = Rational(c, 1);
        term4.exp = 0;
        return v_primitive.multiply_by_single_term_poly(term4);
    }
    else {
        Polynomial c_pol;
        c_pol.dense.push_back(c);
        c_pol.update_sparse();
        return c_pol;
    }
}

Polynomial Polynomial::monicPolyGCD(Polynomial p, Polynomial q) {
    if(p.degree < q.degree)
        return Polynomial::monicPolyGCD(q, p);
    
    //*Make them monic
    Rational p_leading_coeff = p.get_leading_coefficient();
    Rational q_leading_coeff = q.get_leading_coefficient();

    PolyTerm term1, term2;
    term1.coeff = p_leading_coeff.invert();
    term1.exp = 0;
    term2.coeff = q_leading_coeff.invert();
    term2.exp = 0;
    Polynomial u = p.multiply_by_single_term_poly(term1);
    Polynomial v = q.multiply_by_single_term_poly(term2);
    // std::cout << "Term 1: " << term1.coeff << " x^" << term1.exp << "\n";
    // std::cout << "Term 2: " << term2.coeff << " x^" << term2.exp << "\n";
    // std::cout << "Monic u: " << u << "\n";
    // std::cout << "Monic v: " << v << "\n";
    // std::cout << v.degree << "\n";

    while(v.getDegree() > 0) {
        Polynomial r = Polynomial::remainder(u, v);
        // std::cout << "r: " << r << "\n";
        Rational r_leading_coeff = r.get_leading_coefficient();

        PolyTerm term3;
        term3.coeff = r_leading_coeff.invert();
        term3.exp = 0;
        u = v;
        v = r.multiply_by_single_term_poly(term3);
    }
    if (v.isZero()){
        return u;
    }
    return Polynomial("1 0");
}

Integer Rational::getDenominator() const {return this->denominator;}
Integer Rational::getNumerator() const {return this->numerator;}