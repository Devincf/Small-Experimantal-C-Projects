// lernen3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdint.h>
#include <array>
#include <vector>
#include <unordered_map>
#include <bitset>

class Foo{
public:
	int x;
	Foo( ) :x( 10 ){ }
	void Bar( ){
		std::cout << " x ; " << x << std::endl;
	}
};

template <int R, int C>
class Matrix{
public:
	std::array<std::array<int, C>, R> matrix;
};

std::vector<int> v{ };
void print( ){ std::cout << "Size : " << v.size( ) << " Capacity : " << v.capacity( ) << " Address : " << &(v.begin()) << std::endl; }
void inc( ){ v.push_back( 1 ); print( ); }
void inc( int x ){ for( int i = 0; i < x; i++ ){ inc( ); } }


enum class A{
	Foo = 0
};
enum class B{
	Bar = 0,
	Bar2 = 1
};

class Foof{
public:
	int a,b,c,d;
};

int main( ){
	Foo foo = Foo();
	foo.x = 3;
	std::cout << "0x" << &foo << std::endl;
	intptr_t a = reinterpret_cast<intptr_t>(&foo);

	std::cout << "0x" << std::hex << a << std::endl;

	Foo* test = reinterpret_cast<Foo*>(a);

	std::cout << "0x" << test << std::endl;

	test->Bar();

	

	Matrix<3, 3> *m = new Matrix<3,3>();
	m->matrix[0][2] = 3;
	


	//inc(8);

	Foof f{ 0 };

	A foo = A::Foo;
	B bar = B::Bar;
	int* x = new int(0);
	__asm{
		mov eax,foo
		mov ebx,bar
		mov ecx,x
		cmp eax,ebx
		jne end
		inc [ecx]
		end:
	}
	std::cout << *x;

	delete x;

	
	bool test = false;
	__asm{
		lea eax,test
		xor [eax],1
	}
	std::cout << std::boolalpha << test;
	//delete test;

	getchar( );
}

