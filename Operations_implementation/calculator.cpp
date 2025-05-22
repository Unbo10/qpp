#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "calculator.h"

using namespace std;

Calculator::Calculator(){}

void Calculator::print_vector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << "\n";
}

int Calculator::mod(int num, int b) {
    int modulo = num % b;
    if (modulo >= 0) {
        return modulo;
    }
    else {
        return b - abs(modulo);
    }
}

int Calculator::convert_to_integer(std::vector<int> v, int b) {
    int v_int;
    int v_size = int(v.size());
    for (int i = 0; i < v_size; i++) {
        v_int += v[i] * pow(b, v_size - 1 - i);
    }
    return v_int;
}

std::vector<int> Calculator::convert_to_vector(int num) {
    std::vector<int> digits;
    if (num == 0) {
        digits.push_back(0);
        return digits;
    }

    while (num > 0) {
        digits.insert(digits.begin(), num % 10);
        num /= 10;
    }
    return digits;
}

std::vector<int> Calculator::convert_to_b10(int num, int b) {
    int num_len = 0;
    int num_copy = num;
    while (num_copy >= 1) {
        num_copy /= 10;
        num_len++;
    }
    
    std::vector<int> num_arr;
    int i = num_len - 1;
    while (num >= 1) {
        num_arr.insert(num_arr.begin(), num % 10);
        num /= 10;
        i--;
    }
    // for (int i = 0; i < num_len; i++) {
    //     cout << num_arr[i] << " ";
    // }
    // cout << "\n";
    return convert_to_b10(num_arr, num_len, b);
}

std::vector<int> Calculator::convert_to_b10(std::vector<int> num, int num_len, int b) {
    int num_base10 = 0;
    for (int i = 0; i < num_len; i++) {
        num_base10 += num[i] * pow(b, num_len - 1 - i); //* digit * (b**i)
    }

    std::vector<int> num_base10_arr;
    
    // Convert the base-10 number to an array of digits
    while (num_base10 >= 1) {
        num_base10_arr.insert(num_base10_arr.begin(), num_base10 % 10);
        num_base10 /= 10;
    }
    // for (int i = 0; i < num_len; i++) {
    //     cout << num_base10_arr[i] << " ";
    // }
    // cout << "\n";

    return num_base10_arr;
}

std::vector<int> Calculator::add_zeros(std::vector<int> num, int zeros) {
    if (zeros > 0) {
        for (int i = 0; i < zeros; i++) {
            num.insert(num.begin(), 0);
        }
        return num;
    }
    else {
        return num;
    }
}

std::vector<int> Calculator::trim_zeros(std::vector<int> v, int min_length = -1) {
    int zeros = 0;
    int v_size = int(v.size()); //7
    bool found_non_zero = false;

    while ((zeros < v_size) && (found_non_zero == false)) {
        if (zeros == v_size - 1) {
            found_non_zero = true;
        }
        else if (v[zeros] != 0) {
            found_non_zero = true;
        }
        else{
            zeros++; //5
        }
    }

    int new_v_length = 0;
    if (min_length != -1) {
        if ((min_length > v_size - zeros) && min_length <= v_size) {
            new_v_length = min_length;
            zeros = v_size - min_length;
        }
        else {
            new_v_length = v_size - zeros;
        }
    }
    else {
        new_v_length = v_size - zeros; //3
    }
    std::vector<int> new_v(new_v_length);

    for (int i = 0; i < new_v_length; i++) {
        new_v[i] = v[i + zeros];
    }    

    return new_v;
}

void Calculator::pretty_print_operation(
    const std::vector<int>& a, 
    const std::vector<int>& b, 
    const std::vector<int>& result, 
    char op)
{
    string str_a, str_b, str_result;
    for (int d : a) {
        str_a += to_string(d);
    }
    for (int d : b) {
        str_b += to_string(d);
    }
    for (int d : result) {
        str_result += to_string(d);
    }
    
    // Determine total width:
    // For the second line we print an operator before b, so add 1 to b's size.
    int width = max({ static_cast<int>(str_result.size()), 
                       static_cast<int>(str_a.size()), 
                       static_cast<int>(str_b.size()) + 1 }) + 1;
    
    // Print the first operand right-aligned
    cout << string(width - str_a.size(), ' ') << str_a << "\n";
    
    // Print the second operand with the operator in front; right-aligned afterward.
    cout << op << string(width - str_b.size() - 1, ' ') << str_b << "\n";
    
    // Print a separator line
    cout << string(width, '~') << "\n";
    
    // Print the result right-aligned
    cout << string(width - str_result.size(), ' ') << str_result << "\n";
}

std::vector<int> Calculator::add(int n, int m, int b) {
    if (n > m) {
        return add(convert_to_vector(n), convert_to_vector(m), b);
    }
    else {
        return add(convert_to_vector(m), convert_to_vector(n), b);
    }
}

std::vector<int> Calculator::add(std::vector<int> n, std::vector<int> m, int b) {
    //*n >= m
    int zeros = int(n.size()) - int(m.size());
    m = add_zeros(m, zeros);
    // print_vector(n);
    // print_vector(m);

    std::vector<int> res(n.size() + 1);
    int k = 0; //*Carry
    // cout << "Size " << int(n.size()) + 1 << "\n";
    // cout << int(n.size()) - 1 + int(res.size()) - int(n.size()) << "\n";
    for (int i = int(n.size()) - 1; i >= 0; i--) {
        res[i + int(res.size()) - int(n.size())] = (n[i] + m[i] + k) % b;
        // cout << (n[i] + m[i] + k) % b << "\n";
        if (n[i] + m[i] + k >= b) {
            k = 1;
        }
        else {
            k = 0;
        }
    }
    res[0] = k;
    // print_vector(res);
    // pretty_print_operation(n, m, res, '+');

    return res;
}

std::vector<int> Calculator::subtract(int n, int m, int b) {
    if (n < m) {
        return subtract(convert_to_vector(m), convert_to_vector(n), b);
    }
    else {
        return subtract(convert_to_vector(n), convert_to_vector(m), b);
    }
}

std::vector<int> Calculator::subtract(std::vector<int> n, std::vector<int> m, int b) {
    int k = 0; //*Carry (0 or -1);
    int zeros = int(n.size()) - int(m.size());
    m = add_zeros(m, zeros);
    std::vector<int> w(n.size());

    for (int i = int(n.size()) - 1; i >= 0; i--) {
        w[i] = mod(n[i] - m[i] + k, b); //*w.size - n.size = 0
        if (n[i] - m[i] + k < 0) {
            k = -1;
        }
        else {
            k = 0;
        }
    }

    // pretty_print_operation(n, m, w, '-');
    return w;
}

std::vector<int> Calculator::multiply(int n, int m, int b) {
    if (n < m) {
        return multiply(convert_to_vector(m), convert_to_vector(n), b);
    }
    else {
        return multiply(convert_to_vector(n), convert_to_vector(m), b);
    }
}

std::vector<int> Calculator::multiply(std::vector<int> n, std::vector<int> m, int b) {
    int zeros = int(n.size()) - int(m.size());
    m = add_zeros(m, zeros);
    int n_len = int(n.size());
    int m_len = int(m.size());
    int k = 0; //*Carry
    int t = 0;
    std::vector<int> w(n_len + m_len); //*Last position will be n_len + m_len - 1

    //   n
    // * m
    for (int i = m_len - 1; i >= 0; i--) {
        if (m[i] != 0) {
            k = 0;
            for(int j = n_len - 1; j >= 0; j--) {
                t = w[i + j + 1] + (n[j] * m[i]) + k;
                w[i + j + 1] = t % b;
                // cout << "At i=" << i << ", j=" << j << ": w[" << i+j+1 << "]=" << w[i+j+1]
                // << ", n[" << j << "]=" << n[j] << ", m[" << i << "]=" << m[i]
                // << ", k=" << k << ", t=" << t << endl;
                k = t/b;
            }
            w[i] = k; //!Check - 1
            // cout << "At i=" << i << ": w[" << i << "]=" << w[i]
            // << ", k=" << k << "\n";
        }
    }

    // pretty_print_operation(n, m, w, 'x');
    return w;
}

int Calculator::real_len(const std::vector<int> v) {
    // cout << 
    print_vector(v);
    int i = 0;
    int left_zeros = 0;
    while (v[i] == 0) {
        left_zeros++;
        i++;
    }   
    cout << "len: " << v.size() - left_zeros << "\n";
    return v.size() - left_zeros;
}

int Calculator::minimize_greatest_power(std::vector<int> a) {
    int num_digits = int(a.size());
    int exp = 0; //*Exponent
    while (pow(2, exp) < num_digits) {
        exp += 1;
    }
    return pow(2, exp);
}

std::vector<int> Calculator::split_vector(std::vector<int> v, const char half) {
    int v_size = int(v.size());
    std::vector<int> v_half(v_size/2);
    if (half == 'l') {
        for (int i = 0; i < v_size / 2; i++) {
            v_half[i] = v[i];
        }
    }
    else if (half == 'r') {
        for (int i = v_size / 2; i < v_size; i++) {
            v_half[i] = v[i];
        }
    }
    return v_half;
}

std::vector<int> Calculator::karatsuba_m(int n, int k, int b) {
    if (n < k) {
        return karatsuba_m(convert_to_vector(k), convert_to_vector(n), b, false);
    }
    else {
        return karatsuba_m(convert_to_vector(n), convert_to_vector(k), b, false);
    }
}

std::vector<int> Calculator::karatsuba_m(std::vector<int> n, std::vector<int> k, int b, bool balanced) {
    if (!balanced) {
        int n_zeros = minimize_greatest_power(n) - int(n.size());
        n = add_zeros(n, n_zeros);
        int k_zeros = minimize_greatest_power(k) - int(k.size());
        k = add_zeros(k, k_zeros);
    }
    else {
        if (n.size() == 1) {

        }
        else {
            //* n * k = m2 + (m1 - m2 - m3) + m3
            //* m1 = (n1 + n0)(k1 + k0)
            //* m2 = n1 * k1
            //* m3 = n0 * k0
            std::vector<int> n1 = split_vector(n, 'l');
            std::vector<int> n0 = split_vector(n, 'r');
            std::vector<int> k1 = split_vector(k, 'l');
            std::vector<int> k0 = split_vector(k, 'r');
            // return karatsuba_m( , true);
            //! Issue with the b^2
            //! Maybe we don't need to literally split the vector. Instead, we could fill it with zeros on one of the two ends and find a way to track whether it's a left half or a right one. A new object may be required.
        }
    }
    return n;
}

std::vector<int>* Calculator::divide(int u, int v, int b) {
    if (u < v) {
        std::vector<int>* q_and_r = new std::vector<int>[2];
        //*The divisor is bigger than the dividend, so the quotient is 0 and the remainder is the dividend
        q_and_r[0] = convert_to_vector(0);
        q_and_r[1] = convert_to_vector(u);
        return q_and_r;
    }
    //!A brief conditional could be added to determine whether the size of the quotient has to be n or n + 1. That way, we would guarantee it is at least 1 (think of the test as computing (b-1, b-1, ..., b-1) n-times and multiplying it by the divisor. If it is smaller than the number being devided + divisor, then it has length n - 1. Otherwise, it has length n)
    if (u == v) {
        std::vector<int>* q_and_r = new std::vector<int>[2];
        //*The divisor is bigger than the dividend, so the quotient is 0 and the remainder is the dividend
        q_and_r[0] = convert_to_vector(1);
        q_and_r[1] = convert_to_vector(0);
        return q_and_r;
    }
    else {
        return divide(convert_to_vector(u), convert_to_vector(v), b);
    }
}

std::vector<int>* Calculator::divide(std::vector<int> u, std::vector<int> v, int b) {
    int u_size = int(u.size());
    int v_size = int(v.size());

    //*Normalize vectors
    std::vector<int> d = convert_to_vector(b / (v[0] + 1));
    std::vector<int> nu = trim_zeros(multiply(u, d, b)); //*Normalized u or u'
    print_vector(nu);
    std::vector<int> nv = trim_zeros(multiply(v, d, b)); //*Normalized v or v'
    std::vector<int> comparison_nv = add_zeros(nv, 1); //*Will have the same length as u_hat
    print_vector(nv);
    
    //*Initialize u-hat, which will take the first v_size digits of nu (no need for left-padding).
    std::vector<int> u_hat = std::vector<int>(v_size + 1); //!This size may not be correct
    for (int i = 0; i < v_size + 1; i++) {
        u_hat[i] = nu[i];
    }
    std::vector<int> w;

    //*Initialize the quotient and the reminder
    std::vector<int> q = std::vector<int>(u_size - v_size + 1); //! + 1
    std::vector<int> r = std::vector<int>(v_size);

    int correction = 0;
    if (u_hat[0] >= nv[0]) {
        // print_vector(u_hat);
        u_hat = add_zeros(u_hat, 1);
        u_hat.pop_back();
        correction = 1;
        // cout << "Modofied u_hat\n";
        // print_vector(u_hat);
        // cout << "\n";
    }

    for (int j = 0; j <= v_size + 1; j++) { //!May be < and not <=
        //TODO: Check the subscripts -they may vary in the current implementation
        //*Instead of n and n - 1, it is respectively m and 0
        if (u_hat[0] == nv[0]) {
            q[j] = b - 1;
        }
        else {
            q[j] = (u_hat[0] * b + u_hat[1]) / nv[0];
            cout << "Trial quotient: " << q[j] << "\n";
            // cout << u_hat[0] << "\n";
            // cout << u_hat[1] << "\n";
            // cout << nv[0] << "\n";
        }
        w = multiply(convert_to_vector(q[j]), nv, b);
        pretty_print_operation(convert_to_vector(q[j]), nv, w, '*');
        w = trim_zeros(w);
        w = add_zeros(w, v_size + 1 - int(w.size()));
        // cout << real_len(v);
        cout << "w:\n";
        print_vector(w);
        print_vector(u_hat);
        // cout << "\n";
        // print_vector(w);
        while (w > u_hat) {
            cout << "q and u_hat comparison: " << (w > u_hat) << "\n";
            //*At most two iterations
            q[j]--;
            w = subtract(w, nv, b);
        }
        w = trim_zeros(w);
        r = subtract(u_hat, w, b);
        pretty_print_operation(u_hat, w, r, '-');
        // cout << "w:\n";
        // print_vector(w);
        // cout << "r: \n";
        // print_vector(r);
        if (j < v_size + 1) {
            u_hat = add(trim_zeros(multiply(r, convert_to_vector(b), b)), convert_to_vector(nu[(v_size + 1) + j - correction]), b); //! Not adding correctly
            u_hat = trim_zeros(u_hat, v_size + 1);
            // cout << "u_hat: \n";
            // pretty_print_operation(trim_zeros(multiply(r, convert_to_vector(b), b)), convert_to_vector(nu[(v_size + 1) + j - correction]), u_hat, '+');
            // print_vector(u_hat);
        }
    }
    cout << "ddddd";
    print_vector(d);
    r = trim_zeros(r);
    if(r.size() > 1) {
        r = trim_zeros(divide(r, d, b)[0]);
    }

    //*Convert d and the remainder to integers (they both are less than or equal to b-1)
    int r_int = convert_to_integer(trim_zeros(r), b);

    std::vector<int>* q_and_r = new std::vector<int>[2];
    pretty_print_operation(u, v, q, '/');
    std::cout << "Remainder: " << r_int << "\n";
    print_vector(r);
    
    q_and_r[0] = q;
    q_and_r[1] = r;
    return q_and_r;
}