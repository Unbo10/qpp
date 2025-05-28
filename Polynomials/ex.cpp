#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <algorithm>
#include <sstream>
#include <cmath>

class Polynomial {
private:
    std::vector<double> dense;  // Dense representation: coefficients indexed by power
    std::vector<std::pair<double, int>> sparse;  // Sparse representation: [coefficient, power] pairs
    bool is_dense_valid = false;
    bool is_sparse_valid = false;
    int max_degree = 0;

public:
    // Parse polynomial from string
    void parseFromString(const std::string& poly_str) {
        clear();
        std::map<int, double> terms;
        
        // Clean the string: remove spaces and handle signs
        std::string cleaned = poly_str;
        cleaned.erase(std::remove(cleaned.begin(), cleaned.end(), ' '), cleaned.end());
        
        // Add '+' at the beginning if it doesn't start with '+' or '-'
        if (!cleaned.empty() && cleaned[0] != '+' && cleaned[0] != '-') {
            cleaned = "+" + cleaned;
        }
        
        // Regular expression to match terms like +3x^4, -2x^2, +5x, -7, etc.
        std::regex term_regex(R"([+-](?:\d*\.?\d*)?(?:x(?:\^-?\d+)?)?)");
        
        std::sregex_iterator iter(cleaned.begin(), cleaned.end(), term_regex);
        std::sregex_iterator end;
        
        for (; iter != end; ++iter) {
            std::string term = iter->str();
            if (term.empty() || term == "+" || term == "-") continue;
            
            double coeff = 0;
            int power = 0;
            
            // Parse coefficient and power
            if (term.find('x') == std::string::npos) {
                // Constant term
                coeff = std::stod(term);
                power = 0;
            } else {
                // Term with x
                size_t x_pos = term.find('x');
                
                // Extract coefficient
                std::string coeff_str = term.substr(0, x_pos);
                if (coeff_str == "+" || coeff_str.empty()) {
                    coeff = 1;
                } else if (coeff_str == "-") {
                    coeff = -1;
                } else {
                    coeff = std::stod(coeff_str);
                }
                
                // Extract power
                if (x_pos + 1 < term.length() && term[x_pos + 1] == '^') {
                    power = std::stoi(term.substr(x_pos + 2));
                } else {
                    power = 1;  // Just 'x' means x^1
                }
            }
            
            // Add to terms map (combining like terms)
            terms[power] += coeff;
            max_degree = std::max(max_degree, power);
        }
        
        // Convert to sparse representation
        for (const auto& term : terms) {
            if (term.second != 0) {  // Only store non-zero coefficients
                sparse.push_back({term.second, term.first});
            }
        }
        
        // Sort sparse representation by power (descending)
        std::sort(sparse.begin(), sparse.end(), 
                  [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
                      return a.second > b.second;
                  });
        
        is_sparse_valid = true;
        generateDense();
    }
    
    // Generate dense representation from sparse (stored in descending order of powers)
    void generateDense() {
        if (!is_sparse_valid) return;
        
        dense.clear();
        dense.resize(max_degree + 1, 0.0);
        
        for (const auto& term : sparse) {
            if (term.second >= 0 && term.second <= max_degree) {
                // Store in descending order: index 0 = highest power, index max_degree = constant term
                dense[max_degree - term.second] = term.first;
            }
        }
        
        is_dense_valid = true;
    }
    
    // Generate sparse representation from dense (dense is in descending order)
    void generateSparse() {
        if (!is_dense_valid) return;
        
        sparse.clear();
        for (int i = 0; i < static_cast<int>(dense.size()); ++i) {
            if (dense[i] != 0) {
                // Convert from descending order index to actual power
                int power = max_degree - i;
                sparse.push_back({dense[i], power});
            }
        }
        
        is_sparse_valid = true;
    }
    
    // Get maximum degree of the polynomial
    int getMaxDegree() {
        return max_degree;
    }

    // Get dense representation
    std::vector<double> getDense() {
        if (!is_dense_valid) generateDense();
        return dense;
    }
    
    // Get sparse representation
    std::vector<std::pair<double, int>> getSparse() {
        if (!is_sparse_valid) generateSparse();
        return sparse;
    }
    
    // Print dense representation
    void printDense() {
        if (!is_dense_valid) generateDense();
        
        std::cout << "Dense representation: [";
        for (size_t i = 0; i < dense.size(); ++i) {
            std::cout << dense[i];
            if (i < dense.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    // Print sparse representation
    void printSparse() {
        if (!is_sparse_valid) generateSparse();
        
        std::cout << "Sparse representation: [";
        for (size_t i = 0; i < sparse.size(); ++i) {
            std::cout << "[" << sparse[i].first << ", " << sparse[i].second << "]";
            if (i < sparse.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    // Print the polynomial in standard mathematical form
    void printPolynomial() {
        if (!is_sparse_valid) generateSparse();
        
        if (sparse.empty()) {
            std::cout << "0" << std::endl;
            return;
        }
        
        std::cout << "Polynomial: ";
        bool first = true;
        
        for (const auto& term : sparse) {
            double coeff = term.first;
            int power = term.second;
            
            // Handle sign
            if (!first) {
                std::cout << (coeff >= 0 ? " + " : " - ");
                coeff = std::fabs(coeff);
            } else if (coeff < 0) {
                std::cout << "-";
                coeff = std::fabs(coeff);
            }
            
            // Handle coefficient
            if (power == 0 || coeff != 1) {
                std::cout << coeff;
            }
            
            // Handle variable and power
            if (power > 0) {
                std::cout << "x";
                if (power > 1) {
                    std::cout << "^" << power;
                }
            }
            
            first = false;
        }
        std::cout << std::endl;
    }
    
    void clear() {
        dense.clear();
        sparse.clear();
        is_dense_valid = false;
        is_sparse_valid = false;
        max_degree = 0;
    }
};

// int main() {
//     Polynomial poly;
    
//     // Test examples
//     std::vector<std::string> test_cases = {
//         "3x^4 + 2x^2 - 1",
//         "x^3 - 2x + 5",
//         "2x^5 - x^4 + 3x^2 - 7x + 1",
//         "-x^2 + 4x - 3",
//         "5",
//         "x",
//         "-x^3"
//     };
    
//     for (const std::string& test : test_cases) {
//         std::cout << "\n" << std::string(50, '=') << std::endl;
//         std::cout << "Input: \"" << test << "\"" << std::endl;
//         std::cout << std::string(50, '=') << std::endl;
        
//         poly.parseFromString(test);
//         poly.printPolynomial();
//         poly.printDense();
//         poly.printSparse();
//     }
    
//     // Interactive mode
//     std::cout << "\n" << std::string(50, '=') << std::endl;
//     std::cout << "Interactive Mode (enter 'quit' to exit)" << std::endl;
//     std::cout << std::string(50, '=') << std::endl;
    
//     std::string input;
//     while (true) {
//         std::cout << "\nEnter a polynomial: ";
//         std::getline(std::cin, input);
        
//         if (input == "quit" || input == "exit") {
//             break;
//         }
        
//         if (input.empty()) {
//             continue;
//         }
        
//         try {
//             poly.parseFromString(input);
//             poly.printPolynomial();
//             poly.printDense();
//             poly.printSparse();
//         } catch (const std::exception& e) {
//             std::cout << "Error parsing polynomial: " << e.what() << std::endl;
//         }
//     }
    
//     return 0;
// }