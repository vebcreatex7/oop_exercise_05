
#ifndef STACK_H
#define STACK_H 1

#include <memory>
#include <iostream>
#include <iterator>



namespace containers {


template <class T>
class TStack {
private:

	struct Node;


public:


	class forward_iterator {
	public:
		using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
		forward_iterator (Node* ptr) : ptr_(ptr) {};
		T& operator* ();
		forward_iterator& operator++ ();
		forward_iterator operator++ (int);
		bool operator== (const forward_iterator& o) const;
		bool operator!= (const forward_iterator& o) const;
		
	private:
		Node* ptr_ = nullptr;
		friend TStack;
	};
	forward_iterator begin();
	forward_iterator end();
	void pop();
	T& top();
	void push(const T& value);
	void erase(const forward_iterator& it);
	void insert(forward_iterator& it, const T& val);
	void advance(forward_iterator& it, int idx);
	void print();
private:
	struct Node {
		T value;
		std::shared_ptr<Node> following = nullptr;
		forward_iterator next();
		Node(const T& val, std::shared_ptr<Node> nxt) :
			value(val), following(nxt) {};
	};
	std::shared_ptr<Node> head = nullptr;


};

template <class T>
typename TStack<T>::forward_iterator TStack<T>::Node::next() {
	return following.get();
}

template <class T>
typename TStack<T>::forward_iterator TStack<T>::begin() {
	return head.get();
}

template <class T>
typename TStack<T>::forward_iterator TStack<T>::end() {
	return nullptr;
}

template <class T>
T& TStack<T>::forward_iterator::operator* () {
	return ptr_->value;
}

template <class T>
typename TStack<T>::forward_iterator& TStack<T>::forward_iterator::operator++ () {
	*this = ptr_->next();
	return *this;
}

template <class T>
typename TStack<T>::forward_iterator TStack<T>::forward_iterator::operator++ (int) {
	forward_iterator prev =*this;
	++this;
	return prev;
}

template <class T>
bool TStack<T>::forward_iterator::operator== (const forward_iterator& o) const{
	return ptr_ == o.ptr_;
}

template <class T>
bool TStack<T>::forward_iterator::operator!= (const forward_iterator& o) const{
	return ptr_ != o.ptr_;
}



template <class T>
void TStack<T>::push(const T& value) {
	std::shared_ptr<Node> NewNode(new Node(value, nullptr));
	NewNode->following = head;
	head = NewNode;
}

template<class T>
void TStack<T>::pop() {
	if (head.get() == nullptr) {
		throw std::logic_error("Stack is empty\n");
	} else {
		head = head->following;
	}
}

template <class T>
T& TStack<T>::top() {
	if (head.get() == nullptr) throw std::logic_error("Stack is empty\n");
	return head->value;
}


template <class T>
void TStack<T>::print() {
	std::shared_ptr<Node> tmp;
	tmp = head;
	while (tmp != nullptr) {
		std::cout << tmp->value << " ";
		tmp = tmp->following;
	}
}


template <class T>
void TStack<T>::insert(forward_iterator& it, const T& value) {
	std::shared_ptr<Node> NewNode(new Node(value, nullptr));
	if (it.ptr_ == head.get()) {
		this->push(value);
		return;
	}
	auto tmp = this->begin();
	auto prev = tmp;
	while (tmp.ptr_ != it.ptr_) {
		if (tmp.ptr_ == nullptr && tmp.ptr_ != it.ptr_) throw std::logic_error("Out of range");
		prev.ptr_ = tmp.ptr_;
		++tmp;
	}
	NewNode->following = prev.ptr_->following;
	prev.ptr_->following = NewNode;

	return;

}

template <class T>
void TStack<T>::erase(const forward_iterator& it) {
	if (it.ptr_ == head.get()) {
		this->pop();
		return;
	}
	auto tmp = this->begin();
	auto prev =tmp;
	while (tmp.ptr_ != it.ptr_) {

		prev.ptr_ = tmp.ptr_;
		++tmp;
		if (tmp.ptr_ == nullptr) {
			throw std::logic_error("Out of range");
			
		}
	}
	prev.ptr_->following = tmp.ptr_->following;

	return;

}



template <class T>
void TStack<T>::advance(forward_iterator& it, int idx) {
	it = this->begin();
	if (it.ptr_ == nullptr && idx > 0) throw std::logic_error("Out of range");
	int i = 0;
	while (i < idx) {
		if (it.ptr_->following == nullptr && i < idx - 1) {
			
			throw std::logic_error("Out of range\n");
		}
		++it;
		++i;
		
	}
}

}

#endif


	




