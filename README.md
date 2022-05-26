# Simple QT Calculator

## About
This is a very simple calculator written in C++ using the QT Framework. It was designed to handle some *slightly* 
complex expressions; take a look at the examples below to see how expressions will be evaluated. 
Let **a** and **b** be valid numbers:

- a(b) = a * b
- (a)(b) = a * b
- -a = 0 - a

Allowing expressions like that will improve the user's experience when using this calculator. Other features 
include:

- Displaying an **ERROR** message when an invalid expression is entered.
- If **ERROR** message is displayed after previous submission, the user can type anything, and the **ERROR** message 
  will go away.
- If an answer is displayed on the screen from a previous submission, there are two possibilities:
    - If the user wants to clear the answer from the previous calculation, the can press **CLR**, or
      just start typing a numerical or parentheses character. This will clear previous answer.
    - If the user wants to use the answer from the previous calculation in the new calculation,
      they can type an operator (+,-,*,/,^), which will preserve the previous answer.

## Installation
1. Clone this repo.
``git clone https://github.com/markortleb/simple-qt-calculator.git``

2. Change directory to top level of cloned repo.
``cd ./simple-qt-calculator``
   
3. Run CMake.
``cmake -S . -B build``
   
4. Change directory to newly created build folder.
``cd ./build``
   
5. Run make.
``make``
   
6. Run your installed calculator.
``./SimpleCalculator``
   

