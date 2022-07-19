#pragma once
#include <shared_mutex>
#include <thread>

template <class T>
class TQueue
{
private:
	struct Node {
		Node* next;
		T* data;
		Node(T data);
		~Node();
	};
	Node* head;
	Node* tail;
	std::shared_mutex mtx;
public:
	TQueue();
	TQueue(const TQueue& other) = delete;
	TQueue& operator =(const TQueue& other) = delete;
	void Push(T data);
	bool TryFront(T& front);
	bool TryBack(T& back);
	bool IsEmpty();
	bool TryPop(T& deleter);
	~TQueue();
};
template <class T> TQueue<T>::Node::Node(T data) {
	this->next = nullptr;
	this->data = new T;
	*this->data = std::move(data);
}
template <class T> TQueue<T>::Node::~Node() {
	delete this->data;
}
template <class T> TQueue<T>::TQueue() {
	this->head = nullptr;
	this->tail = nullptr;
}
template <class T> void TQueue<T>::Push(T data) {
	Node* node = new Node(std::move(data));
	this->mtx.lock();
	if (this->head==nullptr) {
		this->head = node;
		this->tail = node;
	}
	else {
		this->tail->next = node;
		this->tail = this->tail->next;
	}
	this->mtx.unlock();
}
template <class T> bool TQueue<T>::TryFront(T& front) {
	this->mtx.lock_shared();
	if (this->head==nullptr) {
		this->mtx.unlock_shared();
		return false;
	}
	front = *(this->head->data);
	this->mtx.unlock_shared();
	return true;
}
template <class T> bool TQueue<T>::TryBack(T& back) {
	this->mtx.lock_shared();
	if (this->head == nullptr) {
		this->mtx.unlock_shared();
		return false;
	}
	back = *(this->tail->data);
	this->mtx.unlock_shared();
	return true;
}
template <class T> bool TQueue<T>::IsEmpty() {
	this->mtx.lock_shared();
	bool res = this->head == nullptr;
	this->mtx.unlock_shared();
	return res;
}
template <class T> bool TQueue<T>::TryPop(T& deleter) {
	this->mtx.lock();
	if (this->head == nullptr) {
		this->mtx.unlock();
		return false;
	}
	deleter = std::move(*(this->head->data));
	Node* oldHead = this->head;
	this->head = this->head->next;
	delete oldHead;
	this->mtx.unlock();
	return true;
}
template <class T> TQueue<T>::~TQueue() {
	Node* cur = this->head;
	while (cur != nullptr) {
		Node* oldCur = cur;
		cur = cur->next;
		delete oldCur;
	}
}

