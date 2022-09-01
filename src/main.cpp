/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:29:06 by npinheir          #+#    #+#             */
/*   Updated: 2022/09/01 19:04:43 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
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

void	constructorTests(void)
{
	printTitle("CONSTRUCTORS");
	printSubTitle("DEFAULT CONSTRUCTOR");
	ft::vector<int>	empty;
	vectorAllocationProof(empty, "EMPTY");

	printSubTitle("FILL CONSTRUCTOR");
	ft::vector<int>	fill(9, 20);
	vectorAllocationProof(fill, "FILL");

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
	vec.push_back(99);
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

int	main(void)
{
	/*	INITIALIZATION	*/

	struct timeval begin, end;
	gettimeofday(&begin, 0);

	/*	CODE	*/

	constructorTests();
	iteratorTests();


	/*	OUTPUT AND DEBBUG	*/

	gettimeofday(&end, 0);
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	double elapsed = seconds + microseconds * 1e-6;
	printf("Time measured: %.3f seconds.\n", elapsed);
	// std::cin.get();
	// system("leaks ft_containers");
	return (0);
}
