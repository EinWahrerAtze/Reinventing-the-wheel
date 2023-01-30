//
//  main.cpp
//  queue
//
//  Created by Denis Fedorov on 27.01.2023.
//

#include <iostream>
#include "queue.hpp"

int main(int argc, const char * argv[])
{
	constexpr int size {10};
	reinvent::container::queue<int> q1;
	std::cout << "creating new queue q1\n";
	for (int i {10}; i < 100; i += 10)
	{
		q1.push(i);
	}
	
	reinvent::container::queue<int> q2(q1);
	std::cout << "q2 queue created out of q1 using copy constructor\n\n";
	std::cout << "q1 queue: ";
	try
	{
		for (int i {}; i < size; ++i)
		{
			std::cout << q1.pop() << ' ';
		}
	}
	catch (const std::runtime_error & ex)
	{
		std::cout << "\nq1 " << ex.what() << '\n';
	}
	
	std::cout << "\nassign q2 to q1\n";
	q1 = q2;
	
	std::cout << "q2 queue: ";
	try
	{
		for (int i {}; i < size; ++i)
		{
			std::cout << q2.pop() << ' ';
		}
	}
	catch (const std::runtime_error & ex)
	{
		std::cout << "\nq2 " << ex.what() << '\n';
	}
	
	std::cout << "\nmove q1 to q2\n";
	q2 = std::move(q1);
	std::cout << "q2 queue: ";
	try
	{
		for (int i {}; i < size; ++i)
		{
			std::cout << q2.pop() << ' ';
		}
	}
	catch (const std::runtime_error & ex)
	{
		std::cout << "\nq2 " << ex.what() << '\n';
	}
	return 0;
}