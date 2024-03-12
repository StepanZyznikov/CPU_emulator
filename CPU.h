#include <iostream>
#include <vector>
#include "stack.h"
#include <fstream>
#include <string>
#include <map>

#ifndef CPU_EMULATOR_STACK_H
#define CPU_EMULATOR_STACK_H

#endif //CPU_EMULATOR_STACK_H

namespace cpu {
    class cpu {
    public:
        void begin() {
            if (this->exec)
                exit(1);
            this->exec = true;
        }

        void end() {
            if (!this->exec)
                exit(2);
            this->exec = false;
        }

        void push(int value0) {
            if (!this->exec)
                exit(3);
            this->stack.push(value0);
        }

        void pop() {
            if (!this->exec)
                exit(3);
            this->stack.pop();
        }

        void pushr(int reg_id) {
            if (!this->exec)
                exit(3);
            this->stack.push(this->reg[reg_id]);
        }

        void popr(int reg_id) {
            if (!this->exec)
                exit(3);
            if (this->stack.empty())
            {
                std::cout << "Stack has to have at least one numbers for POPR!" << std::endl;
                exit(5);
            }
            this->reg[reg_id] = this->stack.top();
            this->stack.pop();
        }

        void add() {
            if (!this->exec)
                exit(3);
            if (this->stack.empty())
            {
                std::cout << "Stack has to have at least two numbers for ADD!" << std::endl;
                exit(5);
            }
            int a = this->stack.top();
            this->stack.pop();
            if (this->stack.empty())
            {
                std::cout << "Stack has to have at least two numbers for ADD!" << std::endl;
                exit(5);
            }
            int b = this->stack.top();
            this->stack.push(a);
            this->stack.push(a + b);
        }

        void sub() {
            if (!this->exec)
                exit(3);
            if (this->stack.empty())
            {
                std::cout << "Stack has to have at least two numbers for SUB!" << std::endl;
                exit(5);
            }
            int a = this->stack.top();
            if (this->stack.empty())
            {
                std::cout << "Stack has to have at least two numbers for SUB!" << std::endl;
                exit(5);
            }
            this->stack.pop();
            int b = this->stack.top();
            this->stack.push(a);
            this->stack.push(a - b);
        }

        void mul() {
            if (!this->exec)
                exit(3);
            if (this->stack.empty())
            {
                std::cout << "Stack has to have at least two numbers for MUL!" << std::endl;
                exit(5);
            }
            int a = this->stack.top();
            this->stack.pop();
            if (this->stack.empty())
            {
                std::cout << "Stack has to have at least two numbers for MUL!" << std::endl;
                exit(5);
            }
            int b = this->stack.top();
            this->stack.push(a);
            this->stack.push(a * b);
        }

        void div() {
            if (!this->exec)
                exit(3);
            if (this->stack.empty())
            {
                std::cout << "Stack has to have at least two numbers for DIV!" << std::endl;
                exit(5);
            }
            int a = this->stack.top();
            this->stack.pop();
            if (this->stack.empty())
            {
                std::cout << "Stack has to have at least two numbers for DIV!" << std::endl;
                exit(5);
            }
            int b = this->stack.top();
            if (b == 0)
                {
                    std::cout << "Division by zero!!" << std::endl;
                    exit(6);
                }
            this->stack.push(a);
            this->stack.push(a / b);
        }

        void out()
        {
            if (!this->exec)
                exit(3);
            if (this->stack.empty())
            {
                std::cout << "Stack has to have at least one numbers for OUT!" << std::endl;
                exit(5);
            }
            std::cout << this->stack.top() << std::endl;
            this->stack.pop();
        }

        void in()
        {
            if (!this->exec)
                exit(3);
            int a;
            std::cin >> a;
            this->stack.push(a);
        }

        std::vector<int> reg;

    private:
        bool exec = false;
        st::stack<int> stack;
    };

    void execute_file(const std::string& FILE_NAME)
    {
        std::map <std::string, int> mapping;
        mapping["BEGIN"] = 1;
        mapping["END"]   = 2;
        mapping["PUSH"]  = 3;
        mapping["POP"]   = 4;
        mapping["PUSHR"] = 5;
        mapping["POPR"]  = 6;
        mapping["ADD"]   = 7;
        mapping["SUB"]   = 8;
        mapping["MUL"]   = 9;
        mapping["DIV"]   = 10;
        mapping["OUT"]   = 11;
        mapping["IN"]    = 12;

        std::ifstream FILE;
        FILE.open(FILE_NAME);

        std::string comm;
        cpu a;

        while (FILE >> comm)
        {
            switch (mapping[comm])
            {
                case 0: {
                    std::cout << "Syntaxis error!" << std::endl;
                    exit(4);
                }
                case 1: {
                    a.begin();
                    break;
                }
                case 2: {
                    a.end();
                    break;
                }
                case 3: {
                    int value0;
                    FILE >> value0;
                    a.push(value0);
                    break;
                }
                case 4: {
                    a.pop();
                    break;
                }
                case 5: {
                    int reg0;
                    FILE >> reg0;
                    a.pushr(reg0);
                    break;
                }
                case 6: {
                    int reg0;
                    FILE >> reg0;
                    a.popr(reg0);
                    break;
                }
                case 7: {
                    a.add();
                    break;
                }
                case 8: {
                    a.sub();
                    break;
                }
                case 9: {
                    a.mul();
                    break;
                }
                case 10: {
                    a.div();
                    break;
                }
                case 11: {
                    a.out();
                    break;
                }
                case 12: {
                    a.in();
                    break;
                }
            }
        }

        FILE.close();
    }
}