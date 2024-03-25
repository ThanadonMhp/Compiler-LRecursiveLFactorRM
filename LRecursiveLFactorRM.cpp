#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to check if a given symbol is non-terminal
bool isNonTerminal(char symbol) {
    return symbol >= 'A' && symbol <= 'Z';
}

// Function to remove left recursion from a production
vector<string> removeLeftRecursion(string production) {
    vector<string> newProductions;
    char nonTerminal = production[0];
    string restOfProduction = production.substr(3);
    vector<string> alpha, beta;

    for (int i = 0; i < restOfProduction.length(); i++) {
        string currentProduction = "";
        currentProduction += restOfProduction[i];

        if (i + 1 < restOfProduction.length() && restOfProduction[i + 1] == '|') {
            alpha.push_back(currentProduction);
            i++;
        } else {
            beta.push_back(currentProduction);
        }
    }

    if (alpha.empty()) {
        newProductions.push_back(production);
    } else {
        string newNonTerminal = "";
        newNonTerminal += nonTerminal;
        newNonTerminal += "'";
        newProductions.push_back(newNonTerminal + " -> " + beta[0] + newNonTerminal);

        for (int i = 0; i < alpha.size(); i++) {
            newProductions.push_back(nonTerminal + " -> " + alpha[i] + newNonTerminal);
        }

        newProductions.push_back(newNonTerminal + " -> epsilon");

        for (int i = 1; i < beta.size(); i++) {
            newProductions.push_back(newNonTerminal + " -> " + beta[i] + newNonTerminal);
        }
    }

    return newProductions;
}

// Function to remove left factor from a production
vector<string> removeLeftFactor(string production) {
    vector<string> newProductions;
    char nonTerminal = production[0];
    string restOfProduction = production.substr(3);
    vector<string> commonPrefixes;

    for (int i = 0; i < restOfProduction.length(); i++) {
        string currentProduction = "";
        currentProduction += restOfProduction[i];

        if (i + 1 < restOfProduction.length() && restOfProduction[i + 1] == '|') {
            commonPrefixes.push_back(currentProduction);
            i++;
        } else {
            commonPrefixes.push_back(currentProduction);
            break;
        }
    }

    if (commonPrefixes.size() == 1) {
        newProductions.push_back(production);
    } else {
        string newNonTerminal = "";
        newNonTerminal += nonTerminal;
        newNonTerminal += "'";
        newProductions.push_back(nonTerminal + " -> " + commonPrefixes[0] + newNonTerminal);

        for (int i = 1; i < commonPrefixes.size(); i++) {
            newProductions.push_back(newNonTerminal + " -> " + commonPrefixes[i] + newNonTerminal);
        }

        for (int i = commonPrefixes.size(); i < restOfProduction.length(); i++) {
            string currentProduction = "";
            currentProduction += restOfProduction[i];

            if (i + 1 < restOfProduction.length() && restOfProduction[i + 1] == '|') {
                newProductions.push_back(nonTerminal + " -> " + currentProduction);
                i++;
            } else {
                newProductions.push_back(nonTerminal + " -> " + currentProduction);
                break;
            }
        }
    }

    return newProductions;
}

int main() {
    // example Grammar without left recursion and left factor
    // vector<string> inputGrammar = {
    //     "stmt -> if-stmt",
    //     "stmt -> other",
    //     "if-stmt -> if (exp) stmt else-part",
    //     "else-part -> else stmt",
    //     "else-part -> epsilon",
    //     "exp -> 0",
    //     "exp -> 1"
    // };

    // example Grammar with left recursion and left factor
    // vector<string> inputGrammar = {
    //     "E -> E + T | T",
    //     "T -> T * F | F",
    //     "F -> ( E ) | id"
    // };
    

    vector<string> inputGrammar;
    cout << "Input grammar :   (type 'end' to finish)" << endl; 

    string input;
    
    while (getline(cin, input)) {
        if (input == "end") {
            break;
        }
        inputGrammar.push_back(input);
    }
    
    vector<string> outputGrammar;

    for (string production : inputGrammar) {
        if (isNonTerminal(production[0])) {
            vector<string> newProductions = removeLeftRecursion(production);

            for (string newProduction : newProductions) {
                outputGrammar.push_back(newProduction);
            }
        } else {
            outputGrammar.push_back(production);
        }
    }

    cout << "Grammar without left recursion and left factor:" << endl;

    for (string production : outputGrammar) {
        cout << production << endl;
    }

    return 0;
}