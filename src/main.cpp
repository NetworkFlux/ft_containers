/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:29:06 by npinheir          #+#    #+#             */
/*   Updated: 2022/09/08 13:04:35 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <sys/time.h>

void	printTitle(std::string title)
{
	size_t	spaces = 31 - title.length();

	std::cout << "\033[1;33m-------------------------------" << std::endl << "|";
	for (size_t i = 0; i < (spaces / 2); i++)
		std::cout << " ";
	std::cout << title;
	for (size_t i = 0; i < (spaces / 2) - 1; i++)
		std::cout << " ";
	std::cout << "|" << std::endl;
	std::cout << "-------------------------------\033[0m\n" << std::endl;
}

void	printSubTitle(std::string subTitle)
{
	std::cout << "\033[34;43m--" << subTitle << "--\033[0m" << std::endl;
}

void	printInfo(std::string info)
{
	std::cout << "\033[33m" << info << "\033[0m" << std::endl;
}

template <class T>
void	printVector(ft::vector<T>& vec)
{
	if (vec.size() == 0)
		std::cout << "\033[32m Vector content : \033[0m[]" << std::endl;
	else
	{
		std::cout << "\033[32m Vector content : \033[0m[";
		for (size_t i = 0; i < vec.size() - 1; i++)
			std::cout << vec[i] << " ";
		std::cout << vec[vec.size() - 1] << "]"<< std::endl;
	}
}

/*	Shows the allocation mechanisme by adding some values to the vector
	and by showing its size and capacity	*/
template <class T>
void	vectorAllocationProof(ft::vector<T>& vec, std::string name)
{
	std::cout << "Vector (" << name << ") was initialize with Size : " << vec.size() << " and Capacity : " << vec.capacity() << std::endl;
	printInfo("Doing some push_back() to add values and see how the container reacts");
	std::cout << "\033[32m Allocation Proof :\033[0m" << std::endl;
	vec.push_back(10);
	std::cout << name << ": size = " << vec.size() << "; capacity = " << vec.capacity() << std::endl;
	vec.push_back(10);
	std::cout << name << ": size = " << vec.size() << "; capacity = " << vec.capacity() << std::endl;
	vec.push_back(10);
	vec.push_back(10);
	std::cout << name << ": size = " << vec.size() << "; capacity = " << vec.capacity() << std::endl;
	vec.push_back(10);
	vec.push_back(10);
	vec.push_back(10);
	std::cout << name << ": size = " << vec.size() << "; capacity = " << vec.capacity() << std::endl;
	vec.push_back(10);
	vec.push_back(10);
	vec.push_back(10);
	std::cout << name << ": size = " << vec.size() << "; capacity = " << vec.capacity() << std::endl << std::endl;
	printVector(vec);
	std::cout << std::endl;
}

void	constructorTests(void)
{
	printTitle("CONSTRUCTORS");
	printSubTitle("DEFAULT CONSTRUCTOR");
	ft::vector<int>	empty;
	vectorAllocationProof(empty, "EMPTY");

	printSubTitle("FILL CONSTRUCTOR");
	ft::vector<int>	fill(9, 20);
	vectorAllocationProof(fill, "FILL");

	// ft::vector<int>::iterator	first = fill.begin();
	// ft::vector<int>::iterator	last = fill.end();
	// printSubTitle("RANGE CONSTRUCTOR");
	// ft::vector<int>	range(first, last);
	// vectorAllocationProof(range, "RANGE");

	printSubTitle("COPY CONSTRUCTOR");
	ft::vector<int>	copy(fill);
	vectorAllocationProof(copy, "COPY");
}

void	iteratorTests(void)
{
	printTitle("ITERATORS");
	printSubTitle("begin() -- end()");
	ft::vector<int>	vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	printVector(vec);
	ft::vector<int>::iterator	b = vec.begin();
	ft::vector<int>::iterator	e = vec.end();
	
	std::cout << "begin() points to : " << *b << std::endl;
	std::cout << "end() points to : " << *e << std::endl;
	std::cout << "end() - 1 points to : " << *(e - 1) << std::endl;
	std::cout << "Looping through the vector using iterators : [";
	while (b != e - 1)
	{
		std::cout << *b << " ";
		b++;
	}
	std::cout << *b << "]" << std::endl;
	std::cout << "Modifying values using iterators : [";
	b = vec.begin();
	while (b != e - 1)
	{
		*b = *b * *b;
		std::cout << *b << " ";
		b++;
	}
	*b = *b * *b;
	std::cout << *b << "]" << std::endl;
}

void	capacityTests(void)
{
	printTitle("CAPACITY");
	ft::vector<std::string>	vec(5, "Hello");
	printVector(vec);
	printSubTitle("size()");
	std::cout << "Vector size : " << vec.size() << std::endl;
	printSubTitle("max_size()");
	std::cout << "Vector max size : " << vec.max_size() << std::endl;
	printSubTitle("resize()");
	vec.resize(3);
	printVector(vec);
	std::cout << "Vector new size : " << vec.size() << " and new capacity : " << vec.capacity() << std::endl;
	printSubTitle("capacity()");
	std::cout << "Vector capacity : " << vec.capacity() << std::endl;
	printSubTitle("empty()");
	std::cout << "Vector is empty : " << vec.empty() << std::endl;
	printSubTitle("reserve()");
	vec.reserve(12);
	std::cout << "Vector new capacity : " << vec.capacity() << std::endl;
}

void	elementAccessTests(void)
{
	printTitle("ELEMENT ACCESS");
	ft::vector<double>	vec;
	vec.push_back(1.2f);
	vec.push_back(2.2f);
	vec.push_back(3.2f);
	vec.push_back(4.2f);
	vec.push_back(5.2f);
	printVector(vec);
	printSubTitle("at()");
	std::cout << "Accessing 4th element using at : " << vec.at(4) << std::endl;
	printSubTitle("front()");
	std::cout << "Accessing the front element : " << vec.front() << std::endl;
	printSubTitle("back()");
	std::cout << "Accessing the back element : " << vec.back() << std::endl;
	printSubTitle("data()");
	void	*ptr;
	ptr = vec.data();
	std::cout << "Address of the first element operator []: " << &(vec[0]) << " -- Address of the first element using data(): " << ptr << std::endl;
}

void	modifiersTests(void)
{
	printTitle("MODIFIERS");
	ft::vector<int>	vec(5, 42);

	printVector(vec);
	printSubTitle("assign()");
	vec.assign(3, 12);
	printVector(vec);
	printSubTitle("push_back()");
	vec.push_back(13);
	vec.push_back(14);
	vec.push_back(15);
	printVector(vec);
	printSubTitle("pop_back()");
	vec.pop_back();
	vec.pop_back();
	printVector(vec);
	std::cout << "Infos after the pop_back(); size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("insert()");
	ft::vector<int>::iterator	first = vec.begin();
	first++;
	first = vec.insert(first, 100);
	printVector(vec);
	std::cout << "Infos after the insert; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	first = vec.insert(first, 40);
	printVector(vec);
	std::cout << "Infos after the insert; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	first = vec.insert(first, 30);
	printVector(vec);
	std::cout << "Infos after the insert; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	first = vec.insert(first, 20);
	printVector(vec);
	std::cout << "Infos after the insert; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	first = vec.insert(first, 5, 1);
	printVector(vec);
	std::cout << "Infos after the range insert; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	first = vec.insert(first, 5, 2);
	printVector(vec);
	std::cout << "Infos after the range insert; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	
}

int	main(void)
{
	/*	INITIALIZATION	*/

	struct timeval begin, end;
	gettimeofday(&begin, 0);

	/*	CODE	*/
	{

		// constructorTests();
		// iteratorTests();
		// capacityTests();
		// elementAccessTests();
		modifiersTests();

	}
	/*	OUTPUT AND DEBBUG	*/

	gettimeofday(&end, 0);
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	double elapsed = seconds + microseconds * 1e-6;
	printf("Time measured: %.3f seconds.\n", elapsed);
	std::cin.get();
	system("leaks ft_containers");
	return (0);
}
