#include <iostream>
#include <string>
#include <algorithm>

// Function to add 
std::string addBigIntegers(const std::string& num1, const std::string& num2) {
    std::string result = "";
    int carry = 0;
    int n1 = num1.size();
    int n2 = num2.size();
    
    int lengthDifference = abs(n1 - n2);
    std::string num1Modified = (n1 < n2) ? std::string(lengthDifference, '0') + num1 : num1;
    std::string num2Modified = (n2 < n1) ? std::string(lengthDifference, '0') + num2 : num2;

    for (int i = num1Modified.size() - 1; i >= 0; i--) {
        int digit1 = num1Modified[i] - '0';
        int digit2 = num2Modified[i] - '0';
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result += (sum % 10) + '0';
    }
    if (carry) {
        result += carry + '0';
    }
    std::reverse(result.begin(), result.end());
    return result;
}

// Function to subtract 
std::string subtractBigIntegers(const std::string& num1, const std::string& num2) {
    std::string result = "";
    int borrow = 0;
    int n1 = num1.size();
    int n2 = num2.size();
    int lengthDifference = abs(n1 - n2);
    std::string num1Modified = num1;
    std::string num2Modified = std::string(lengthDifference, '0') + num2;
    for (int i = num1Modified.size() - 1; i >= 0; i--) {
        int digit1 = num1Modified[i] - '0';
        int digit2 = num2Modified[i] - '0' + borrow;
        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result += (digit1 - digit2) + '0';
    }
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }
    std::reverse(result.begin(), result.end());
    return result;
}

// Function to multiply
std::string multiplyBigIntegers(const std::string& num1, const std::string& num2) {
    int n1 = num1.size();
    int n2 = num2.size();
    std::string result(n1 + n2, '0');

    for (int i = n1 - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = n2 - 1; j >= 0; j--) {
            int sum = (result[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0') + carry;
            carry = sum / 10;
            result[i + j + 1] = sum % 10 + '0';
        }
        result[i] += carry;
    }

    size_t startPos = result.find_first_not_of('0');
    if (startPos != std::string::npos) {
        return result.substr(startPos);
    }
    return "0";
}

// Function to divide 
std::pair<std::string, std::string> divideBigIntegers(const std::string& num1, const std::string& num2) {
    if (num2 == "0") throw std::invalid_argument("Division by zero is undefined.");
    std::string quotient = "0";
    std::string remainder = num1;
    while (remainder.size() > num2.size() || (remainder.size() == num2.size() && remainder >= num2)) {
        std::string currentQuotient = "1";
        std::string currentSubtractor = num2;

        while (remainder.size() > currentSubtractor.size() || 
               (remainder.size() == currentSubtractor.size() && remainder >= currentSubtractor)) {
            currentSubtractor += '0';
            currentQuotient += '0';
        }
        currentSubtractor.pop_back();
        currentQuotient.pop_back();

        remainder = subtractBigIntegers(remainder, currentSubtractor);
        quotient = addBigIntegers(quotient, currentQuotient);
    }

    return {quotient, remainder};
}

int main() {
    std::string num1, num2;
    
    std::cout << "Enter the first big integer: ";
    std::cin >> num1;
    std::cout << "Enter the second big integer: ";
    std::cin >> num2;
    // Addition
    std::string sum = addBigIntegers(num1, num2);
    std::cout << "Sum of the big integers: " << sum << std::endl;
    // Subtraction
    std::string difference;
    if (num1 >= num2) {
        difference = subtractBigIntegers(num1, num2);
        std::cout << "Difference of the big integers (num1 - num2): " << difference << std::endl;
    } else {
        difference = subtractBigIntegers(num2, num1);
        std::cout << "Difference of the big integers (num2 - num1): " << difference << std::endl;
    }
    // Multiplication
    std::string product = multiplyBigIntegers(num1, num2);
    std::cout << "Product of the big integers: " << product << std::endl;
    // Division
    try {
        auto [quotient, remainder] = divideBigIntegers(num1, num2);
        std::cout << "Quotient of the big integers: " << quotient << std::endl;
        std::cout << "Remainder of the big integers: " << remainder << std::endl;
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
