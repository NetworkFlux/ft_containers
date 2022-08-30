/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:29:06 by npinheir          #+#    #+#             */
/*   Updated: 2022/08/27 11:43:36 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <sys/time.h>

void	vectorAllocationProof(ft::vector<int> empty, std::string name)
{
	std::cout << name << ": size = " << empty.size() << "; capacity = " << empty.capacity() << std::endl;
	empty.push_back(10);
	std::cout << name << ": size = " << empty.size() << "; capacity = " << empty.capacity() << std::endl;
	empty.push_back(10);
	std::cout << name << ": size = " << empty.size() << "; capacity = " << empty.capacity() << std::endl;
	empty.push_back(10);
	empty.push_back(10);
	std::cout << name << ": size = " << empty.size() << "; capacity = " << empty.capacity() << std::endl;
	empty.push_back(10);
	empty.push_back(10);
	empty.push_back(10);
	std::cout << name << ": size = " << empty.size() << "; capacity = " << empty.capacity() << std::endl;
	empty.push_back(10);
	empty.push_back(10);
	empty.push_back(10);
	std::cout << name << ": size = " << empty.size() << "; capacity = " << empty.capacity() << std::endl;
}

int	main(void)
{
	/*	INITIALIZATION	*/

	struct timeval begin, end;
	gettimeofday(&begin, 0);

	/*	CODE	*/

	ft::vector<int>	empty;
	ft::vector<int>	fill(9, 20);

	std::cout << "EMPTY VECTOR TEST (DEFAULT CONSTRUCTOR) " << std::endl;
	std::cout << "------------------------------------------" << std::endl << std::endl;
	vectorAllocationProof(empty, "EMPTY");
	std::cout << std::endl;
	std::cout << "FILL VECTOR TEST (FILL CONSTRUCTOR) " << std::endl;
	std::cout << "------------------------------------------" << std::endl << std::endl;
	vectorAllocationProof(fill, "FILL");
	std::cout << std::endl;

	std::cout << fill.max_size() << std::endl;

	/*	OUTPUT AND DEBBUG	*/

	gettimeofday(&end, 0);
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	double elapsed = seconds + microseconds * 1e-6;
	printf("Time measured: %.3f seconds.\n", elapsed);
	std::cin.get();
	system("leaks ft_container");
	return (0);
}
