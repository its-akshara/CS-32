#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

bool isBinaryOperator(char ch)
{
    return ch=='&' || ch == '|';
}

bool isOperand(char ch)
{
    return ch=='0' || ch == '1' ||ch=='2' || ch == '3' || ch=='4' || ch == '5' || ch=='6' || ch == '7' || ch=='8' || ch == '9';
}
bool checkPrecedence(char islow, char ishigh)
{
    if(islow==ishigh)
        return true;
    switch(islow)
    {
        case '!': return false;
        case '&': return ishigh=='!';
        case '|': return ishigh == '!' || ishigh == '&';
    }
    
    return false;
    
}
//removes all spaces from a given string
void removeSpaces(string &s)
{
    int j;
    bool LastSpace = false;
    for(int i=0; i<s.length(); i++)
    {
        if(s[i] == ' ')
        {
            for(j = i; j<s.length()-1; j++)
            {
                s[j] = s[j+1];
            }
            s[s.length()-1] = ' ';
            for(int x = i; x<s.length(); x++)
            {
                if(x == (s.length()-1))
                {
                    LastSpace = true;
                }
                if(s[x] == ' ')
                {
                    continue;
                }
                else
                {
                    LastSpace=false;
                    break;
                }
            }
            
            if(!LastSpace)
                i--;
        }
    }
    
}

//Takes an infix string, checks if it's valid and converts it to postfix
bool makePostfix(string infix, string &postfix)
{
    postfix = "";
    stack<char> opStack;
    int i=0, countOpen = 0, countClose = 0;
    string temp = infix;
    removeSpaces(temp);
    infix = temp;
    if(infix=="")
        return false;
    for(;i<infix.length(); i++)
    {
        
        if (infix[i] == '(') {
            countOpen++;
        }
        else if (infix[i] == ')')
            countClose++;
    }
    if(countClose!=countOpen)
        return  false;
    i=0;
    for(char ch = infix[0]; i<infix.length(); i++)
    {
        ch = infix[i];
        switch(ch)
        {
            case ' ':continue;
            case '0':case'1':case '2': case '3': case '4':case '5':case '6':case '7':case '8':case '9':
                
                if(i>0 && (infix[i-1]==')' || isOperand(infix[i-1])))
                    return false;
                if(i<infix.length() && (isOperand(infix[i+1]) || infix[i+1]=='('))
                    return false;
                    
                postfix+=ch;
                break;
            
            case '(':
                if(i!=0 && isOperand(infix[i-1]))
                    return false;
                if(i<(infix.length()-1) && (isBinaryOperator(infix[i+1]) || infix[i+1] == ')'))
                    return false;
                if(i == infix.length()-1)
                    return false;
                opStack.push(ch);
                break;
            case ')': while(opStack.top() != '(')
            {
                postfix+=opStack.top();
                opStack.pop();
            }
                opStack.pop();
                break;
            case '!':
                if(i>0 && (infix[i-1] == ')' || isOperand(infix[i-1])))
                    return false;
                if(i<(infix.length()-1) && infix[i+1] == ')')
                    return false;
                if(i == infix.length()-1)
                    return false;
                
                opStack.push(ch);
                
                break;
            case '|':case '&':
                if(i == 0 || i==(infix.length()-1))
                    return false;
                if(i>0 && (isBinaryOperator(infix[i-1]) || infix[i-1]=='('))
                    return false;
                if(i<(infix.length()-1) && (isBinaryOperator(infix[i+1]) || infix[i+1] == ')'))
                    return false;
                
                
                while(!opStack.empty() && checkPrecedence(ch, opStack.top()))
                {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.push(ch);
                break;
            default: return false;
        }
    }
    while(!opStack.empty())
    {
        postfix += opStack.top();
        opStack.pop();
    }
    return true;
}
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
    //bool testResult = false;
    if(!makePostfix(infix, postfix))
        return 1;
    //now has no spaces and correct postfix syntax
    bool operand1,operand2;
    stack<bool> operandStack;
    char ch;
    for(int i = 0; i<postfix.length(); i++)
    {
        ch = postfix[i];
        if(isOperand(ch))
        {
            operandStack.push(values[ch-'0']);
        }
        else if(isBinaryOperator(ch))
        {
            operand2 = operandStack.top();
            operandStack.pop();
            operand1 = operandStack.top();
            operandStack.pop();
            switch(ch)
            {
                case '&':
                    operandStack.push(operand2 && operand1);
                    break;
                case '|':
                    operandStack.push(operand2 || operand1);
                    break;
            }
            
        }
        else{  //!
            operand1 = operandStack.top();
            operand1 = !operand1;
            operandStack.pop();
            operandStack.push(operand1);
        }
        
    }
    result = operandStack.top();
    operandStack.pop();
    return 0;
}


int main()
{
    bool ba[10] = {
        //  0      1      2      3      4      5      6      7      8      9
        true,  true,  true,  false, false, false, true,  false, true,  false
    };
    string pf;
    bool answer;
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
    assert(evaluate("8|", ba, pf, answer) == 1);
    assert(evaluate("4 5", ba, pf, answer) == 1);
    assert(evaluate("3&5!7",ba,pf,answer)==1);
    assert(evaluate("  3    &5 | !    7 ",ba,pf,answer)==0 && pf=="35&7!|" && answer);
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

