#include <iostream>

/* Validation of a real number*/
bool validRealNumber(std::string number) {
    int period = 0, numerals = 0;
    for (int i = 0; i < number.length(); ++i) {
        if (number[i] == '.') period++;
        else if (number[i] >= '0' && number[i] <= '9') numerals++;

        /* errors */
        //incorrect character
        if (number[i] != '.' && number[i] != '-' && !(number[i] >= '0' && number[i] <= '9'))
            return false;
        //More than one decimal point
        if (period > 1)
            return false;
        //No one num
        if (i == (number.length() - 1) && numerals == 0)
            return false;
        //Character "-" can only be the first character
        if (i > 0 && number[i] == '-')
            return false;
        i++;
    }
    return true;
}

/*Correct real number.  - Zero delete*/
std::string CorrectRealNum(std::string number) {
    std::string result;
    int i = 0;

    if (number[0] == '-') {
        result += '-';
        i++;
    }
    for (; i < number.length(); ++i) {
        if (number[i] != '0') break;
    }
    for (; number[i] != '.' && i < number.length(); ++i) {
        result += number[i];
    }
    if (number[i] == '.' ) {
        std::string mant;

        for (; i < number.length(); ++i) {
            mant += number[i];
            if (number[i] != '0' && number[i] != '.') {
                result += mant;
                mant.clear();
            }
        }
    }
    return result;
}

/*get part of a string "str" from index "n" to character "c"*/
std::string getPartRow(std::string str, int n, char c) {
    std::string partStr;

    for (int i = n; str[i] != '.' && i < str.length(); ++i) {
        partStr += str[i];
    }
    return partStr;
}

int firstRealNumMoreSecond(std::string firstNumber, std::string secondNumber) {
    std::string exponentFirstNumber, exponentSecondNumber, mantissaFirstNumber, mantissaSecondNumber;

    if (firstNumber == secondNumber) return 2;

        //get exponent parts
    int firstPartNumIndex = 0, secondPartNumIndex = 0;

    for (int i = 0; firstNumber[i] != '.' && i < firstNumber.length(); ++i) {
        if (firstNumber[i] == '-' || firstNumber[i] == '0') firstPartNumIndex++;
        else break;
    }
    for (int i = 0; secondNumber[i] != '.' && i < secondNumber.length(); ++i) {
        if (secondNumber[i] == '-' || secondNumber[i] == '0') secondPartNumIndex++;
        else break;
    }

    exponentFirstNumber = getPartRow(firstNumber, firstPartNumIndex, '.');
    exponentSecondNumber = getPartRow(secondNumber, secondPartNumIndex, '.');

    if (firstNumber.find('.') != std::string::npos)
        mantissaFirstNumber = firstNumber.substr(firstNumber.find('.') + 1, firstNumber.length() - 1);
    if (secondNumber.find('.') != std::string::npos)
        mantissaSecondNumber =  secondNumber.substr(secondNumber.find('.') + 1, secondNumber.length() - 1);

        //check for negativity
    if (firstNumber[0] == '-' || secondNumber[0] == '-') {
            //if only one negative then it's less
        if (firstNumber[0] == '-' && secondNumber[0] != '-') return false;
        else if (firstNumber[0] != '-' && secondNumber[0] == '-') return true;
            //if both are negative:
        else {
                //if the parts are equal
            if (exponentFirstNumber == exponentSecondNumber && mantissaFirstNumber == mantissaSecondNumber) return 2;
                //if one exponent length more
            else if (exponentFirstNumber.length() > exponentSecondNumber.length()) return false;
            else if (exponentFirstNumber.length() < exponentSecondNumber.length()) return true;
                //if both have the equal length, check every char
            else {
                for (int i = 0; i < exponentFirstNumber.length(); ++i) {
                    if (exponentFirstNumber[i] > exponentSecondNumber[i]) return false;
                    else if (exponentFirstNumber[i] < exponentSecondNumber[i]) return true;
                }
                for (int i = 0; ((mantissaFirstNumber.length() < mantissaSecondNumber.length()) ?
                                 (i < mantissaFirstNumber.length()) : (i < mantissaSecondNumber.length())); ++i) {
                    if (mantissaFirstNumber[i] > mantissaSecondNumber[i]) return false;
                    else if (mantissaFirstNumber[i] < mantissaSecondNumber[i]) return true;
                }
                if (mantissaFirstNumber.length() > mantissaSecondNumber.length()) return false;
                else if (mantissaFirstNumber.length() < mantissaSecondNumber.length()) return true;
            }
        }
    } else {
            //if one exponent length more
        if (exponentFirstNumber.length() > exponentSecondNumber.length()) return true;
        else if (exponentFirstNumber.length() < exponentSecondNumber.length()) return false;
            //if both have the equal length, check every char
        else {
            for (int i = 0; i < exponentFirstNumber.length(); ++i) {
                if (exponentFirstNumber[i] > exponentSecondNumber[i]) return true;
                else if (exponentFirstNumber[i] < exponentSecondNumber[i]) return false;
            }

            for (int i = 0; ((mantissaFirstNumber.length() < mantissaSecondNumber.length()) ?
                             (i < mantissaFirstNumber.length()) : (i < mantissaSecondNumber.length())); ++i) {
                if (mantissaFirstNumber[i] > mantissaSecondNumber[i]) return true;
                else if (mantissaFirstNumber[i] < mantissaSecondNumber[i]) return false;
            }
            if (mantissaFirstNumber.length() > mantissaSecondNumber.length()) return true;
            else if (mantissaFirstNumber.length() < mantissaSecondNumber.length()) return false;
        }

    }
    return 3;
}

int main() {
    std::string firstNumber, secondNumber, result;
    std::string exponentFirstNumber, exponentSecondNumber, mantissaFirstNumber, mantissaSecondNumber;
    int resultFunction;
    bool correct = false;

    while (!correct) {
        std::cout << "Input first number\n";
        std::cin >> firstNumber;
        if (validRealNumber(firstNumber)) correct = true;
        else (std::cout << "incorrect data.\n");
    }
    correct = false;

    while (!correct) {
        std::cout << "Input second number\n";
        std::cin >> secondNumber;
        if (validRealNumber(secondNumber)) correct = true;
        else (std::cout << "incorrect data.\n");
    }

    secondNumber = CorrectRealNum(secondNumber);
    firstNumber = CorrectRealNum(firstNumber);

    resultFunction = firstRealNumMoreSecond(firstNumber, secondNumber);
    if (resultFunction == 0) result = "Less";
    else if (resultFunction == 1) result = "More";
    else if (resultFunction == 2) result = "Equal";
    else result = "Something went wrong (error " + std::to_string(resultFunction) + ")";

    std::cout << result;
}