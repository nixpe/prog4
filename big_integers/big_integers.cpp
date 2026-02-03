#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class BigInt {
private:
    string digits;

    static string strip(const string& s) {
        int i = 0;
        while (i < (int)s.size() && s[i] == '0') {
            ++i;
        }
        if (i == (int)s.size()) {
            return "0";
        }
        return s.substr(i);
    }

    static int compare(const string& a, const string& b) {
        if (a.size() != b.size()) {
            return (a.size() < b.size()) ? -1 : 1;
        }
        if (a == b) {
            return 0;
        }
        return (a < b) ? -1 : 1;
    }

public:
    BigInt() : digits("0") {}

    BigInt(string value) {
        digits = strip(value);
    }

    string getValue() const {
        return digits;
    }

    BigInt operator+(const BigInt& other) const {
        int i = digits.size() - 1;
        int j = other.digits.size() - 1;
        int carry = 0;
        string result;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += digits[i--] - '0';
            if (j >= 0) sum += other.digits[j--] - '0';
            result.push_back(char('0' + sum % 10));
            carry = sum / 10;
        }

        reverse(result.begin(), result.end());
        return BigInt(strip(result));
    }

    BigInt operator-(const BigInt& other) const {
        int i = digits.size() - 1;
        int j = other.digits.size() - 1;
        int borrow = 0;
        string result;

        while (i >= 0) {
            int diff = (digits[i--] - '0') - borrow;
            if (j >= 0) diff -= other.digits[j--] - '0';

            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.push_back(char('0' + diff));
        }

        reverse(result.begin(), result.end());
        return BigInt(strip(result));
    }

    BigInt operator*(const BigInt& other) const {
        if (digits == "0" || other.digits == "0") {
            return BigInt("0");
        }

        string result(digits.size() + other.digits.size(), '0');

        for (int i = digits.size() - 1; i >= 0; --i) {
            int carry = 0;
            for (int j = other.digits.size() - 1; j >= 0; --j) {
                int index = i + j + 1;
                int sum =
                    (digits[i] - '0') * (other.digits[j] - '0') +
                    (result[index] - '0') + carry;

                result[index] = char('0' + sum % 10);
                carry = sum / 10;
            }
            result[i] += carry;
        }

        return BigInt(strip(result));
    }

    BigInt operator/(const BigInt& other) const {
        string quotient;
        string remainder = "0";

        for (char c : digits) {
            remainder = strip(remainder + c);

            int q = 0;
            while (compare(remainder, other.digits) >= 0) {
                remainder = (BigInt(remainder) - BigInt(other.digits)).digits;
                ++q;
            }

            quotient.push_back(char('0' + q));
        }

        return BigInt(strip(quotient));
    }

    BigInt operator%(const BigInt& other) const {
        BigInt quotient = (*this) / other;
        BigInt product = quotient * other;
        return (*this) - product;
    }
};

int main() {
    BigInt a("123456789123456789");
    BigInt b("12345");

    cout << (a + b).getValue() << endl;
    cout << (a - b).getValue() << endl;
    cout << (a * b).getValue() << endl;
    cout << (a / b).getValue() << endl;
    cout << (a % b).getValue() << endl;

    return 0;
}
