//
//  eval.cpp
//  eval
//
//  Created by Runjia Li on 2/4/17.
//  Copyright © 2017 Runjia Li. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;


// Removes white space from str
string noSpace(const string& str);

// Checks the type of char encountered
int charType(const char& ch);

// Checks the precedence of operator
int precedence(const char& ch);


// Evaluates a boolean expression
// Postcondition: If infix is a syntactically valid infix boolean
//   expression, then postfix is set to the postfix form of that
//   expression, result is set to the value of the expression (where
//   in that expression, each digit k represents element k of the
//   values array), and the function returns zero.  If infix is not a
//   syntactically valid expression, the function returns 1.  (In that
//   case, postfix may or may not be changed, but result must be
//   unchanged.)

int evaluate(string infix, const bool values[], string& postfix, bool& result)
{
    string input = noSpace(infix); // Remove white space
    stack<char> charStack;
    string output = "";
    
    int leftCount = 0;  // Counts number of parentheses encountered
    int rightCount = 0;
    
    for (int i = 0; i < input.length(); i++)
    {
        if (i == 0 && charType(input[i]) != 2 && input[i] != '(' && input[i] != '!')
        // First char must be a number, '(' or '!'
            return 1;
        
        if (i == (input.length() - 1) && charType(input[i]) != 2 && input[i] != ')')
        // Last char must be a number or ')'
            return 1;
        
        switch(charType(input[i]))
        {
            case 1: // Operator
                if ((i + 1) < input.length() && (charType(input[i + 1]) != 2 && input[i + 1] != '(' && input[i + 1] != '!'))
                // Operator must be followed by a number, '(' or '!'
                    return 1;
                
                if (input[i] == '!' && input[i + 1] == '!') // Get rid of consecutive '!'s.
                {
                    i++;
                    break;
                }
                
                while (!charStack.empty())
                {
                    if (charStack.top() == '(' || precedence(charStack.top()) < precedence(input[i]))
                    {
                        break;
                    }
                    output += charStack.top();
                    charStack.pop();
                }
                charStack.push(input[i]);
                break;
                
            case 2: // Number
                if ((i + 1) < input.length() && charType(input[i + 1]) != 1 && input[i + 1] != ')')
                // Number must be followed by operator or ')'
                    return 1;
                output += input[i];
                break;
                
            case 3: // "("
                if ((i + 1) < input.length() && charType(input[i + 1]) != 2 && input[i + 1] != '!' && input[i + 1] != '(')
                // '(' must be followed by number or '!' or '('
                    return 1;
                charStack.push(input[i]);
                leftCount++;
                break;
                
            case 4: // ")"
                if (((i + 1) < input.length() && charType(input[i + 1]) != 1 && input[i + 1] != ')') || input[i + 1] == '!')
                // ')' must be followed by operators, not '!' and ')'
                    return 1;
                
                while (!charStack.empty() && charStack.top() != '(')
                {
                    output += charStack.top();
                    charStack.pop();
                }
                
                if (!charStack.empty())
                    charStack.pop();
                rightCount++;
                break;
                
            default:
                return 1;
        }
    }
    
    if (leftCount != rightCount) // Check if number of left and right parentheses are the same
    {
        return 1;
    }
    
    while (!charStack.empty())
    {
        output += charStack.top();
        charStack.pop();
    }
    
    if (output.length() < 1)
        return 1;
    postfix = output;
    
    stack<bool> evalStack;
    
    for (int i = 0; i < output.length(); i++)
    {
        if (charType(output[i]) == 1)
        {
            bool op1 = evalStack.top();
            evalStack.pop();
            bool op2 = false;
            
            switch(output[i])
            {
                case('!'):
                    evalStack.push(!op1);
                    break;
                case('|'):
                    op2 = evalStack.top();
                    evalStack.pop();
                    evalStack.push(op1 || op2);
                    break;
                case('&'):
                    op2 = evalStack.top();
                    evalStack.pop();
                    evalStack.push(op1 && op2);
                    break;
            }
        }
        
        else if (charType(output[i]) == 2)
        {
            evalStack.push(values[output[i] - 48]);
        }
    }
    
    result = evalStack.top();
    
    return 0;
}

string noSpace(const string& str)
{
    string result = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ')
            result += str[i];
    }
    return result;
}

int charType(const char& ch)
{
    if (ch == '!' || ch == '|' || ch == '&')
        return 1;
    if (isdigit(ch))
        return 2;
    if (ch == '(')
        return 3;
    if (ch == ')')
        return 4;
    return 0;
}

int precedence(const char& ch)
{
    switch (ch)
    {
        case '|':
            return 1;
        case '&':
            return 2;
        case '!':
            return 3;
        default:
            return 0;
    }
}


int main()
{
    bool ba[10] = {
        //  0      1      2      3      4      5      6      7      8      9
        true,  true,  true,  false, false, false, true,  false, true,  false
    };
    

    string pf;
    bool answer;
    assert(evaluate("2", ba, pf, answer) == 0 && answer);
    assert(evaluate("(3)", ba, pf, answer) == 0 && !answer);
    assert(evaluate(" 2&(3) ", ba, pf, answer) == 0 && !answer);
    assert(evaluate(" 0 & !9", ba, pf, answer) == 0 && answer);
    assert(evaluate("!(7|8)", ba, pf, answer) == 0 && !answer);
    assert(evaluate(" !7|8", ba, pf, answer) == 0 && answer);
    assert(evaluate("6|4&5 ", ba, pf, answer) == 0 && answer);
    assert(evaluate("1&!(9|1&1|9) | !!!(9&1&9)", ba, pf, answer) == 0 && answer);
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
    assert(evaluate("8|", ba, pf, answer) == 1);
    assert(evaluate("4 5", ba, pf, answer) == 1);
    assert(evaluate("01", ba, pf, answer) == 1);
    assert(evaluate("()", ba, pf, answer) == 1);
    assert(evaluate("2(9|8)", ba, pf, answer) == 1);
    assert(evaluate("2(&8)", ba, pf, answer) == 1);
    assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
    assert(evaluate("", ba, pf, answer) == 1);
    assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
           &&  pf == "43!03&&|"  &&  !answer);
    assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
    ba[2] = false;
    ba[9] = true;
    assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
    cout << "Passed all tests" << endl;
}