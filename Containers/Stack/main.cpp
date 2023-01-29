//
//  main.cpp
//  stack
//
//  Created by Denis Fedorov on 27.01.2023.
//

#include <iostream>
#include "stack.hpp"

int main(int argc, const char * argv[])
{
	constexpr int size {10};
	reinvent::container::stack<int> s1;
	std::cout << "s1 stack is created\n";
	
	for (int i {10}; i < 100; i += 10)
	{
		s1.push(i);
	}
	
	reinvent::container::stack<int> s2(s1);
	std::cout << "s2 stack is created out of s1 stack using copy constructor\n";
	std::cout << "\ns1 stack:\n";
	try
	{
		for (int i {}; i < size; ++i)
		{
			std::cout << s1.pop() << ' ';
		}
	}
	catch (const std::runtime_error & ex)
	{
		std::cout << "\ns1 " << ex.what() << '\n';
	}
	
	s1 = s2;
	std::cout << "\nAssign s2 stack to s1 stack...\n";
	std::cout << "s2 stack:\n";
	try
	{
		for (int i {}; i < size; ++i)
		{
			std::cout << s2.pop() << ' ';
		}
	}
	catch (const std::runtime_error & ex)
	{
		std::cout << "\ns2 " << ex.what() << '\n';
	}
	
	std::cout << "\ns1 stack:\n";
	try
	{
		for (int i {}; i < size; ++i)
		{
			std::cout << s1.pop() << ' ';
		}
	}
	catch (const std::runtime_error & ex)
	{
		std::cout << "\ns1 " << ex.what() << '\n';
	}
	std::cout << '\n';

	return 0;
}