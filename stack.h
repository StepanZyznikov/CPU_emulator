#include <iostream>

#ifndef CPU_EMULATOR_STACK_H
#define CPU_EMULATOR_STACK_H

#endif //CPU_EMULATOR_STACK_H

namespace st {
    template<typename Type>
    class stack_child {
    public:
        void set_data(Type in_data) {
            this->data = in_data;
        }

        void set_ptr(stack_child *new_ptr) {
            this->ptr = new_ptr;
        }

        stack_child *copy() {
            auto final_ptr = new stack_child;
            stack_child *curr_ptr = final_ptr;
            stack_child *iter_ptr = this;
            while (iter_ptr != nullptr) {
                curr_ptr->data = iter_ptr->data;

                if (iter_ptr->ptr != nullptr) {
                    curr_ptr->ptr = new stack_child;
                    curr_ptr = curr_ptr->ptr;
                } else
                    curr_ptr->ptr = nullptr;
                iter_ptr = iter_ptr->ptr;
            }
            return final_ptr;
        }

        [[nodiscard]]
        Type top() const {
            return this->data;
        }

        stack_child *pop() {
            stack_child *temp_ptr = this->ptr;
            delete[] this;
            return temp_ptr;
        }

        stack_child *push(Type in_data) {
            auto *child = new stack_child;
            child->data = in_data;
            child->ptr = this;
            return child;
        }

    private:
        Type data;
        stack_child *ptr;
    };


    template<typename Type>
    class stack {
    public:
        stack() {
            this->ptr = nullptr;
        }

        ~stack() {
            while (this->ptr != nullptr) {
                this->pop();
            }
        }

        stack(const stack &orig) {
            this->ptr = new stack_child<Type>;
            this->ptr = orig.ptr->copy();
        }

        stack &operator=(const stack &orig) {
            this->ptr = new stack_child<Type>;
            this->ptr = orig.ptr->copy();
            return *this;
        }

        stack(stack &&moved) noexcept {
            this->ptr = moved.ptr;
            moved.ptr = nullptr;
        }

        stack &operator=(stack &&moved) noexcept {
            this->ptr = moved.ptr;
            moved.ptr = nullptr;
            return *this;
        }

        [[nodiscard]]
        bool empty() const {
            if (this->ptr == nullptr)
                return true;
            else
                return false;
        }

        [[nodiscard]]
        Type top() const {
            if (!this->empty())
                return ptr->top();
            else
            {
                std::cout << "Attempt to access top of empty stack!";
                exit(-1);
            }
        }

        void push(Type num) {
            if (!this->empty())
                this->ptr = this->ptr->push(num);
            else {
                this->ptr = new stack_child<Type>;
                this->ptr->set_data(num);
                this->ptr->set_ptr(nullptr);
            }
        }

        void pop() {
            if (!this->empty())
                this->ptr = this->ptr->pop();
        }

    private:
        stack_child<Type> *ptr;
    };
}