#pragma once
#include<iostream>
template<class T>
class Object {
private:
	int a;
	T* arr;
public:
	Object() {
		a = 0;
		arr = nullptr;
	}
	Object(int a) {
		std::cout << "Constructor" << std::endl;
		this->a = a;
		this->arr = new T[a];
	}
	Object(const Object& other) {
		std::cout << "Copy" << std::endl;
		this->a = other.a;
		this->arr = new T[a];
		memcpy(this->arr, other.arr, sizeof(T) * other.a);
	}
	Object(Object&& other) {
		std::cout << "Move" << std::endl;
		this->a = other.a;
		this->arr = other.arr;
		other.a = 0;
		other.arr = nullptr;
	}
	int get_a() {
		return this->a;
	}
	T operator[](const int index) const {
		return this->arr[index];
	}
	Object& operator=(const Object& other) {
		if (this == &other)
			return *this;
		std::cout << "Copy Assign" << std::endl;
		this->a = other.a;
		this->arr = new T[a];
		memcpy(this->arr, other.arr, sizeof(T) * other.a);
	}
	Object& operator=(Object&& other) noexcept {
		if (this == &other)
			return *this;
		std::cout << "Move Assign" << std::endl;
		this->a = other.a;
		this->arr = other.arr;
		other.a = 0;
		other.arr = nullptr;
	}
	~Object() {
		std::cout << "Destructor" << std::endl;
		delete[] this->arr;
		this->a = 0;
	}
};

