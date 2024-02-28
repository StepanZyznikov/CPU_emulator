#include <iostream>

class stack_child {
public:
    void set_data(int num) {
        this->data = num;
    }

    void set_ptr(stack_child *new_ptr) {
        this->ptr = new_ptr;
    }

    stack_child *copy()
    {
        auto final_ptr = new(stack_child);
        stack_child *curr_ptr = final_ptr;
        stack_child *iter_ptr = this;
        while (iter_ptr != nullptr)
        {
            curr_ptr->data = iter_ptr->data;

            if (iter_ptr->ptr != nullptr) {
                curr_ptr->ptr = new(stack_child);
                curr_ptr = curr_ptr->ptr;
            }
            else
                curr_ptr->ptr = nullptr;
            iter_ptr = iter_ptr->ptr;
        }
        return final_ptr;
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

    stack(const stack &orig)
    {
        this->ptr = new(stack_child);
        this->ptr = orig.ptr->copy();
    }

    stack& operator=(const stack &orig)
    {
        this->ptr = new(stack_child);
        this->ptr = orig.ptr->copy();
        return *this;
    }

    stack(stack&& moved) noexcept {
        this->ptr = moved.ptr;
        moved.ptr=nullptr;
    }

    stack& operator=(stack&& moved) noexcept {
        this->ptr = moved.ptr;
        moved.ptr=nullptr;
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