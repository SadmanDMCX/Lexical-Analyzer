#include <iostream>
#include <vector>

using namespace std;

class general {
public:
    int StringLength(string data) {
        int i = 0;
        while (data[i] != '\0') {
            i++;
        }
        return i;
    }
} general;

class compiler {
public:
    vector<string> tokenizer(string data) {
        vector<string> tokens;
        string line = "";

        string points = " ,;(){}+-*/<>=";
        string point = "";

        // Found New Line
        for (int i = 0; i < general.StringLength(data); i++) {
            for (int j = 0; j < points.length(); j++) {
                if (data[i] == points[j]) {
                    line = removeSpace(line);
                    if (point != "" || points != " ")
                        tokens.push_back(point);
                    tokens.push_back(line);
                    line = "";
                    point = "";
                }
                if (i == general.StringLength(data) - 1) {
                    if (point != "") {
                        tokens.push_back(point);
                        point = "";
                    }
                    if (line != "") {
                        tokens.push_back(line);
                        line = "";
                    }
                }
            }

            bool pointFound = false;
            for (int j = 0; j < points.length(); j++) {
                if (data[i] == points[j]) {
                    pointFound = true;
                }
                if (pointFound){
                    point += points[j];
                    break;
                }
            }

            if (!pointFound) {
                line += data[i];
            }

            if (data[i] == '-' && (data[i+1] == '0' || data[i+1] == '1' || data[i+1] == '2')) {
                pointFound = false;
                line += data[i];
            }
        }

        return tokens;
    }

    vector<string> commentDetectAndDelete(string& data) {
        bool isFirstFound = false;
        vector<string> comments;
        string comment;
        for (int i = 0, j = 0; i < data.length(); i++) {

            if (data[i] == '/' && data[i+1] == '*') {
                isFirstFound = true;
            }

            if (data[i] == '*' && data[i+1] == '/') {
                j = 0;
                isFirstFound = false;
                comments.push_back(comment);
            }

            if (isFirstFound == true) {
                if (j == 2) {
                    comment += data[i];
                } else {
                    j++;
                }
                data[i] = ' ';
            }

        }
        return comments;
    }

    string removeSpace(string data) {
        int len = data.length();
        for (int i = 0; i < data.length(); i++) {
            if (data[i] == ' ' || data[i] == '\n' || data[i] == '\t') {
                if (i == data.length()-1) {
                    len--;
                } else {
                    for (int j = i; j < data.length(); j++) {
                        data[j] = data[j+1];
                    }
                    len--;
                }
            }
        }

        data.resize(len);
        return data;
    }

    bool isConstant(string data) {
        string numbers = "0123456789";
        char opa = '-';
        for (int j = 0; j < numbers.length(); j++) {
            if (data[0] == numbers[j] || data[0] == opa) {
                return true;
            }
        }
        return false;
    }
} comp;

namespace super {
    vector<string> compile(string data) {
        vector<string> comments = comp.commentDetectAndDelete(data);
        vector<string> tokens = comp.tokenizer(data);
        vector<string> keywords, refineKeywords;
        vector<string> operators, refineOperators;
        vector<string> specialSymbol, refineSpecialSymbol;
        vector<string> constants, refineSConstants;
        vector<string> variables;
        vector<string> finalOutput;

        bool isVariableFound = false;
        for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
            // -> Variables
            if (*it == "int" || *it == "float") {
                isVariableFound = true;
                it++;
            }

            if (*it == ";") {
                isVariableFound = false;
            }

            if (isVariableFound == true) {
                if(*it != "," && *it != " " && *it != "")
                    variables.push_back(*it);
            }
        }

        for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {

            // -> Keywords
            if (*it == "void" || *it == "print" || *it == "main" || *it == "if" || *it == "endif"
                || *it == "then" || *it == "else" || *it == "int") {
                keywords.push_back(*it);
                tokens.erase(it);

                if (it != tokens.begin()) {
                    it = tokens.begin();
                }
            }

            // -> Operators
            if (*it == "+" || *it == "-" || *it == "/" || *it == "<" || *it == ">" || *it == "=" || *it == "*") {
                operators.push_back(*it);
                tokens.erase(it);

                if (it != tokens.begin()) {
                    it = tokens.begin();
                }
            }

            // -> Special Symbol
            if (*it == "," || *it == ";" || *it == "(" || *it == ")" || *it == "{" || *it == "}") {
                specialSymbol.push_back(*it);
                tokens.erase(it);

                if (it != tokens.begin()) {
                    it = tokens.begin();
                }
            }

            // -> Constants
            if (comp.isConstant(*it)) {
                constants.push_back(*it);
                tokens.erase(it);

                if (it != tokens.begin()) {
                    it = tokens.begin();
                }
            }

        }



        // -> Part - 2

        bool isFound = false;
        // Refine Keywords
        for (vector<string>::iterator it = keywords.begin(); it != keywords.end(); it++) {
            isFound = false;
            for (vector<string>::iterator itw = it+1; itw != keywords.end(); itw++) {
                if (*it == *itw) {
                    isFound = true;
                }
            }
            if (!isFound) {
                refineKeywords.push_back(*it);
            }
        }

        // Show Keywords
        cout << "Keywords: ";
        finalOutput.push_back("Keywords: ");
        for (vector<string>::iterator it = refineKeywords.begin(); it != refineKeywords.end(); it++) {
            cout << *it << " ";
            finalOutput.push_back(*it);
        }
        finalOutput.push_back("END");
        cout << endl;
        // End Keywords

        // Refine Operator
        for (vector<string>::iterator it = operators.begin(); it != operators.end(); it++) {
            isFound = false;
            for (vector<string>::iterator itw = it+1; itw != operators.end(); itw++) {
                if (*it == *itw) {
                    isFound = true;
                }
            }
            if (!isFound) {
                refineOperators.push_back(*it);
            }
        }

        // Show Operator
        cout << "Operators: ";
        finalOutput.push_back("Operators: ");
        for (vector<string>::iterator it = refineOperators.begin(); it != refineOperators.end(); it++) {
            cout << *it << " ";
            finalOutput.push_back(*it);
        }
        finalOutput.push_back("END");
        cout << endl;
        // End Operator

        // Refine Special Symbol
        for (vector<string>::iterator it = specialSymbol.begin(); it != specialSymbol.end(); it++) {
            isFound = false;
            for (vector<string>::iterator itw = it+1; itw != specialSymbol.end(); itw++) {
                if (*it == *itw) {
                    isFound = true;
                }
            }
            if (!isFound) {
                refineSpecialSymbol.push_back(*it);
            }
        }

        // Show Special Symbol
        cout << "Special Symbols: ";
        finalOutput.push_back("Special Symbols: ");
        for (vector<string>::iterator it = refineSpecialSymbol.begin(); it != refineSpecialSymbol.end(); it++) {
            cout << *it << " ";
            finalOutput.push_back(*it);
        }
        finalOutput.push_back("END");
        cout << endl;
        // End Special Symbol

        // Refine Constants
        for (vector<string>::iterator it = constants.begin(); it != constants.end(); it++) {
            isFound = false;
            for (vector<string>::iterator itw = it+1; itw != constants.end(); itw++) {
                if (*it == *itw) {
                    isFound = true;
                }
            }
            if (!isFound) {
                refineSConstants.push_back(*it);
            }
        }

        // Show Constants
        cout << "Constants: ";
        finalOutput.push_back("Constants: ");
        for (vector<string>::iterator it = refineSConstants.begin(); it != refineSConstants.end(); it++) {
            cout << *it << " ";
            finalOutput.push_back(*it);
        }
        finalOutput.push_back("END");
        cout << endl;
        // End Constants

        // Show Variables
        cout << "Variables: ";
        finalOutput.push_back("Variables: ");
        for (vector<string>::iterator it = variables.begin(); it != variables.end(); it++) {
            cout << *it << " ";
            finalOutput.push_back(*it);
        }
        finalOutput.push_back("END");
        cout << endl;
        // End Variables

        // Show Comment
        cout << "Comments: ";
        finalOutput.push_back("Comments: ");
        for (vector<string>::iterator it = comments.begin(); it != comments.end(); it++) {
            cout << *it << " ";
            finalOutput.push_back(*it);
        }
        finalOutput.push_back("END");
        cout << endl;
        // End Comment

        return finalOutput;
    }

    string vectorToString(vector<string> data) {
        string stringData = "";
        for (vector<string>::iterator it = data.begin(); it != data.end(); it++) {
            if (*it != "END") {
                stringData += *it + " ";
            } else {
                stringData += "\n";
            }
        }
        return stringData;
    }
}







