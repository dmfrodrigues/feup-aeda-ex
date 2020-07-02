# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
private:
    stack<T> s;
    stack<T> m;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const
{
	return s.empty();
}

//a alterar
template <class T> 
T& StackExt<T>::top(){
    return s.top();
}

//a alterar
template <class T> 
void StackExt<T>::pop(){
    if(s.top() == m.top()) m.pop();
    s.pop();
}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val){
    if(m.empty() || val <= m.top()) m.push(val);
    s.push(val);
}

//a alterar
template <class T> 
T& StackExt<T>::findMin()
{
    return m.top();
}

