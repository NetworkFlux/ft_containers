/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:29:06 by npinheir          #+#    #+#             */
/*   Updated: 2022/09/06 17:35:05 by npinheir         ###   ########.fr       */
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
template <class T>
void	printVector(ft::vector<T>& vec)
{
	std::cout << "\033[32m Vector content : \033[0m[";
	for (size_t i = 0; i < vec.size() - 1; i++)
		std::cout << vec[i] << " ";
	std::cout << vec[vec.size() - 1] << "]"<< std::endl;
}

/*	Shows the allocation mechanisme by adding some values to the vector
	and by showing its size and capacity	*/
template <class T>
void	vectorAllocationProof(ft::vector<T>& vec, std::string name)
{
	std::cout << "Vector (" << name << ") was initialize with Size : " << vec.size() << " and Capacity : " << vec.capacity() << std::endl;
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

// void	constructorTests(void)
// {
// 	printTitle("CONSTRUCTORS");
// 	printSubTitle("DEFAULT CONSTRUCTOR");
// 	ft::vector<int>	empty;
// 	vectorAllocationProof(empty, "EMPTY");

// 	printSubTitle("FILL CONSTRUCTOR");
// 	ft::vector<int>	fill(9, 20);
// 	vectorAllocationProof(fill, "FILL");

// 	printSubTitle("COPY CONSTRUCTOR");
// 	ft::vector<int>	copy(fill);
// 	vectorAllocationProof(copy, "COPY");
// }

// void	iteratorTests(void)
// {
// 	printTitle("ITERATORS");
// 	printSubTitle("begin() -- end()");
// 	ft::vector<int>	vec;
// 	vec.push_back(1);
// 	vec.push_back(2);
// 	vec.push_back(3);
// 	vec.push_back(4);
// 	vec.push_back(5);
// 	printVector(vec);
// 	ft::vector<int>::iterator	b = vec.begin();
// 	ft::vector<int>::iterator	e = vec.end();
	
// 	std::cout << "begin() points to : " << *b << std::endl;
// 	vec.push_back(99);
// 	std::cout << "end() points to : " << *e << std::endl;
// 	std::cout << "end() - 1 points to : " << *(e - 1) << std::endl;
// 	std::cout << "Looping through the vector using iterators : [";
// 	while (b != e - 1)
// 	{
// 		std::cout << *b << " ";
// 		b++;
// 	}
// 	std::cout << *b << "]" << std::endl;
// 	std::cout << "Modifying values using iterators : [";
// 	b = vec.begin();
// 	while (b != e - 1)
// 	{
// 		*b = *b * *b;
// 		std::cout << *b << " ";
// 		b++;
// 	}
// 	*b = *b * *b;
// 	std::cout << *b << "]" << std::endl;
// }

// void	capacityTests(void)
// {
// 	printTitle("CAPACITY");
// 	ft::vector<std::string>	vec(5, "Hello");
// 	printSubTitle("size()");
// 	std::cout << "Vector size : " << vec.size() << std::endl;
// 	printSubTitle("max_size()");
// 	std::cout << "Vector max size : " << vec.max_size() << std::endl;
// 	printSubTitle("resize()");
// 	vec.resize(3);
// 	std::cout << "Vector new size : " << vec.size() << " and new capacity : " << vec.capacity() << std::endl;
// 	printSubTitle("capacity()");
// 	std::cout << "Vector capacity : " << vec.capacity() << std::endl;
// 	printSubTitle("empty()");
// 	std::cout << "Vector is empty : " << vec.empty() << std::endl;
// 	printSubTitle("reserve()");
// 	vec.reserve(12);
// 	std::cout << "Vector new capacity : " << vec.capacity() << std::endl;
// 	printSubTitle("shrink_to_fit()");
// 	vec.shrink_to_fit();
// 	std::cout << "Vector new capacity : " << vec.capacity() << std::endl;
// }

void	elementAccessTests(void)
{
	// printTitle("ELEMENT ACCESS");
	ft::vector<int>	vec(5, 1);
	// vec.push_back(1.2f);
	// vec.push_back(2.2f);
	// vec.push_back(3.2f);
	// vec.push_back(4.2f);
	// vec.push_back(5.2f);
	// printSubTitle("at()");
	// std::cout << "Accessing 4th element using at : " << vec.at(4) << std::endl;
	// printSubTitle("front()");
	// std::cout << "Accessing the front element : " << vec.front() << std::endl;
	// printSubTitle("back()");
	// std::cout << "Accessing the back element : " << vec.back() << std::endl;
	// printSubTitle("data()");
	// void	*ptr;
	// ptr = vec.data();
	// std::cout << "Address of the first element : " << &(vec[0]) << " -- by data : " << ptr << std::endl;
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

	// ft::vector<int>	vec1;
	// ft::vector<std::string>	vec2(5, "Hello");
	// ft::vector<std::string>	vec3(vec2);

	// elementAccessTests();
	// printTitle("ELEMENT ACCESS");
	ft::vector<double>	vec(5, 1.4f);
	// vec.push_back(1.2f);
	// vec.push_back(2.2f);
	// vec.push_back(3.2f);
	// vec.push_back(4.2f);
	// vec.push_back(5.2f);
	// printSubTitle("at()");
	// std::cout << "Accessing 4th element using at : " << vec.at(4) << std::endl;
	// printSubTitle("front()");
	// std::cout << "Accessing the front element : " << vec.front() << std::endl;
	// printSubTitle("back()");
	// std::cout << "Accessing the back element : " << vec.back() << std::endl;
	// printSubTitle("data()");
	// void	*ptr;
	// ptr = vec.data();
	// std::cout << "Address of the first element : " << &(vec[0]) << " -- by data : " << ptr << std::endl;
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
