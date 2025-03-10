#include <stdexcept>
#include <string>
#include <memory>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "sympp.hpp"

namespace parsing {

enum char_type {
    CHAR_UNSPECIFIED,          // dummy
    CHAR_LETTER,               // eg: "a", "b", "x"
    CHAR_DIGIT,                // eg: "0", "5", "."
    CHAR_POW,                  // "^"
    CHAR_MUL,                  // "*"
    CHAR_DIV,                  // "/"
    CHAR_ADD,                  // "+"
    CHAR_SUB,                  // "-"
    CHAR_PAR_LEFT,             // "("
    CHAR_PAR_RIGHT,            // ")"
};

bool is_letter(char x) {
    return (('a' <= x) && (x <= 'z'));
}

bool is_digit(char x) {
    return (('0' <= x) && (x <= '9')) || (x == '.');
}

char_type to_type(char x) {
    switch (x) {
    case '^':
        return CHAR_POW;
    case '*':
        return CHAR_MUL;
    case '/':
        return CHAR_DIV;
    case '+':
        return CHAR_ADD;
    case '-':
        return CHAR_SUB;
    case '(':
        return CHAR_PAR_LEFT;
    case ')':
        return CHAR_PAR_RIGHT;
    default:
        break;
    }

    if (is_letter(x)) {
        return CHAR_LETTER;
    }

    if (is_digit(x)) {
        return CHAR_DIGIT;
    }

    throw std::invalid_argument("invalid input character, valid expression characters are: [0-9a-z.+-*/^()]");
}

bool is_once(char_type t) {
    switch (t){
    case CHAR_POW:
        return true;
    case CHAR_MUL:
        return true;
    case CHAR_DIV:
        return true;
    case CHAR_ADD:
        return true;
    case CHAR_SUB:
        return true;
    case CHAR_PAR_LEFT:
        return true;
    case CHAR_PAR_RIGHT:
        return true;
    default:
        break;
    }

    return false;
}

enum token_family_type {
    TOKEN_FAMILY_UNSPECIFIED,          // dummy
    TOKEN_FAMILY_SYMBOL,               // eg: "x"
    TOKEN_FAMILY_NUMBER,               // eg: "1337.420"
    TOKEN_FAMILY_OPERATION,            // eg: "^"
    TOKEN_FAMILY_FUNCTION,             // eg: "ln"
    TOKEN_FAMILY_PAR_LEFT,             // "("
    TOKEN_FAMILY_PAR_RIGHT,            // ")"
};

enum token_type {
    TOKEN_UNSPECIFIED,          // dummy
    TOKEN_SYMBOL,               // eg: "x"
    TOKEN_NUMBER,               // eg: "1337.420"
    TOKEN_POW,                  // "^"
    TOKEN_MUL,                  // "*"
    TOKEN_DIV,                  // "/"
    TOKEN_ADD,                  // "+"
    TOKEN_SUB,                  // "-"
    TOKEN_LN,                   // "ln"
    TOKEN_EXP,                  // "exp"
    TOKEN_SIN,                  // "sin"
    TOKEN_COS,                  // "cos"
    TOKEN_PAR_LEFT,             // "("
    TOKEN_PAR_RIGHT,            // ")"
};

token_family_type to_family_type(token_type tt) {
    switch (tt){
    case TOKEN_UNSPECIFIED:
        return TOKEN_FAMILY_UNSPECIFIED;

    case TOKEN_SYMBOL:
        return TOKEN_FAMILY_SYMBOL;
    
    case TOKEN_NUMBER:
        return TOKEN_FAMILY_NUMBER;
    
    case TOKEN_POW:
        return TOKEN_FAMILY_OPERATION;
    case TOKEN_MUL:
        return TOKEN_FAMILY_OPERATION;
    case TOKEN_DIV:
        return TOKEN_FAMILY_OPERATION;
    case TOKEN_ADD:
        return TOKEN_FAMILY_OPERATION;
    case TOKEN_SUB:
        return TOKEN_FAMILY_OPERATION;
    
    case TOKEN_LN:
        return TOKEN_FAMILY_FUNCTION;
    case TOKEN_EXP:
        return TOKEN_FAMILY_FUNCTION;
    case TOKEN_SIN:
        return TOKEN_FAMILY_FUNCTION;
    case TOKEN_COS:
        return TOKEN_FAMILY_FUNCTION;

    case TOKEN_PAR_LEFT:
        return TOKEN_FAMILY_PAR_LEFT;
    
    case TOKEN_PAR_RIGHT:
        return TOKEN_FAMILY_PAR_RIGHT;

    default:
        break;
    }

    throw std::logic_error("cannot map token type to any known token family type");
}

size_t to_prescence(token_type tt) {
    switch (tt){
    case TOKEN_UNSPECIFIED:
        return 0;
    
    case TOKEN_ADD:
        return 1;
    case TOKEN_SUB:
        return 1;

        
    case TOKEN_MUL:
        return 2;
    case TOKEN_DIV:
        return 2;
        
    case TOKEN_POW:
        return 3;

    case TOKEN_LN:
        return 4;
    case TOKEN_EXP:
        return 4;
    case TOKEN_SIN:
        return 4;
    case TOKEN_COS:
        return 4;

    case TOKEN_PAR_LEFT:
        return 5;
    case TOKEN_PAR_RIGHT:
        return 5;
    case TOKEN_SYMBOL:
        return 5;
    case TOKEN_NUMBER:
        return 5;

    default:
        break;
    }

    return 5;
}

struct token {
    token_type type;
    std::string instance;
};

token to_token(std::string str) {
    if (str.size() == 0) {
        throw std::logic_error("attempted to build token from empty substring");
    }
    
    bool point_seen = false;

    switch (to_type(str[0])){
    case CHAR_POW:
        return token{TOKEN_POW, str};
    case CHAR_MUL:
        return token{TOKEN_MUL, str};
    case CHAR_DIV:
        return token{TOKEN_DIV, str};
    case CHAR_ADD:
        return token{TOKEN_ADD, str};
    case CHAR_SUB:
        return token{TOKEN_SUB, str};
    case CHAR_PAR_LEFT:
        return token{TOKEN_PAR_LEFT, str};
    case CHAR_PAR_RIGHT:
        return token{TOKEN_PAR_RIGHT, str};
    case CHAR_DIGIT:
        for (size_t i = 0; i < str.size(); i++) {
            if (!is_digit(str[i])){
                throw std::logic_error("attempted to build token from substring with multiple character families");
            }

            if (str[i] == '.'){
                if (point_seen) {
                    throw std::invalid_argument("invalid numeric input, multiple floating points found");
                }

                point_seen = true;
            }
        }

        return token{TOKEN_NUMBER, str};
    case CHAR_LETTER:
        if (str == "ln") {
            return token{TOKEN_LN, str};
        }
        if (str == "exp") {
            return token{TOKEN_EXP, str};
        }
        if (str == "sin") {
            return token{TOKEN_SIN, str};
        }
        if (str == "cos") {
            return token{TOKEN_COS, str};
        }

        for (size_t i = 0; i < str.size(); ++i) {
            if (!is_letter(str[i])){
                throw std::logic_error("attempted to build token from substring with multiple character families");
            }
        }

        return token{TOKEN_SYMBOL, str};
    default:
        break;
    }

    throw std::logic_error("attempted to build token from substring, but no first character type was found");
}

std::vector<token> lexify(std::string expr) {
    if (expr.size() == 0){
        throw std::invalid_argument("an input expression cannot be a empty string");
    }
    
    // phase 1: lexify

    char_type cur_type = CHAR_UNSPECIFIED;
    std::string cur;
    
    std::vector<token> tokens;

    for (int i = 0; i < expr.size(); ++i) {
        if (expr[i] == ' ') {
            continue;
        }

        char_type type = to_type(expr[i]);

        if (cur_type == CHAR_UNSPECIFIED) {
            cur_type = type;
        }

        if ((cur_type != type) || is_once(cur_type)){
            token t = to_token(cur);
            tokens.push_back(t);
            
            cur_type = type;
            cur.clear();
        }

        cur.push_back(expr[i]);
    }

    token t = to_token(cur);
    tokens.push_back(t);

    // phase 2: validation and postproccessing

    int par_cnt = 0;
    std::vector<token> tokens_;

    for (int i = 0; i < tokens.size() - 1; ++i) {
        token_family_type t1 = to_family_type(tokens[i].type);
        token_family_type t2 = to_family_type(tokens[i+1].type);

        tokens_.push_back(tokens[i]);

        switch (t1){
        case TOKEN_FAMILY_SYMBOL:
            switch (t2){
            case TOKEN_FAMILY_SYMBOL:
                tokens_.push_back(token{TOKEN_MUL, "*"});
                break;
            case TOKEN_FAMILY_NUMBER:
                throw std::invalid_argument("wrong neighbour tokens: " + tokens[i].instance + " and " + tokens[i+1].instance);
            case TOKEN_FAMILY_OPERATION:
                break;
            case TOKEN_FAMILY_FUNCTION:
                tokens_.push_back(token{TOKEN_MUL, "*"});
                break;
            case TOKEN_FAMILY_PAR_LEFT:
                tokens_.push_back(token{TOKEN_MUL, "*"});
                break;
            case TOKEN_FAMILY_PAR_RIGHT:
               break;
            default:
                break;
            }
            
            break;
        case TOKEN_FAMILY_NUMBER:
            switch (t2){
            case TOKEN_FAMILY_SYMBOL:
                tokens_.push_back(token{TOKEN_MUL, "*"});
                break;
            case TOKEN_FAMILY_NUMBER:
                tokens_.push_back(token{TOKEN_MUL, "*"});
                break;
            case TOKEN_FAMILY_OPERATION:
                break;
            case TOKEN_FAMILY_FUNCTION:
                tokens_.push_back(token{TOKEN_MUL, "*"});
                break;
            case TOKEN_FAMILY_PAR_LEFT:
                tokens_.push_back(token{TOKEN_MUL, "*"});
                break;
            case TOKEN_FAMILY_PAR_RIGHT:
                break;
            default:
                break;
            }

            break;
        case TOKEN_FAMILY_OPERATION:
            switch (t2){
            case TOKEN_FAMILY_SYMBOL:
                break;
            case TOKEN_FAMILY_NUMBER:
                break;
            case TOKEN_FAMILY_OPERATION:
                throw std::invalid_argument("wrong neighbour tokens: " + tokens[i].instance + " and " + tokens[i+1].instance);
            case TOKEN_FAMILY_FUNCTION:
                break;
            case TOKEN_FAMILY_PAR_LEFT:
                break;
            case TOKEN_FAMILY_PAR_RIGHT:
                throw std::invalid_argument("wrong neighbour tokens: " + tokens[i].instance + " and " + tokens[i+1].instance);
            default:
                break;
            }

            break;
        case TOKEN_FAMILY_FUNCTION:
            switch (t2){
            case TOKEN_FAMILY_SYMBOL:
                throw std::invalid_argument("wrong neighbour tokens: " + tokens[i].instance + " and " + tokens[i+1].instance);
            case TOKEN_FAMILY_NUMBER:
                throw std::invalid_argument("wrong neighbour tokens: " + tokens[i].instance + " and " + tokens[i+1].instance);
            case TOKEN_FAMILY_OPERATION:
                throw std::invalid_argument("wrong neighbour tokens: " + tokens[i].instance + " and " + tokens[i+1].instance);
            case TOKEN_FAMILY_FUNCTION:
                throw std::invalid_argument("wrong neighbour tokens: " + tokens[i].instance + " and " + tokens[i+1].instance);
            case TOKEN_FAMILY_PAR_LEFT:
                break;
            case TOKEN_FAMILY_PAR_RIGHT:
                throw std::invalid_argument("wrong neighbour tokens: " + tokens[i].instance + " and " + tokens[i+1].instance);
            default:
                break;
            }
            
            break;
        case TOKEN_FAMILY_PAR_LEFT:
            par_cnt++;

            switch (t2){
            case TOKEN_FAMILY_SYMBOL:
                break;
            case TOKEN_FAMILY_NUMBER:
                break;
            case TOKEN_FAMILY_OPERATION:
                if (tokens[i+1].type == TOKEN_SUB) {
                    break; // may be unary
                }
                throw std::invalid_argument("wrong neighbour tokens: " + tokens[i].instance + " and " + tokens[i+1].instance);
            case TOKEN_FAMILY_FUNCTION:
                break;
            case TOKEN_FAMILY_PAR_LEFT:
                break;
            case TOKEN_FAMILY_PAR_RIGHT:
                throw std::invalid_argument("wrong neighbour tokens: " + tokens[i].instance + " and " + tokens[i+1].instance);
            default:
                break;
            }

            break;
        case TOKEN_FAMILY_PAR_RIGHT:
            par_cnt--;
            if (par_cnt < 0) {
                throw std::invalid_argument("expression contains bad parentheses sequence");
            }

            switch (t2){
            case TOKEN_FAMILY_SYMBOL:
                tokens_.push_back(token{TOKEN_MUL, "*"});
                break;
            case TOKEN_FAMILY_NUMBER:
                tokens_.push_back(token{TOKEN_MUL, "*"});
                break;
            case TOKEN_FAMILY_OPERATION:
                break;
            case TOKEN_FAMILY_FUNCTION:
                tokens_.push_back(token{TOKEN_MUL, "*"});
                break;
            case TOKEN_FAMILY_PAR_LEFT:
                tokens_.push_back(token{TOKEN_MUL, "*"});
                break;
            case TOKEN_FAMILY_PAR_RIGHT:
               break;
            default:
                break;
            }
            
            break;
        default:
            break;
        }
    }

    token last = tokens[tokens.size()-1];
    tokens_.push_back(last);
    
    if (last.type == TOKEN_PAR_LEFT) {
        par_cnt++;
    }
    if (last.type == TOKEN_PAR_RIGHT) {
        par_cnt--;
    }

    if (par_cnt != 0) {
        throw std::invalid_argument("expression contains bad parentheses sequence");
    }

    return tokens_;
}

std::shared_ptr<sympp::expression<long double>> parse(std::vector<token>& tokens, int i, int j){
    // phase 0: for unary minus: return 0, eg (-x + y) -> ((0 - x) + y) 
    if (j < i) {
        return sympp::Number<long double>(0);
    }

    // phase 1: remove parentheses in the begin and in the end
    while ((tokens[i].type == TOKEN_PAR_LEFT) && (tokens[j].type == TOKEN_PAR_RIGHT)) {
        i++;
        j--;
    }

    // phase 2: find top-prescense pivot token (if exists)
    int par_cnt = 0;
    int p = i;
    int prescense = 99;

    for (int k = i; k <= j; ++k){
        if (tokens[k].type == TOKEN_PAR_LEFT) {
            par_cnt++;
            continue;
        }
        if (tokens[k].type == TOKEN_PAR_RIGHT) {
            par_cnt--;
            continue;
        }

        size_t cur_prescense = to_prescence(tokens[k].type);
        if ((par_cnt == 0) && (cur_prescense < prescense)) {
            p = k;
            prescense = cur_prescense;
        }
    }

    // phase 3: parse recursively
    token_type t = tokens[p].type;

    // std::cout << tokens[p].instance << std::endl;
    // for (int k = i; k <= j; ++k) {
    //     std::cout << tokens[k].type << "[" << tokens[k].instance << "]|";
    // }
    // std::cout << std::endl;

    long double x;
    switch (t){
    case TOKEN_SYMBOL:
        return sympp::Symbol<long double>(tokens[p].instance);

    case TOKEN_NUMBER:
        x = std::stold(tokens[p].instance, NULL);
        return sympp::Number<long double>(x);

    case TOKEN_POW:
        return parse(tokens, i, p-1) ^ parse(tokens, p+1, j);    

    case TOKEN_MUL:
        return parse(tokens, i, p-1) * parse(tokens, p+1, j);    

    case TOKEN_DIV:
        return parse(tokens, i, p-1) / parse(tokens, p+1, j);    

    case TOKEN_ADD:
        return parse(tokens, i, p-1) + parse(tokens, p+1, j);    

    case TOKEN_SUB:
        return parse(tokens, i, p-1) - parse(tokens, p+1, j);    
    
    case TOKEN_LN:
        return sympp::Ln(parse(tokens, p+1, j));

    case TOKEN_EXP:
        return sympp::Exp(parse(tokens, p+1, j));

    case TOKEN_SIN:
        return sympp::Sin(parse(tokens, p+1, j));

    case TOKEN_COS:
        return sympp::Cos(parse(tokens, p+1, j));

    default:
        break;
    }

    throw std::logic_error("unexpected parser token instance: " + tokens[p].instance);
}

}


namespace sympp {

std::shared_ptr<expression<long double>> Parse(std::string expr){
    std::vector<parsing::token> tokens;

    try {
        tokens = parsing::lexify(expr);

    } catch (std::exception& e) {
        std::stringstream ss;
        ss << "couldn't lexify input: " << e.what();
        
        throw std::invalid_argument(ss.str());
    }

    // for (int i = 0; i < tokens.size(); ++i) {
    //     std::cout << tokens[i].type << "[" << tokens[i].instance << "]|";
    // }
    // std::cout << std::endl;

    return parsing::parse(tokens, 0, tokens.size()-1);
};

}