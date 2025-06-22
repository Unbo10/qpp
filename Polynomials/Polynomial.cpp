#include <bits/stdc++.h>

#include "Polynomial.h"
#include "../include/Rational.h"

Polynomial::Polynomial(PolyTerm& term) {
    dense = std::vector<Rational>(term.exp);
    degree = term.exp;
    sparse.push_back(term);
    if((term.coeff.getDenominator() != 1) || (term.coeff.getDenominator() != -1))
        is_rational = true;
    is_dense_valid = true;
    is_sparse_valid = true;
}

Polynomial::Polynomial(const std::string& str) { *this = str; }
    
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
    if(is_dense_valid) {
        for(const auto& coeff : dense) {
            if(coeff != Rational(0)) return false;
        }
    }
    else {
        for(const auto& term : sparse) {
            if(term.coeff != Rational(0)) return false;
        }
    }
    return true;
}

//*Sorts them in descending order (greatest to smallest exponent)
void Polynomial::order_poly() {
    if(is_ordered) return;

    std::sort(sparse.begin(), sparse.end(), 
        [](const PolyTerm& a, const PolyTerm& b) {
            return a.exp > b.exp;
        });

is_ordered = true;
}

Rational Polynomial::get_leading_coefficient() const { return this->sparse[0].coeff; }

//***OSTREAM AND ISTREAM***

Polynomial Polynomial::operator=(const Polynomial& other) {
    degree = other.degree;
    dense = other.dense;
    sparse = other.sparse;
    is_dense_valid = other.is_dense_valid;
    is_ordered = other.is_ordered;
    is_rational = other.is_rational;
    is_sparse_valid = other.is_sparse_valid;
    return *this;
}

Polynomial Polynomial::operator=(std::string str) {
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

    order_poly();
    dense = std::vector<Rational>(degree);
    degree = sparse[0].exp;  // The first term is the one with the greatest exponent

    // Generate dense representation from sparse
    int deg = degree;
    int i = 0;
    while (deg != -1){
        if (deg == sparse[i].exp){
            dense.push_back(sparse[i].coeff);
            i++;
        }
        else {
            dense.push_back(Rational(0));
        }
        deg--;
    }
    is_dense_valid = true;
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

    if(poly.is_dense_valid) {
        os << "Dense representation: ";
        for (const auto& coeff : poly.dense) {
            os << coeff << " ";
        }
        os << "\n";
    }
    else{
        int n = poly.sparse.size();

        for(int i = 0; i < n; i++) {
            os << poly.sparse[i];
            if(i < n - 1) os << " + ";
        }
    }
    return os;
}

//***COMPARISON OPERATIONS***

// std::istream& operator>>(std::istream& is, const Polynomial& other) {

// }

//***ARITHMETIC OPERATIONS***

Polynomial Polynomial::multiply_by_single_term_poly(const PolyTerm& singleTerm) {
    this->order_poly();
    if((singleTerm.coeff == 0)) {
        Polynomial result;
        result.sparse.push_back(PolyTerm(0, 0));
        return result;
    }
    if((singleTerm.coeff == 1) && (singleTerm.exp == 0)) return *this;

    int n = this->sparse.size();
    Polynomial prod;
    PolyTerm prodTerm;

    for(int i = 0; i < n; i++) {
        prodTerm = this->sparse[i] * singleTerm;
        prod.sparse.push_back(prodTerm);
    }
    prod.is_ordered = true;
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
                std::cout << "NewTerm: " << newTerm.coeff << "\n";
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
    std::cout << "Size: " << result.sparse.size() << "\n";
    if((int)result.sparse.size() == 0) {
        PolyTerm zeroTerm;
        zeroTerm.coeff = 0;
        zeroTerm.exp = 0;
        result.sparse.push_back(zeroTerm);
    }

    return result;
}

Polynomial operator+(const Polynomial& poly, PolyTerm& term) {
    Polynomial newPoly(term);
    return poly + newPoly;
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

Polynomial Polynomial::operator/(const Polynomial& other) {
    if(other.isZero()) throw std::invalid_argument("Cannot divide by zero polynomial");
    if(other.degree > this->degree) return Polynomial("0 0"); // Return zero polynomial if divisor degree is greater than dividend degree

    Polynomial u = *this;
    Polynomial r = u;
    Polynomial q;
    q.dense = std::vector<Rational>(degree - other.degree + 1);
    // std::cout << q.dense.size() << " VS " << degree - other.degree << "\n";
    // std::cout.flush();

    for(int i = 0; i <= u.degree - other.degree; i++){
        q.dense[i] = r.dense[i] / other.dense[0];
        for(int j = 0; j <= other.degree ; j++){
            r.dense[i + j] = r.dense[i+j] - (q.dense[i] * other.dense[j]);
        }
    }
    q.update_sparse();
    q.update_dense();
    r.update_sparse();
    return r;
}

//***RATIONAL POLYNOMIALS***

Polynomial Polynomial::remainder(const Polynomial& divisor) const {
    Polynomial u = *this;
    Polynomial r, q;
    r = u;
    q.dense.resize(u.degree - divisor.degree + 1, Rational(0));

    for(int i = 0; i <= u.degree - divisor.degree; i++){
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
        r.degree = 0;
    } else {
        r.update_dense();
    }
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

    Polynomial r = u_prime_scaled.remainder(v_prime);
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
    Polynomial r = pseudoremainder(u_primitive ,v_primitive);
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
        r = pseudoremainder(u_primitive, v_primitive);
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
    //make them monic
    Rational p_leading_coeff = p.get_leading_coefficient();
    Rational q_leading_coeff = q.get_leading_coefficient();

    PolyTerm term1, term2;
    term1.coeff = Rational(p_leading_coeff.getDenominator() , p_leading_coeff.getNumerator());
    term1.coeff.setSign(p_leading_coeff.getSign());
    term1.exp = 0;
    term2.coeff = Rational(q_leading_coeff.getDenominator() , q_leading_coeff.getNumerator());
    term2.coeff.setSign(q_leading_coeff.getSign());
    term2.exp = 0;
    Polynomial u = p.multiply_by_single_term_poly(term1);
    Polynomial v = q.multiply_by_single_term_poly(term2);

    while(v.getDegree() > 0) {
        Polynomial r = u.remainder(v);
        Rational r_leading_coeff = r.get_leading_coefficient();

        PolyTerm term3;
        term3.coeff = Rational(r_leading_coeff.getDenominator() , r_leading_coeff.getNumerator());
        term3.coeff.setSign(r_leading_coeff.getSign());
        term3.exp = 0;
        u = v;
        v = r.multiply_by_single_term_poly(term3);
    }
    if (v.isZero()){
        return u;
    }
    return Polynomial("1 0");
}