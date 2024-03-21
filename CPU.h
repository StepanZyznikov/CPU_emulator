#include <iostream>
#include <deque>
#include "stack.h"
#include <fstream>
#include <string>
#include <map>

#ifndef CPU_EMULATOR_STACK_H
#define CPU_EMULATOR_STACK_H

#endif //CPU_EMULATOR_STACK_H

namespace cpu {
    void file_to_bite_code(const std::string& FILE_NAME, const std::string& BITE_CODE_FILE_NAME)
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
        std::ofstream BFILE;
        BFILE.open(BITE_CODE_FILE_NAME);

        if (!FILE.is_open())
        {
            std::cout << "No such file in " << FILE_NAME << std::endl;
            exit(8);
        }

        std::string comm;
        int comm_code;

        while (FILE >> comm)
        {
            comm_code = mapping[comm];
            if (comm_code == 0)
            {
                std::cout << "Syntaxis error!" << std::endl;
                exit(4);
            }
            if (comm_code > 0)
            {
                BFILE << std::to_string(comm_code);
                if (comm_code == 3 || comm_code == 5 || comm_code == 6)
                {
                    std::string value;
                    FILE >> value;
                    for (int i = 0; i < value.length(); i += 1) {
                        if (!isdigit(value[i])) {
                            std::cout << "Not a number!";
                            exit(7);
                        }
                    }
                    BFILE << " " << value << std::endl;
                }
                else
                    BFILE << std::endl;
            }
        }
    }

    class cpu {
    public:
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

            if (!FILE.is_open())
            {
                std::cout << "No such file in " << FILE_NAME << std::endl;
                exit(8);
            }

            std::string comm;

            while (FILE >> comm)
            {
                switch (mapping[comm])
                {
                    case 0: {
                        std::cout << "Syntaxis error!" << std::endl;
                        exit(4);
                    }
                    case 1: {
                        this->begin();
                        break;
                    }
                    case 2: {
                        this->end();
                        break;
                    }
                    case 3: {
                        std::string value0;
                        FILE >> value0;
                        for (int i = 0; i < value0.length(); i += 1) {
                            if (!isdigit(value0[i])) {
                                std::cout << "Not a number after PUSH!";
                                exit(7);
                            }
                        }
                        this->push(std::stoi(value0));
                        break;
                    }
                    case 4: {
                        this->pop();
                        break;
                    }
                    case 5: {
                        std::string reg0;
                        FILE >> reg0;
                        for (int i = 0; i < reg0.length(); i += 1) {
                            if (!isdigit(reg0[i])) {
                                std::cout << "Not a number after PUSHR!";
                                exit(7);
                            }
                        }
                        this->pushr(std::stoi(reg0));
                        break;
                    }
                    case 6: {
                        std::string reg0;
                        FILE >> reg0;
                        for (int i = 0; i < reg0.length(); i += 1) {
                            if (!isdigit(reg0[i])) {
                                std::cout << "Not a number after POPR!";
                                exit(7);
                            }
                        }
                        this->popr(std::stoi(reg0));
                        break;
                    }
                    case 7: {
                        this->add();
                        break;
                    }
                    case 8: {
                        this->sub();
                        break;
                    }
                    case 9: {
                        this->mul();
                        break;
                    }
                    case 10: {
                        this->div();
                        break;
                    }
                    case 11: {
                        this->out();
                        break;
                    }
                    case 12: {
                        this->in();
                        break;
                    }
                }
            }

            if (this->exec)
                std::cout << "Warning! CPU is running!" << std::endl;
            FILE.close();
        }

        void execute_bite_code_file(const std::string& BITE_CODE_FILE_NAME)
        {
            std::ifstream BFILE;
            BFILE.open(BITE_CODE_FILE_NAME);

            if (!BFILE.is_open())
            {
                std::cout << "No such file in " << BITE_CODE_FILE_NAME << std::endl;
                exit(8);
            }

            std::string comm;
            int comm_code;

            while (BFILE >> comm)
            {
                comm_code = std::stoi(comm);
                switch (comm_code)
                {
                    case 1: {
                        this->begin();
                        break;
                    }
                    case 2: {
                        this->end();
                        break;
                    }
                    case 3: {
                        std::string value0;
                        BFILE >> value0;
                        this->push(std::stoi(value0));
                        break;
                    }
                    case 4: {
                        this->pop();
                        break;
                    }
                    case 5: {
                        std::string reg0;
                        BFILE >> reg0;
                        this->pushr(std::stoi(reg0));
                        break;
                    }
                    case 6: {
                        std::string reg0;
                        BFILE >> reg0;
                        this->popr(std::stoi(reg0));
                        break;
                    }
                    case 7: {
                        this->add();
                        break;
                    }
                    case 8: {
                        this->sub();
                        break;
                    }
                    case 9: {
                        this->mul();
                        break;
                    }
                    case 10: {
                        this->div();
                        break;
                    }
                    case 11: {
                        this->out();
                        break;
                    }
                    case 12: {
                        this->in();
                        break;
                    }
                }
            }
        }

        void begin() {
            this->exec = true;
        }

        void end() {
            this->exec = false;
        }

        void push(int value0) {
            this->stack.push(value0);
        }

        void pop() {
            this->stack.pop();
        }

        void pushr(int reg_id) {
            this->stack.push(this->reg[reg_id]);
        }

        void popr(int reg_id) {
            if (this->stack.empty())
            {
                std::cout << "Stack has to have at least one numbers for POPR!" << std::endl;
                exit(5);
            }
            this->reg[reg_id] = this->stack.top();
            this->stack.pop();
        }

        void add() {
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
            int a;
            std::cin >> a;
            this->stack.push(a);
        }

        std::deque<int> reg;

    private:
        bool exec = false;
        st::stack<int> stack;
    };
}