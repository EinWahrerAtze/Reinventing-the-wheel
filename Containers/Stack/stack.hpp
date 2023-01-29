//
//  stack.hpp
//  stack
//
//  Created by Denis Fedorov on 26.01.2023.
//

#pragma once
#include <memory>
#include <stdexcept>

// Simple implementation of stack data structure based on linked list. It uses a unique pointer to top node to help
// manage dynamicaly allocated memory. The 'node' structure contains of value itself and a pointer to previous node.
// The copy constructor and the assignment operator have O(N*N) complexity because of two nested loops. The class has
// no arithmetic operators available. The 'top' method gives access to last added value. The 'pop' method pops
// top value out of the stack and the 'push' method adds value to the top of the stack. If stack is empty and pop method
// is called, std::runtime_error exception is thrown. The destructor destroys any nodes left with the unique pointer
// and thus clears up allocated memory.

namespace reinvent::container
{
	template <typename T>
	class stack
	{
	public:
		stack();
		~stack();
		stack(const stack & other);
		stack(stack && other) noexcept;
		stack & operator = (const stack & other);
		stack & operator = (stack && other) noexcept;
	public:
		const T & top() const;
		void push(T value);
		T pop();
		bool empty() const;
		uint32_t size() const;
	private:
		struct node
		{
			node(T data) : value(std::move(data)), previous(nullptr) {}
			T value;
			node * previous;
		};
		uint32_t _size;
		std::unique_ptr<node> _top;
	};

	template <typename T>
	stack<T>::stack() : _size() {}
	
	template <typename T>
	stack<T>::~stack()
	{
		// destroy all nodes left in the stack
		while (_top)
		{
			_top.reset(_top->previous);
		}
	}
	
	template <typename T>
	stack<T>::stack(const stack<T> & other)
	{
		if (!other._size)
		{
			return;
		}
		else
		{
			_size = 0;
			// pointer to the top value of other stack
			node * other_ptr {other._top.get()};
			// set the pointer to the last node of other stack and get its value, copy it
			// and then set the position to last - 1 and so on
			for (uint32_t position {other._size - 1}; position != 0; --position)
			{
				for (int i {}; i < position; ++i)
				{
					other_ptr = other_ptr->previous;
				}
				this->push(other_ptr->value);
				other_ptr = other._top.get();
			}
			// copy the last value (the top of the other stack object)
			this->push(other_ptr->value);
		}
	}

	template <typename T>
	stack<T>::stack(stack && other) noexcept
	{
		_size = other._size;
		_top = std::move(other._top);
	}
	
	template <typename T>
	stack<T> & stack<T>::operator = (const stack<T> & other)
	{
		if (this == &other)
		{
			return *this;
		}
		else
		{
			_size = 0;
			node * other_ptr {other._top.get()};
			for (uint32_t position {other._size - 1}; position != 0; --position)
			{
				for (int i {}; i < position; ++i)
				{
					other_ptr = other_ptr->previous;
				}
				this->push(other_ptr->value);
				other_ptr = other._top.get();
			}
			this->push(other_ptr->value);
			return *this;
		}
	}
	
	template <typename T>
	stack<T> & stack<T>::operator = (stack<T> && other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}
		else
		{
			_size = other._size;
			_top = std::move(other._top);
			return *this;
		}
	}
	
	template <typename T>
	const T & stack<T>::top() const
	{
		return _top->value;
	}
	
	template <typename T>
	void stack<T>::push(T value)
	{
		if (!_top)
		{
			_top = std::make_unique<node>(std::move(value));
		}
		else
		{
			std::unique_ptr<node> new_node {std::make_unique<node>(std::move(value))};
			new_node->previous = _top.release();
			_top = std::move(new_node);
		}
		++_size;
	}
	
	template <typename T>
	T stack<T>::pop()
	{
		if (this->empty())
		{
			throw std::runtime_error {"stack is empty!"};
		}
		else
		{
			T value {std::move(_top->value)};
			_top.reset(_top->previous);
			--_size;
			return value;
		}
	}
	
	template <typename T>
	bool stack<T>::empty() const
	{
		return _size == 0;
	}
	
	template <typename T>
	uint32_t stack<T>::size() const
	{
		return _size;
	}
}
