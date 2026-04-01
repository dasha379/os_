#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <stack>
#include <set>
#include <map>
#include <cstdlib>

enum class TokenType{
    VAR,
    AND,
    OR,
    NOT,
    LPAREN,
    RPAREN,
    END
};

struct Token{
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string v = "") : type(t), value(v) {}
    Token() : type(TokenType::END), value("") {}
};

class Lexer{
    private:
    std::string input;
    size_t pos;

    void skip_whitespace(){
        while (pos < input.length() && isspace(input[pos])){
            pos++;
        }
    }

    public:
    Lexer(const std::string expr) : input(expr), pos(0) {}

    Token get_next(){
        skip_whitespace();
        if (pos >= input.length()){
            return Token(TokenType::END);
        }

        char c = input[pos];

        if (pos + 2 < input.length() && input.substr(pos, 3) == "AND"){
            pos += 3;
            return Token(TokenType::AND);
        }

        if (pos + 1 < input.length() && input.substr(pos, 2) == "OR"){
            pos += 2;
            return Token(TokenType::OR);
        }

        if (pos + 2 < input.length() && input.substr(pos, 3) == "NOT"){
            pos += 3;
            return Token(TokenType::NOT);
        }

        if (isalpha(c) && isupper(c)){
            pos++;
            return Token(TokenType::VAR, std::string(1, c));
        } else {
            if (islower(c)){
                std::cerr << "Error: wrong input. aborting.\n";
                std::exit(EXIT_FAILURE);
            }
        }

        if (c == '('){
            pos++;
            return Token(TokenType::LPAREN);
        }

        if (c == ')'){
            pos++;
            return Token(TokenType::RPAREN);
        }
        return Token(TokenType::END);
    }
};

class Parser{
    private:
    Lexer lexer;
    Token token_cur;

    void get(){
        token_cur = lexer.get_next();
    }

    int precedence(TokenType type){
        switch (type)
        {
        case TokenType::NOT:
            return 3;
            break;
        case TokenType::AND:
            return 2;
            break;
        case TokenType::OR:
            return 1;
            break;
        default:
            return 0;
            break;
        }
    }

    public:
    Parser(const std::string& expr) : lexer(expr), token_cur(){
        get();
    }

    std::vector<Token> f(){
        std::vector<Token> output;
        std::stack<Token> operations;

        while (token_cur.type != TokenType::END){
            switch(token_cur.type){
                case TokenType::VAR:
                    output.push_back(token_cur);
                    break;
                case TokenType::AND:
                case TokenType::OR:
                    while (!operations.empty() && (precedence(operations.top().type) >= precedence(token_cur.type)) && operations.top().type != TokenType::LPAREN){
                        output.push_back(operations.top());
                        operations.pop();
                    }
                    break;
                case TokenType::NOT:
                    operations.push(token_cur);
                    break;
                case TokenType::LPAREN:
                    operations.push(token_cur);
                    break;
                case TokenType::RPAREN:
                    while (!operations.empty() && operations.top().type != TokenType::LPAREN){
                        output.push_back(operations.top());
                        operations.pop();
                    }
                    if (operations.top().type == TokenType::LPAREN){
                        operations.pop();
                    }
                    break;
                default: break;
            }
            get();
        }
        return output;
    }

    std::set<char> vars_collect(const std::vector<Token>& dict){
        std::set<char> vars;
        for (auto a : dict){
            if (a.type == TokenType::VAR){
                vars.insert(a.value[0]);
            }
        }
        return vars;
    }

    bool compute(const std::vector<Token>& dict, const std::map<char, bool>& values){
        std::stack<bool> st;
        for(auto a : dict){
            switch(a.type){
                case TokenType::VAR:
                    st.push(values.at(a.value[0]));
                    break;
                case TokenType::AND: {
                    if (st.size() < 2) return false;
                    bool tmp1 = st.top();
                    st.pop();
                    bool tmp2 = st.top();
                    st.pop();
                    st.push(tmp1 && tmp2);
                    break;
                }
                case TokenType::OR: {
                    if (st.size() < 2) return false;
                    bool tmp3 = st.top();
                    st.pop();
                    bool tmp4 = st.top();
                    st.pop();
                    st.push(tmp3 || tmp4);
                    break;
                }
                case TokenType::NOT: {
                    if (st.empty()) return false;
                    bool tmp5 = st.top();
                    st.pop();
                    st.push(!tmp5);
                    break;
                }
                default: break;
            }
        }
        if (!st.empty())
            return st.top();
        else return false;
    }

    void print_truth_table(const std::vector<Token>& dict){
        std::set<char> vars = vars_collect(dict);
        std::vector<char> vars1(vars.begin(), vars.end());

        for (char c : vars1){
            std::cout << c << " ";
        }
        std::cout << "Result\n";

        int n = vars1.size();
        int comb = 1 << n;

        for (int i = 0; i < comb; ++i){
            std::map<char, bool> values;
            for (int j = 0; j < n; ++j){
                bool v = (1 << (n - 1 - j)) & i;
                values[vars1[j]] = v;
                std::cout << v << " ";
            }
            bool res = compute(dict, values);
            std::cout << res << '\n';
        }
    }
};

int main(){
    std::string expr;
    std::getline(std::cin, expr, '\n');
    Parser parser(expr);
    std::vector<Token> str = parser.f();
    parser.print_truth_table(str);
    return 0;
}

