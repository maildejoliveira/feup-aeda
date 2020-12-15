# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack<T> s;
    stack<T> min;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

template <class T> 
bool StackExt<T>::empty() const
{
    return s.empty();
}

template <class T> 
T& StackExt<T>::top()
{
    return s.top();
}

template <class T> 
void StackExt<T>::pop()
{
    s.pop();
    min.pop();
}

template <class T> 
void StackExt<T>::push(const T & val)
{
    s.push(val);
    if(min.empty()){
        min.push(val);
    }
    else if(val<min.top()){
        min.push(val);
    }
    else min.push(min.top());
}

template <class T> 
T& StackExt<T>::findMin()
{
    cout << min.top();
    return min.top();
}

