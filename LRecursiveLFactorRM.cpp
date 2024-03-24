#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

// Function to remove left recursion from a production
void removeLeftRecursion(string nonTerminal, vector<string>& productions) {
    string alpha, beta;
    vector<string> newProductions;

    for (string prod : productions) {
        if (prod[0] == nonTerminal[0]) {
            newProductions.push_back(prod.substr(1) + nonTerminal + "'");
        } else {
            newProductions.push_back(prod + nonTerminal + "'");
        }
    }

    alpha = newProductions[0];
    for (size_t i = 1; i < newProductions.size(); ++i) {
        beta += newProductions[i];
        if (i != newProductions.size() - 1) {
            beta += "|";
        }
    }

    cout << nonTerminal << " -> " << beta << endl;
    cout << nonTerminal << "' -> " << alpha << nonTerminal << "'|" << "epsilon" << endl;
}

// Function to remove left factoring from a production
void removeLeftFactor(string nonTerminal, vector<string>& productions) {
    map<char, vector<string>> groups;
    for (string prod : productions) {
        groups[prod[0]].push_back(prod.substr(1));
    }

    for (auto group : groups) {
        if (group.second.size() > 1) {
            string factor = group.second[0];
            cout << nonTerminal << " -> " << group.first << factor << nonTerminal << "'" << endl;
            cout << nonTerminal << "' -> ";
            for (size_t i = 1; i < group.second.size(); ++i) {
                cout << group.second[i] << nonTerminal << "'|";
            }
            cout << "epsilon" << endl;
        } else {
            cout << nonTerminal << " -> " << group.first << group.second[0] << "|" << "epsilon" << endl;
        }
    }
}

int main() {
    map<string, vector<string>> grammar;
    int numProductions;
    string nonTerminal, production;

    cout << "Enter the number of productions: ";
    cin >> numProductions;

    cout << "Enter the productions in the form 'NonTerminal -> Production':" << endl;
    for (int i = 0; i < numProductions; ++i) {
        cin >> nonTerminal;
        cin.ignore();
        getline(cin, production);
        grammar[nonTerminal].push_back(production);
    }

    cout << "Grammar after removing left recursion:" << endl;
    for (auto nonTerm : grammar) {
        removeLeftRecursion(nonTerm.first, nonTerm.second);
    }

    cout << "Grammar after removing left factor:" << endl;
    for (auto nonTerm : grammar) {
        removeLeftFactor(nonTerm.first, nonTerm.second);
    }

    return 0;
}
