#include <string>
#include "stack.h"

const char brackets[] {'[', ']', '{', '}', '(', ')'};

bool isBracket(char ch, Stack& stack){
    for(int i = 0; i < 6; i++){
        if(ch == brackets[i]){
            return true;
        }
    }
    return false;
}

bool isAPair(char lhs, char rhs){
    return ((lhs == brackets[0] && rhs == brackets[1]) ||
            (lhs == brackets[2] && rhs == brackets[3]) ||
            (lhs == brackets[4] && rhs == brackets[5]));
}

bool bracketCheck(const std::string &s){
    Stack stack;
    //stack.initialize();
    for (std::string::size_type i = 0; i < s.size(); ++i){
        if(isBracket(s[i], stack)){
            if(stack.isEmpty()){
                stack.push(s[i]);
            }
            else{
                if(isAPair(stack.top(), s[i])){
                    stack.pop();
                }
                else{
                    stack.push(s[i]);
                }
            }
        }
    }
    return stack.isEmpty();
}
