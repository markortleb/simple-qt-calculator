#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include "utility.h"


bool calculateExpression(std::string calcLine, double *result) {
	int parenthesesLevel = 0;
	double left = 0.0;
	double right = 0.0;
	bool validExpression = true;
	bool expectingNum = true;
	char previousChar = 0;
	std::string numBuffer = "";
	std::queue<std::string> calcElements;
	std::stack<std::string> conversionStack;
	std::queue<std::string> postfix;
	std::stack<double> calcStack;
	std::queue<std::string> tempQueue;
	std::vector<std::string> tempList;

	for (int i = 0; i < calcLine.length(); i++) {
		if (isdigit(calcLine[i]) || calcLine[i] == '.') {
			numBuffer = numBuffer + calcLine[i];
		} else {
			if (!numBuffer.empty()) {
				calcElements.push(numBuffer);
				numBuffer = "";
			}

            // Allows us to interpret (6)(5) as 6*5
			if (calcLine[i] == '(') {
				if (isdigit(previousChar) || previousChar == ')') {
				    calcElements.push("*");
				}
			}

			if (calcLine[i] == '-' && previousChar == '\0') {
			    calcElements.push("0");
			}

			calcElements.push(std::string(1, calcLine[i]));
		}

		if (i + 1 == calcLine.length() && !numBuffer.empty()) {
			calcElements.push(numBuffer);
			numBuffer = "";
		}

		previousChar = calcLine[i];
	}

	while (!calcElements.empty()) {
		if (calcElements.front()[0] == '(') {
			conversionStack.push(calcElements.front());
		} else if (calcElements.front()[0] == ')' && !conversionStack.empty()) {
			while (conversionStack.top()[0] != '(') {
				postfix.push(conversionStack.top());
				conversionStack.pop();
			}
			conversionStack.pop();
		} else if (calcElements.front()[0] == '+' || calcElements.front()[0] == '-'
				|| calcElements.front()[0] == '*' || calcElements.front()[0] == '/' || calcElements.front()[0] == '^') {
			
			while (!conversionStack.empty() && conversionStack.top()[0] != '('
					&& getHierarchy(calcElements.front()[0]) <= getHierarchy(conversionStack.top()[0])) {
				
				postfix.push(conversionStack.top());
				conversionStack.pop();
			}
			conversionStack.push(calcElements.front());
		} else {
			postfix.push(calcElements.front());
		}
		calcElements.pop();
	}

	while (!conversionStack.empty() && validExpression) {
		postfix.push(conversionStack.top());
		conversionStack.pop();
	}

    while (!postfix.empty() && validExpression) {
        std::string token = postfix.front();
        tempList.push_back(token);
        tempQueue.push(token);
        postfix.pop();
    }

    postfix = tempQueue;

	// Verify all numbers have at most one decimal
	for (int i = 0; i < tempList.size(); i++) {
	    if (std::count(tempList[i].begin(), tempList[i].end(), '.') > 1) {
            validExpression = false;
	    }
	}

	while (!postfix.empty() && validExpression) {
		if (postfix.front()[0] == '+' || postfix.front()[0] == '-' || postfix.front()[0] == '*'
			       || postfix.front()[0] == '/' || postfix.front()[0] == '^') {
			if (calcStack.size() < 2) {
				validExpression = false;
				break;
			} else {
				right = calcStack.top();
				calcStack.pop();
				left = calcStack.top();
				calcStack.pop();

				if (postfix.front()[0] == '/' && right == 0.0) {
					validExpression = false;
					break;
				}	

				switch (postfix.front()[0]) {
					case '+':
						calcStack.push(left + right);
						break;
					case '-':
						calcStack.push(left - right);
						break;
					case '*':
						calcStack.push(left * right);
						break;
					case '/':
						calcStack.push(left / right);	
						break;
					case '^':	
						calcStack.push(std::pow(left,right));
						break;
				}
			}
		} else {
			try {
				calcStack.push(std::stod(postfix.front(), NULL));
			} catch (const std::invalid_argument& ia) {
				validExpression = false;
				break;
			}
		}
		postfix.pop();
	}

    if (calcStack.size() > 0) {
        *result = calcStack.top();
    } else {
        *result = 0;
        validExpression = false;
    }

	return validExpression;
}


int getHierarchy(char op) {
	int opHierarchy = -1;
	if (op == '+' || op == '-') {
		opHierarchy = 1;
	} else if (op == '*' || op == '/') {
		opHierarchy = 2;
	} else if (op == '^') {
		opHierarchy = 3;
	} else if (op == '(') {
		opHierarchy = 4;
	}
	return opHierarchy;
}
