#include <vector>
#include <iostream>

using namespace std;

class StackEmpty : public runtime_error {
public:
    explicit StackEmpty(const char* message) : runtime_error(message) {}
};

class StackFull : public runtime_error {
private:
    int value;
public:
    StackFull(const char* str, int val) : runtime_error(str), value(val){    }

    int GetValue() const {
        return value;
    }
};

class InvalidSize : public invalid_argument {
public:
    InvalidSize(const char* str): invalid_argument(str) {    }
};


class IntStack {
public:
    IntStack(int MaxSize) {
        if (MaxSize < 0) {
            throw InvalidSize("Cannot create a negative size stack");
        } 
        
        else {
            data.resize(MaxSize);
        }
        cur_index = 0;
    }

    void push(int new_data) {
        if (cur_index == data.size()) {
            throw StackFull("Push to full stack", new_data);
        } 
        
        else {
            data.at(cur_index) = new_data;
            cur_index++;
        }
    }

    int pop() {
        if (cur_index == 0) {
            throw StackEmpty("Pop from empty stack");
        } 
        
        else {
            cur_index--;
            return data.at(cur_index);
        }
    }

private:
    vector<int> data;
    unsigned int cur_index;
};

int main() {
    
    try {
        IntStack c_test(-10);
        c_test.push(3);
        c_test.push(4);
        c_test.pop();
        c_test.pop();
    } 
    catch (InvalidSize& e) {
        cerr << e.what() << endl;
    } 

    try {
        IntStack push_test(5);
        
        for (unsigned int i = 0; i < 7; i++) {
            push_test.push(i);
        }
    } 
    catch (const StackFull& e) {
        cerr << e.what() << ", value = " << e.GetValue() << endl;
    }

    try {
        IntStack pop_test(2);
    
        pop_test.push(1);
        pop_test.push(2);
        pop_test.pop();
        pop_test.pop();
        pop_test.pop(); 
    } 
    catch (const StackEmpty& e) {
        cerr << e.what() << endl;
    }

    cout << "Completed!" ;
    return 0; 
}

