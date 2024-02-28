#include <iostream>

class stack_child {
public:
    void set_data(int num) {
        this->data = num;
    }

    void set_ptr(stack_child *new_ptr) {
        this->ptr = new_ptr;
    }

    [[nodiscard]]
    int top() const {
        return this->data;
    }

    stack_child *pop() {
        stack_child *temp_ptr = this->ptr;
        delete(this);
        return temp_ptr;
    }

    stack_child *push(int num) {
        auto *child = new(stack_child);
        child->data = num;
        child->ptr = this;
        return child;
    }

private:
    int data;
    stack_child *ptr;
};

class stack {
public:
    stack() {
        this->ptr = nullptr;
    }

    ~stack() {
        while(this->ptr != nullptr) {
            this->pop();
        }
    }

    [[nodiscard]]
    bool empty() const {
        if (this->ptr == nullptr)
            return true;
        else
            return false;
    }

    [[nodiscard]]
    int top() const {
        if (!this->empty())
            return ptr->top();
        else
            exit(-1);
    }

    void push(int num) {
        if (!this->empty())
            this->ptr = this->ptr->push(num);
        else {
            this->ptr = new(stack_child);
            this->ptr->set_data(num);
            this->ptr->set_ptr(nullptr);
        }
    }

    void pop() {
        if (!this->empty())
            this->ptr = this->ptr->pop();
        else
            exit(-2);
    }

private:
    stack_child *ptr;
};

int main() {
    return 0;
}