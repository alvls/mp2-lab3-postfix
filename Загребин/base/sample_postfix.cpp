#include "postfix.h"

int main(){
    TPostfix postfix; std::string expression; int choice = 0;
    try {
        do {
            std::cout << "Enter an arithmetic expression (0.1 format): "; // expression
            std::getline(std::cin, expression);
            postfix.SetInfix(expression);
            try {
                std::cout << "Postfix form: " << postfix.ToPostfix() << std::endl;;
            }catch (std::string s) {
                std::cout << "Error: " << s << std::endl;
                goto next;
            }

            std::cout << "Count it? No-0, Yes-1: ";
            std::cin >> choice;
            while (choice) {
                try {
                    std::cout << "Answer: " << postfix.Calculate() << std::endl;
                }
                catch (std::string s) {
                    std::cout << "Error: " << s << std::endl;
                }
                std::cout << "Count it again? No-0, Yes-1: ";
                std::cin >> choice;
            }

        next:
            std::cout << "Go to beginning? No-0, Yes-1: ";
            std::cin >> choice;
            std::getline(std::cin, expression);// clear thread  
        } while (choice);
    }catch (...) {
        std::cout << "Fatal Error! " << std::endl;
    }

  return 0;
}
