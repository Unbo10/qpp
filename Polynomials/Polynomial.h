#pragma once

#include <iostream>
#include <vector>

#include "PolyTerm.h"

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

    Polynomial();

    Polynomial(PolyTerm& term);

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
    int getDegree();

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
    void printPolynomial();
    
    void clear();

    //***UTILS***

    //*Sorts them in descending order (greatest to smallest exponent)
    void order_poly();

    //***OSTREAM AND ISTREAM***

    Polynomial operator=(const Polynomial& other);

    Polynomial operator=(std::string str);

    Polynomial update_sparse();

    friend std::istream& operator>>(std::istream& is, Polynomial& poly);

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);

    //***COMPARISON OPERATIONS***

    // std::istream& operator>>(std::istream& is, const Polynomial& other) {

    // }

    //***ARITHMETIC OPERATIONS***

    Polynomial multiply_by_single_term_poly(const PolyTerm& singleTerm);

    Polynomial multiply_by_single_term_poly(const Polynomial& singleTerm);

    Polynomial operator+(const Polynomial& other) const;

    Polynomial to_integer_poly();

    //*For integer polynomials
    Integer find_gcd_of_poly_terms();

    Integer find_lcm_of_poly_terms();

    Polynomial operator/(const Polynomial& other);

    std::pair<Polynomial, Polynomial> divide_by(const Polynomial& divisor) const;

    Polynomial pseudoquotient(Polynomial u, Polynomial v);

    Polynomial pseudoremainder(Polynomial u, Polynomial v);
};