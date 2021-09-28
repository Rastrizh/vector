#pragma once
#include <memory>

template<typename T>
class Vector
{
private:
	T* arr;
	size_t m_size;
	size_t m_capacity;
public:
	Vector() 
		: m_size{0}, m_capacity{1} 
	{
		arr = reinterpret_cast<T*>(new int8_t[m_capacity * sizeof(T)]);
	}

	~Vector()
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			(arr+i)->~T();
		}
		delete[] reinterpret_cast<int8_t*>(arr);
		arr = nullptr;
		m_size = 0;
		m_capacity = 0;
	}

	void reserve(size_t n)
	{
		if (n <= m_capacity) return;

		T* newarr = reinterpret_cast<T*>(new int8_t[n * sizeof(T)]);
		//T* newarr = new T[n]; <- bad difinition(not working with complex types)
		
		/*
		* Definition of exception-safeness
		* 
		// STL option to process copy constructor exceptions
		try
		{
			std::uninitialized_copy(arr, arr + m_size, newarr);
		}
		catch (...)
		{
			delete[] reinterpret_cast<int8_t>(newarr);
			throw;
		}

		// own defined option to process copy constructor exceptions
		//size_t i = 0;
		//try
		//{
		//	for (; i < n; ++i)
		//	{
		//		new(newarr + i) T(arr[i]); // function placement new
		//		//newarr[i] = arr[i]; <- bad difinition(not working with complex types)
		//	}
		//}
		//catch (...)
		//{
		//	for (size_t j = 0; j < i; ++j)
		//	{
		//		(newarr + j)->~T();
		//	}
		//	delete[] reinterpret_cast<int8_t>(newarr);
		//	throw;
		//}
		*/

		for (size_t i = 0; i < n; ++i)
		{
			new(newarr+i) T(arr[i]); // function placement new
			//newarr[i] = arr[i]; <- bad difinition(not working with complex types)
		}
		for (size_t i = 0; i < m_size; ++i)
		{
			(arr+i)->~T();
		}
		delete[] reinterpret_cast<int8_t*>(arr);
		arr = newarr;
		m_capacity = n;
	}

	void resise(size_t n, const T& value = T())
	{
		if (n > m_capacity) reserve(n);
		for (size_t i = m_size; i < n; ++i)
			new(arr+i) T(value);
		if (n < m_size)
			m_size = n;
	}

	void push_back(const T& value)
	{
		if (m_size == m_capacity) reserve(m_size * 2);
		new(arr+m_size) T(value);
		++m_size;
	}

	void pop_back()
	{
		--m_size;
		(arr+m_size)->~T();
	}

	T& operator[](const size_t index)
	{
		return *(arr+index);
	}
	const T& operator[](const size_t index) const
	{
		return *(arr+index);
	}

	T& at(const size_t index)
	{
		if (index >= m_size)
			throw;// std::out_of_range("...");
		return *(arr+index);
	}
	const T& at(const size_t index) const
	{
		if (index >= m_size)
			throw;// std::out_of_range("...");
		return *(arr + index);
	}

	size_t size() const
	{
		return m_size;
	}

	size_t capacity() const
	{
		return m_capacity;
	}

};