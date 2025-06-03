#pragma once

#include <bits/stdc++.h>

#include "../Numbers/Rational.h"
#include "../Polynomials/PolyTerm.cpp"

class Polynomial {
private:
    std::vector<Rational> dense;  // Dense representation: coefficients indexed by power
    std::vector<PolyTerm> sparse;  // Sparse representation: [coefficient, power] pairs
    bool is_dense_valid = false;
    bool is_ordered = false;
    bool is_rational = false;
    bool is_sparse_valid = false;
    int degree = 0;

public:

    Polynomial() {}

    Polynomial(PolyTerm& term) {
        dense = std::vector<Rational>(term.exp);
        degree = term.exp;
        sparse.push_back(term);
        if((term.coeff.getDenominator() != 1) || (term.coeff.getDenominator() != -1)) 
            is_rational = true;
        is_dense_valid = true;
        is_sparse_valid = true;
    }

    // // Parse polynomial from string
    // void parseFromString(const std::string& poly_str) {
    //     clear();
    //     std::map<int, double> terms;
        
    //     // Clean the string: remove spaces and handle signs
    //     std::string cleaned = poly_str;
    //     cleaned.erase(std::remove(cleaned.begin(), cleaned.end(), ' '), cleaned.end());
        
    //     // Add '+' at the beginning if it doesn't start with '+' or '-'
    //     if (!cleaned.empty() && cleaned[0] != '+' && cleaned[0] != '-') {
    //         cleaned = "+" + cleaned;
    //     }
        
    //     // Regular expression to match terms like +3x^4, -2x^2, +5x, -7, etc.
    //     std::regex term_regex(R"([+-](?:\d*\.?\d*)?(?:x(?:\^-?\d+)?)?)");
        
    //     std::sregex_iterator iter(cleaned.begin(), cleaned.end(), term_regex);
    //     std::sregex_iterator end;
        
    //     for (; iter != end; ++iter) {
    //         std::string term = iter->str();
    //         if (term.empty() || term == "+" || term == "-") continue;
            
    //         double coeff = 0;
    //         int power = 0;
            
    //         // Parse coefficient and power
    //         if (term.find('x') == std::string::npos) {
    //             // Constant term
    //             coeff = std::stod(term);
    //             power = 0;
    //         } else {
    //             // Term with x
    //             size_t x_pos = term.find('x');
                
    //             // Extract coefficient
    //             std::string coeff_str = term.substr(0, x_pos);
    //             if (coeff_str == "+" || coeff_str.empty()) {
    //                 coeff = 1;
    //             } else if (coeff_str == "-") {
    //                 coeff = -1;
    //             } else {
    //                 coeff = std::stod(coeff_str);
    //             }
                
    //             // Extract power
    //             if (x_pos + 1 < term.length() && term[x_pos + 1] == '^') {
    //                 power = std::stoi(term.substr(x_pos + 2));
    //             } else {
    //                 power = 1;  // Just 'x' means x^1
    //             }
    //         }
            
    //         // Add to terms map (combining like terms)
    //         terms[power] += coeff;
    //         degree = std::max(degree, power);
    //     }
        
    //     // Convert to sparse representation
    //     for (const auto& term : terms) {
    //         if (term.second != 0) {  // Only store non-zero coefficients
    //             sparse.push_back({term.second, term.first});
    //         }
    //     }
        
    //     // Sort sparse representation by power (descending)
    //     std::sort(sparse.begin(), sparse.end(), 
    //               [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
    //                   return a.second > b.second;
    //               });
        
    //     is_sparse_valid = true;
    //     generateDense();
    // }
    
    // // Generate dense representation from sparse (stored in descending order of powers)
    // void generateDense() {
    //     if (!is_sparse_valid) return;
        
    //     dense.clear();
    //     dense.resize(degree + 1, 0.0);
        
    //     for (const auto& term : sparse) {
    //         if (term.second >= 0 && term.second <= degree) {
    //             // Store in descending order: index 0 = highest power, index degree = constant term
    //             dense[degree - term.second] = term.first;
    //         }
    //     }
        
    //     is_dense_valid = true;
    // }
    
    // // Generate sparse representation from dense (dense is in descending order)
    // void generateSparse() {
    //     if (!is_dense_valid) return;
        
    //     sparse.clear();
    //     for (int i = 0; i < static_cast<int>(dense.size()); ++i) {
    //         if (dense[i] != 0) {
    //             // Convert from descending order index to actual power
    //             int power = degree - i;
    //             sparse.push_back({dense[i], power});
    //         }
    //     }
        
    //     is_sparse_valid = true;
    // }
    
    // Get maximum degree of the polynomial
    int getDegree() {
        return degree;
    }

    // // Get dense representation
    // std::vector<Rational> getDense() {
    //     if (!is_dense_valid) generateDense();
    //     return dense;
    // }
    
    // Get sparse representation
    // std::vector<PolyTerm> getSparse() {
    //     if (!is_sparse_valid) generateSparse();
    //     return sparse;
    // }
    
    // // Print dense representation
    // void printDense() {
    //     if (!is_dense_valid) generateDense();
        
    //     std::cout << "Dense representation: [";
    //     for (size_t i = 0; i < dense.size(); ++i) {
    //         std::cout << dense[i];
    //         if (i < dense.size() - 1) std::cout << ", ";
    //     }
    //     std::cout << "]" << std::endl;
    // }
    
    // // Print sparse representation
    // void printSparse() {
    //     if (!is_sparse_valid) generateSparse();
        
    //     std::cout << "Sparse representation: [";
    //     for (size_t i = 0; i < sparse.size(); ++i) {
    //         std::cout << "[" << sparse[i].first << ", " << sparse[i].second << "]";
    //         if (i < sparse.size() - 1) std::cout << ", ";
    //     }
    //     std::cout << "]" << std::endl;
    // }
    
    // Print the polynomial in standard mathematical form
    void printPolynomial() {
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
    
    void clear() {
        dense.clear();
        sparse.clear();
        is_dense_valid = false;
        is_sparse_valid = false;
        degree = 0;
    }

    //***UTILS***

    //*Sorts them in descending order (greatest to smallest exponent)
    void order_poly() {
        if(is_ordered) return;

        std::sort(sparse.begin(), sparse.end(), 
            [](const PolyTerm& a, const PolyTerm& b) {
                return a.exp > b.exp;
            });

        is_ordered = true;
    }

    //***OSTREAM AND ISTREAM***

    Polynomial operator=(const Polynomial& other) {
        degree = other.degree;
        dense = other.dense;
        sparse = other.sparse;
        is_dense_valid = other.is_dense_valid;
        is_ordered = other.is_ordered;
        is_rational = other.is_rational;
        is_sparse_valid = other.is_sparse_valid;
        return *this;
    }

    Polynomial operator=(std::string str) {
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
                    // std::cout << "Coefficient: " << tokens[i] << "\n";
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
            // std::cout << "Checkpoint 1. Num: " << num << ", den: " << den << "\n";
            Rational coeff(num, den);
            // std::cout << "Final coefficient: " << coeff << "\n";
            term.coeff = coeff;
            term.exp = std::stoi(tokens[i + 1]);
            sparse.push_back(term);
        }

        order_poly();
        dense = std::vector<Rational>(degree);
        degree = sparse[0].exp;  // The first term is the one with the greatest exponent
        //std::cout << "Degree: " << degree << " "<< sparse.size() << "\n";

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

    Polynomial update_sparse(){
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

    friend std::istream& operator>>(std::istream& is, Polynomial& poly) {
        std::string line;
        std::getline(is, line);
        if (!line.empty()) {
            poly = line;
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {

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

    Polynomial multiply_by_single_term_poly(const PolyTerm& singleTerm) {
        this->order_poly();
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

    Polynomial multiply_by_single_term_poly(const Polynomial& singleTerm) {
        if(singleTerm.sparse.size() != 1) throw std::invalid_argument("Polynomial is not a single-term polynomial; has " + std::to_string(singleTerm.sparse.size()) + " non-zero terms");

        return this->multiply_by_single_term_poly(singleTerm.sparse[0]);
    }

    Polynomial operator+(const Polynomial& other) const {
        int j = 0, i = 0, this_size = sparse.size(), other_size = other.sparse.size();
        Polynomial result;
        PolyTerm newTerm;

        while((i < this_size) && (j < other_size))
        {
            // std::cout << sparse[i].exp << " " << other.sparse[j].exp << "\n";
            if(sparse[i].exp > other.sparse[j].exp) {
                result.sparse.push_back(sparse[i]);
                i++;
            }
            else if (sparse[i].exp == other.sparse[j].exp) {
                newTerm.coeff = sparse[i].coeff + other.sparse[j].coeff;
                newTerm.exp = sparse[i].exp;
                result.sparse.push_back(newTerm);
                i++;
                j++;
            }
            else if (sparse[i].exp < other.sparse[j].exp){
                result.sparse.push_back(other.sparse[j]);
                j++;
            }
            // std::cout << result << "\n";
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

    Polynomial to_integer_poly() {
        //!NOT WORKING
        if(!is_rational) return *this;
        
        // Find the LCM of all denominators
        Integer lcm_den = 1;
        int n = sparse.size();
        
        for(int i = 0; i < n; i++) {
            Integer current_den = sparse[i].coeff.getDenominator();
            Integer gcd = Integer::binaryEuclidean(lcm_den, current_den);
            lcm_den = (lcm_den * current_den) / gcd;
        }
        
        Polynomial result;
        for(int i = 0; i < n; i++) {
            PolyTerm term = sparse[i];
            Integer factor = lcm_den / term.coeff.getDenominator();
            // std::cout << "FActor: " << factor << ", " << lcm_den << ", " << term.coeff.getDenominator() << "\n";
            term.coeff = (term.coeff.getNumerator() * factor) / 1;
            result.sparse.push_back(term);
        }
        
        result.is_ordered = is_ordered;
        result.is_rational = true;  // It's still rational, just with common denominator
        
        return result;
    }

    //*For integer polynomials
    Integer find_gcd_of_poly_terms() {
        if (sparse.size() < 2) return sparse[0].coeff.getNumerator();
        
        Integer gcd;
        gcd = Integer::binaryEuclidean(sparse[0].coeff.getNumerator(), sparse[1].coeff.getNumerator());
        // std::cout << "GCD of " << sparse[0].coeff.getNumerator() << ", " << sparse[1].coeff.getNumerator() << " is " << gcd << ", " << sparse.size() << "\n";
        for(int i = 2; i < (int)sparse.size(); i++) {
            // std::cout << "GCD: " << gcd << "\n";
            gcd = Integer::binaryEuclidean(gcd, sparse[i].coeff.getNumerator());
        }

        return gcd;
    }

    Integer find_lcm_of_poly_terms() {
        if (sparse.size() < 2) return sparse[0].coeff.getDenominator();
        
        Integer lcm = sparse[0].coeff.getDenominator();
        for(int i = 1; i < (int)sparse.size(); i++) {
            Integer current_den = sparse[i].coeff.getDenominator();
            Integer gcd = Integer::binaryEuclidean(lcm, current_den);
            lcm = (lcm * current_den) / gcd;
        }

        return lcm;
    }

    Polynomial operator/(const Polynomial& other) {
        Polynomial u = *this;
        Polynomial r = u;
        Polynomial q;
        q.dense = std::vector<Rational>(degree - other.degree + 1);
        std::cout << q.dense.size() << " VS " << degree - other.degree << "\n";
        std::cout.flush();

        for(int i = 0; i <= u.degree - other.degree; i++){
            std::cout << "i: " << i << ", r.dense[i]: " << r.dense[i] << ", other.dense[0]: " << other.dense[0] << "\n";
            q.dense[i] = r.dense[i] / other.dense[0];
            std::cout << "q.dense[" << i << "]: " << q.dense[i] << "\n";
            for(int j = 0; j <= other.degree ; j++){
                std::cout << "i: " << i << ", j: " << j << ", r.dense[i+j]: " << r.dense[i+j] << ", q.dense[i]: " << q.dense[i] << ", other.dense[j]: " << other.dense[j] << "\n";
                r.dense[i + j] = r.dense[i+j] - (q.dense[i] * other.dense[j]); 
                std::cout << "r.dense[" << i + j << "]: " << r.dense[i + j] << "\n";

            }
            std::cout << "Iteration " << i << "\n";
            std::cout << "q: " << q << "\n";
            std::cout << "r: " << r << "\n";

        }
        q.update_sparse();
        r.update_sparse();
        return q;
    }

    std::pair<Polynomial, Polynomial> divide_by(const Polynomial& divisor) const {
        Polynomial u = *this;
        Polynomial r, q;
        r = u;
        std::string q_str = "0 " + std::to_string(u.degree - divisor.degree);
        q = q_str;

        for(int i = 0; i <= u.degree - divisor.degree; i++){
            q.dense[i] = r.dense[i] / divisor.dense[0];
            for(int j = 0; j <= divisor.degree ; j++){
                r.dense[i + j] = r.dense[i+j] - (q.dense[i] * divisor.dense[j]); 
            }
        }
        q.update_sparse();
        r.update_sparse();
        return {q, r};
    }

    Polynomial pseudoquotient(Polynomial u, Polynomial v) {
        Integer beta = u.find_lcm_of_poly_terms();
        Integer gamma = v.find_gcd_of_poly_terms();
        PolyTerm term1, term2;
        term1.coeff = Rational(beta, 1);
        term1.exp = 0;
        term2.coeff = Rational(gamma, 1);
        term2.exp = 0;

        Polynomial u_prime = u.multiply_by_single_term_poly(term1);
        Polynomial v_prime = v.multiply_by_single_term_poly(term2);

        Integer alpha = v_prime.sparse[0].coeff.getDenominator()^Integer(u.getDegree() - v.getDegree() + 1);
        std::cout << "Alpha: " << alpha << "\n";

        PolyTerm term3;
        term3.coeff = Rational(alpha, 1);
        term3.exp = 0;

        Polynomial u_prime_scaled = u_prime.multiply_by_single_term_poly(term3);
        Polynomial q = u_prime_scaled / v_prime;

        PolyTerm term4;
        term4.coeff = Rational(gamma, beta * alpha);
        term4.exp = 0;

        Polynomial q_scaled = q.multiply_by_single_term_poly(term4);
        return q_scaled;
    }   

    Polynomial pseudoremainder(Polynomial u, Polynomial v) {
        Integer beta = u.find_lcm_of_poly_terms();
        Integer gamma = v.find_gcd_of_poly_terms();
        PolyTerm term1, term2;
        term1.coeff = Rational(beta, 1);
        term1.exp = 0;
        term2.coeff = Rational(gamma, 1);
        term2.exp = 0;

        Polynomial u_prime = u.multiply_by_single_term_poly(term1);
        Polynomial v_prime = v.multiply_by_single_term_poly(term2);

        Integer alpha = v_prime.sparse[0].coeff.getDenominator()^Integer(u.getDegree() - v.getDegree() + 1);
        std::cout << "Alpha: " << alpha << "\n";

        PolyTerm term3;
        term3.coeff = Rational(alpha, 1);
        term3.exp = 0;

        Polynomial u_prime_scaled = u_prime.multiply_by_single_term_poly(term3);
        Polynomial r = u_prime_scaled.divide_by(v_prime).second;

        return r;
    } 
};