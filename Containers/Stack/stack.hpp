//
//  stack.hpp
//  stack
//
//  Created by Denis Fedorov on 26.01.2023.
//

#pragma once
#include <memory>
#include <stdexcept>

// Simple implementation of stack data type based on linked list. It uses a unique pointer to top node to help
// manage dynamicaly allocated memory. The 'node' structure contains of template data variable and a pointer to previous node.
// The copy constructor and the assignment operator have O(N*N) complexity because of two nested loops. The class has
// no arithmetic operators available. The 'top' method returns the last added data by value. The 'pop' method pops
// top value out of the stack and the 'push' method adds data to the top of the stack. If stack is empty and top method
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
		T top();
		void push(T value);
		void pop();
		bool empty() const;
		uint32_t size() const;
	private:
		struct node
		{
			node(T new_data) : data(std::move(new_data)), previous() {}
			T data;
			node * previous;
		};
		uint32_t m_size;
		std::unique_ptr<node> m_top;
	};

	template <typename T>
	stack<T>::stack() : m_size() {}
	
	template <typename T>
	stack<T>::~stack()
	{
		// while pointer is not equal nullptr, destroy all nodes left
		while (m_top)
		{
			m_top.reset(m_top->previous);
		}
	}
	
	template <typename T>
	stack<T>::stack(const stack<T> & other)
	{
		if (!other.m_size)
		{
			return;
		}
		else
		{
			m_size = 0;
			// pointer to the top value of other stack
			node * other_ptr {other.m_top.get()};
			// set the pointer to the last node of other stack and get its value
			// then set the position to last - 1 and so on
			for (uint32_t position {other.m_size - 1}; position != 0; --position)
			{
				for (int i {}; i < position; ++i)
				{
					other_ptr = other_ptr->previous;
				}
				this->push(other_ptr->data);
				other_ptr = other.m_top.get();
			}
			// copy the last value (the top of the other stack object)
			this->push(other_ptr->data);
		}
	}

	template <typename T>
	stack<T>::stack(stack && other) noexcept
	{
		m_size = other.m_size;
		m_top = std::move(other.m_top);
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
			m_size = 0;
			node * other_ptr {other.m_top.get()};
			for (uint32_t position {other.m_size - 1}; position != 0; --position)
			{
				for (int i {}; i < position; ++i)
				{
					other_ptr = other_ptr->previous;
				}
				this->push(other_ptr->data);
				other_ptr = other.m_top.get();
			}
			this->push(other_ptr->data);
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
			m_size = other.m_size;
			m_top = std::move(other.m_top);
			return *this;
		}
	}
	
	template <typename T>
	T stack<T>::top()
	{
		if (this->empty())
		{
			throw std::runtime_error {"stack is empty!"};
		}
		else
		{
			T data {std::move(m_top->data)};
			this->pop();
			return data;
		}
	}
	
	template <typename T>
	void stack<T>::push(T new_data)
	{
		if (!m_top)
		{
			m_top = std::make_unique<node>(std::move(new_data));
		}
		else
		{
			std::unique_ptr<node> new_node {std::make_unique<node>(std::move(new_data))};
			new_node->previous = m_top.release();
			m_top = std::move(new_node);
		}
		++m_size;
	}
	
	template <typename T>
	void stack<T>::pop()
	{
		if (!m_top)
		{
			return;
		}
		else
		{
			m_top.reset(m_top->previous);
			--m_size;
		}
	}
	
	template <typename T>
	bool stack<T>::empty() const
	{
		return m_size == 0;
	}
	
	template <typename T>
	uint32_t stack<T>::size() const
	{
		return m_size;
	}
}
