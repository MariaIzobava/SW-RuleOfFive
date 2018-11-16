// RuleOfFive.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

class MyClass {
private:
	int8_t * p_;
	size_t n_;

public:
	MyClass(size_t n) : n_(n) {
		p_ = (int8_t *)malloc(n_ * sizeof(int8_t));
		printf("Constructor: memory is allocated for %d elements starting from %ld\n", n_, p_);
	}
	MyClass(MyClass const& obj) : n_(obj.n_) {
		p_ = (int8_t *)malloc(n_ * sizeof(int8_t));
		std::copy(obj.p_, obj.p_ + n_, p_);
		printf("Copy constructor: memory is allocated for %d elements starting from %ld\n", n_, p_);
	}

	MyClass(MyClass && obj) : n_(obj.n_), p_(obj.p_) {
		printf("Move constructor: data is moved from address %ld to %ld\n", obj.p_, p_);
		obj.p_ = nullptr;
		obj.n_ = 0;
	}

	MyClass& operator=(MyClass const & obj) {
		if (this == &obj) {
			printf("They are equal\n");
			return *this;
		}
		n_ = obj.n_;
		std::free(p_);
		p_ = (int8_t *)malloc(n_ * sizeof(int8_t));
		std::copy(obj.p_, obj.p_ + n_, p_);
		printf("Assign operator: memory is allocated for %d elements starting from %ld\n", n_, p_);
		return *this;
	}

	MyClass& operator=(MyClass&& obj) {
		n_ = obj.n_;
		p_ = obj.p_;
		printf("Move operator: data is moved from address %ld to %ld\n", obj.p_, p_);
		obj.p_ = nullptr;
		obj.n_ = 0;
		return *this;
	}

	~MyClass() {
		printf("Destructor: data memory is freed by address %ld\n", p_);
		std::free(p_);
		n_ = 0;
	}
};

MyClass f() {
	printf("MyClass x(7);\n");
	MyClass x(7);
	return x;
}

MyClass g() {
	printf("return MyClass(8);\n");
	return MyClass(8);
}

int main()
{
	printf("MyClass a(10);\n");
	MyClass a(10);
	printf("\nMyClass b(5);\n");
	MyClass b(5);
	printf("\nb = MyClass(15);\n");
	b = MyClass(15);
	printf("\na = b;\n");
	a = b;
	printf("\nb = b;\n");
	b = b;
	printf("\nMyClass x = MyClass(8);\n");
	MyClass x = MyClass(8);
	printf("\na = f();\n");
	a = f();
	printf("\nMyClass c = f();\n");
	MyClass c = f();
	printf("\nMyClass d = g();\n");
	MyClass d = g();
	getchar();
}