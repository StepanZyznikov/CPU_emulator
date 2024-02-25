#include <iostream>

class stack{
public:
    stack()
    {
        this->ptr = nullptr;
        this->data = 0;
    }

    ~stack()
    {
        stack* curr_ptr = this->ptr;
        stack* delete_ptr;
        while (curr_ptr != nullptr)
        {
            delete_ptr = curr_ptr;
            curr_ptr = curr_ptr->ptr;
            // Delete the current node without calling its destructor
            //delete(delete_ptr);
        }
    }

    [[nodiscard]]
    bool empty() const
    {
        if (this->ptr == nullptr)
            return true;
        else
            return false;
    }

    [[nodiscard]]
    int top() const
    {
        if (!this->empty())
            return this->ptr->data;
        else
            return -192;
    }

    void push(int num)
    {
        if (this->empty())
        {
            this->ptr = new(stack);
            this->ptr->data = num;
            this->ptr->ptr = nullptr;
        }
        else
        {
            stack *temp_ptr = this->ptr;
            this->ptr = new(stack);
            this->ptr->ptr = temp_ptr;
            this->ptr->data = num;
        }
    }

    void pop()
    {
        if (!this->empty())
        {
            stack *temp_ptr = this->ptr->ptr;
            delete(this->ptr);
            this->ptr = temp_ptr;
        }
    }
private:
    int data;
    stack* ptr;
};

int main()
{
    stack a;
    for (int i = 0; i < 5; i += 1)
    {
        a.push(i);
    }

    return 0;
}