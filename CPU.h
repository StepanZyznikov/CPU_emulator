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
        mapping["JMP"]   = 13;
        mapping["JEQ"]   = 14;
        mapping["JNE"]   = 15;
        mapping["JA"]    = 16;
        mapping["JAE"]   = 17;
        mapping["JB"]    = 18;
        mapping["JBE"]   = 19;
        mapping["CALL"]  = 20;
        mapping["RET"]   = 21;

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
                std::cout << "Syntax error!" << std::endl;
                exit(4);
            }
            if (comm_code > 0)
            {
                BFILE << std::to_string(comm_code);
                if (comm_code == 3 || comm_code == 5 || comm_code == 6 || (comm_code >= 13 && comm_code <= 20))
                {
                    std::string value;
                    FILE >> value;
                    BFILE << " " << value << std::endl;
                }
                else
                    BFILE << std::endl;
            }
        }
    }

    class cpu {
    public:
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
                this->comms.push_back(comm_code);
                if (comm_code == 3 || comm_code == 5 || comm_code == 6 || (comm_code >= 13 && comm_code <= 20)) {
                    std::string arg;
                    BFILE >> arg;
                    this->comms.push_back(std::stoi(arg));
                }
                else
                    this->comms.push_back(0);
            }
            this->curr_label = 0;
            while (this->curr_label < this->comms.size())
            {
                int curr_comm = this->comms[this->curr_label];
                switch (curr_comm)
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
                        this->push(this->comms[this->curr_label+1]);
                        break;
                    }
                    case 4: {
                        this->pop();
                        break;
                    }
                    case 5: {
                        this->pushr(this->comms[this->curr_label+1]);
                        break;
                    }
                    case 6: {
                        this->popr(this->comms[this->curr_label+1]);
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
                    case 13: {
                        this->jmp(this->comms[this->curr_label+1]);
                        break;
                    }
                    case 14: {
                        this->jeq(this->comms[this->curr_label+1]);
                        break;
                    }
                    case 15: {
                        this->jne(this->comms[this->curr_label+1]);
                        break;
                    }
                    case 16: {
                        this->ja(this->comms[this->curr_label+1]);
                        break;
                    }
                    case 17: {
                        this->jae(this->comms[this->curr_label+1]);
                        break;
                    }
                    case 18: {
                        this->jb(this->comms[this->curr_label+1]);
                        break;
                    }
                    case 19: {
                        this->jbe(this->comms[this->curr_label+1]);
                        break;
                    }
                    case 20: {
                        this->call(this->comms[this->curr_label+1]);
                        break;
                    }
                    case 21: {
                        this->ret();
                        break;
                    }
                }
                this->curr_label += 2;
            }
        }

        void begin() {
            this->exec = true;
        }

        void end() {
            this->exec = false;
        }

        void push(int value0) {
            if (this->exec)
                this->stack.push(value0);
        }

        void pop() {
            if (this->exec)
                this->stack.pop();
        }

        void pushr(int reg_id) {
            if (this->exec)
                this->stack.push(this->reg[reg_id]);
        }

        void popr(int reg_id) {
            if (this->exec) {
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least one numbers for POPR!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                this->reg[reg_id] = this->stack.top();
                this->stack.pop();
            }
        }

        void add() {
            if (this->exec) {
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for ADD!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int a = this->stack.top();
                this->stack.pop();
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for ADD!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int b = this->stack.top();
                this->stack.push(a);
                this->stack.push(a + b);
            }
        }

        void sub() {
            if (this->exec) {
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for SUB!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int a = this->stack.top();
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for SUB!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                this->stack.pop();
                int b = this->stack.top();
                this->stack.push(a);
                this->stack.push(a - b);
            }
        }

        void mul() {
            if (this->exec) {
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for MUL!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int a = this->stack.top();
                this->stack.pop();
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for MUL!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int b = this->stack.top();
                this->stack.push(a);
                this->stack.push(a * b);
            }
        }

        void div() {
            if (this->exec) {
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for DIV!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int a = this->stack.top();
                this->stack.pop();
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for DIV!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int b = this->stack.top();
                if (b == 0) {
                    std::cout << "Division by zero!!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(6);
                }
                this->stack.push(a);
                this->stack.push(a / b);
            }
        }

        void out()
        {
            if (this->exec) {
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least one numbers for OUT!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                std::cout << this->stack.top() << std::endl;
                this->stack.pop();
            }
        }

        void in() {
            if (this->exec) {
                int a;
                std::cin >> a;
                this->stack.push(a);
            }
        }

        void jmp(int label)
        {
            if (this->exec)
                this->curr_label = 2 * (label - 1);
        }

        void jeq(int label)
        {
            if (this->exec) {
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for JEQ!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int a = this->stack.top();
                this->stack.pop();
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for JEQ!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int b = this->stack.top();
                this->stack.push(a);
                if (a == b)
                    this->curr_label = 2 * (label - 1);
            }
        }

        void jne(int label)
        {
            if (this->exec) {
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for JNE!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int a = this->stack.top();
                this->stack.pop();
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for JNE!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int b = this->stack.top();
                this->stack.push(a);
                if (a != b)
                    this->curr_label = 2 * (label - 1);
            }
        }

        void ja(int label)
        {
            if (this->exec) {
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for JA!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int a = this->stack.top();
                this->stack.pop();
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for JA!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int b = this->stack.top();
                this->stack.push(a);
                if (a > b)
                    this->curr_label = 2 * (label - 1);
            }
        }

        void jae(int label)
        {
            if (this->exec) {
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for JAE!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int a = this->stack.top();
                this->stack.pop();
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for JAE!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int b = this->stack.top();
                this->stack.push(a);
                if (a >= b)
                    this->curr_label = 2 * (label - 1);
            }
        }

        void jb(int label)
        {
            if (this->exec) {
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for JB!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int a = this->stack.top();
                this->stack.pop();
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for JB!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int b = this->stack.top();
                this->stack.push(a);
                if (a < b)
                    this->curr_label = 2 * (label - 1);
            }
        }

        void jbe(int label)
        {
            if (this->exec) {
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for JBE!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int a = this->stack.top();
                this->stack.pop();
                if (this->stack.empty()) {
                    std::cout << "Stack has to have at least two numbers for JBE!" << std::endl;
                    std::cout << "Line: " << curr_label / 2 << std::endl;
                    exit(5);
                }
                int b = this->stack.top();
                this->stack.push(a);
                if (a <= b)
                    this->curr_label = 2 * (label - 1);
            }
        }

        void call(int label)
        {
            if (this->exec) {

                this->return_label.push(this->curr_label + 2);
                this->curr_label = 2 * (label - 1);
            }
        }

        void ret()
        {
            if (this->exec) {
                this->curr_label = this->return_label.top() - 2;
                this->return_label.pop();
            }
        }

    private:
        bool exec = false;
        st::stack<int> stack;
        std::deque<int> reg;
        std::deque<int> comms;
        int curr_label;
        st::stack<int> return_label;
    };
}