/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:28:56 by npinheir          #+#    #+#             */
/*   Updated: 2022/09/13 17:17:31 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
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
void	printVector(std::vector<T>& vec)
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

void	iteratorTests(void)
{
	// Iterators
	printTitle("ITERATORS");
	// begin() - end()
	printSubTitle("begin() - end()");
	std::vector<int>	vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	printVector(vec);
	std::vector<int>::iterator	b = vec.begin();
	std::vector<int>::iterator	e = vec.end();

	std::vector<int>::reverse_iterator	rb = vec.rbegin();
	std::vector<int>::reverse_iterator	re = vec.rend();
	
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
	std::cout << std::endl;

	// rbegin() - rend()
	printSubTitle("rbegin() - rend()");
	printVector(vec);
	std::cout << "begin() points to : " << *rb << std::endl;
	std::cout << "end() points to : " << *re << std::endl;
	std::cout << "end() - 1 points to : " << *(re - 1) << std::endl;
	std::cout << "Looping through the vector using reverse iterators : [";
	while (rb != re - 1)
	{
		std::cout << *rb << " ";
		rb++;
	}
	std::cout << *rb << "]" << std::endl;
	std::cout << "Modifying values using reverse iterators : [";
	rb = vec.rbegin();
	while (rb != re - 1)
	{
		*rb = *rb * *rb;
		std::cout << *rb << " ";
		rb++;
	}
	*rb = *rb * *rb;
	std::cout << *rb << "]" << std::endl;
	std::cout << std::endl;
}

void	capacityTests(void)
{
	printTitle("CAPACITY");
	std::vector<std::string>	vec(5, "Hello");
	printVector(vec);
	printSubTitle("size()");
	std::cout << "Vector size : " << vec.size() << std::endl;
	printSubTitle("max_size()");
	std::cout << "Vector max size : " << vec.max_size() << std::endl;
	printSubTitle("resize(less)");
	vec.resize(3);
	printVector(vec);
	std::cout << "Vector new size : " << vec.size() << " and new capacity : " << vec.capacity() << std::endl;
	printSubTitle("resize(more)");
	vec.resize(6, "yo");
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
	std::vector<double>	vec;
	vec.push_back(1.2f);
	vec.push_back(2.2f);
	vec.push_back(3.2f);
	vec.push_back(4.2f);
	vec.push_back(5.2f);
	printVector(vec);
	printSubTitle("at()");
	std::cout << "Accessing 4th element using at : " << vec.at(4) << std::endl;
	std::cout << "Accessing out of range element using at : " << vec.at(8) << std::endl;
	printSubTitle("front()");
	std::cout << "Accessing the front element : " << vec.front() << std::endl;
	printSubTitle("back()");
	std::cout << "Accessing the back element : " << vec.back() << std::endl;
	printSubTitle("data()");
	void	*ptr;
	ptr = vec.data();
	std::cout << "Address of the first element operator []: " << &(vec[0]) << " -- Address of the first element using data(): " << ptr << std::endl;
}

int	main(void)
{
	/*	INITIALIZATION	*/

	struct timeval begin, end;
	gettimeofday(&begin, 0);

	/*	CODE	*/
	{
		// iteratorTests();
		// capacityTests();
		elementAccessTests();
	}
	/*	OUTPUT AND DEBBUG	*/

	gettimeofday(&end, 0);
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	double elapsed = seconds + microseconds * 1e-6;
	printf("Time measured: %.3f seconds.\n", elapsed);
	std::cin.get();
	system("leaks a.out");
	return (0);
}