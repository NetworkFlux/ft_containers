/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npinheir <npinheir@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:29:06 by npinheir          #+#    #+#             */
/*   Updated: 2022/10/10 15:01:40 by npinheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define VECTOR(T) ft::vector<T>
#define STACK(T) ft::stack<T>
#define MAP(T, P) ft::map<T, P>
#define NAMESPACE ft

#include "../include/stack/stack.hpp"
#include "../include/map/map.hpp"
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
void	printVector(VECTOR(T)& vec)
{
	if (vec.size() == 0)
		std::cout << "\033[32m Vector content : \033[0m[]" << std::endl;
	else
	{
		std::cout << "\033[32m Vector content : \033[0m[";
		for (size_t i = 0; i < vec.size() - 1; i++)
			std::cout << vec[i] << " ";
		std::cout << vec[vec.size() - 1] << "]"<< " --- size = " << vec.size() << std::endl;
	}
}
template <class T>
void	vectorAllocationProof(VECTOR(T)& vec, std::string name, std::string param)
{
	std::cout << "Vector " << name << "( " << param << " ) was initialize with Size : " << vec.size() << " and Capacity : " << vec.capacity() << std::endl;
	printInfo("Doing some push_back() to add values and see how the container reacts");
	std::cout << "\033[32m Allocation Proof\033[0m" << std::endl;
	printInfo("1 value added");
	vec.push_back(10);
	std::cout << name << ": size = " << vec.size() << "; capacity = " << vec.capacity() << std::endl;
	printInfo("1 value added");
	vec.push_back(10);
	std::cout << name << ": size = " << vec.size() << "; capacity = " << vec.capacity() << std::endl;
	printInfo("2 value added");
	vec.push_back(10);
	vec.push_back(10);
	std::cout << name << ": size = " << vec.size() << "; capacity = " << vec.capacity() << std::endl;
	printInfo("3 value added");
	vec.push_back(10);
	vec.push_back(10);
	vec.push_back(10);
	std::cout << name << ": size = " << vec.size() << "; capacity = " << vec.capacity() << std::endl;
	printInfo("3 value added");
	vec.push_back(10);
	vec.push_back(10);
	vec.push_back(10);
	std::cout << name << ": size = " << vec.size() << "; capacity = " << vec.capacity() << std::endl << std::endl;
	printVector(vec);
	std::cout << std::endl;
}
void	vectorConstructor(void)
{
	printTitle("CONSTRUCTORS");
	printSubTitle("DEFAULT CONSTRUCTOR");
	VECTOR(int)	empty;
	vectorAllocationProof(empty, "Empty", "");

	printSubTitle("FILL CONSTRUCTOR");
	VECTOR(int)	fill(9, 20);
	vectorAllocationProof(fill, "Fill", "9, 20");

	VECTOR(int)::iterator	first = fill.begin();
	VECTOR(int)::iterator	last = fill.end();
	printSubTitle("RANGE CONSTRUCTOR");
	VECTOR(int)	range(first, last);
	vectorAllocationProof(range, "Range", "first{Fill iterator}, last{Fill iterator}");

	printSubTitle("COPY CONSTRUCTOR");
	VECTOR(int)	copy(fill);
	vectorAllocationProof(copy, "Copy", "Fill");
}
void	vectorIterator(void)
{
	printTitle("ITERATORS");
	printSubTitle("begin() - end()");
	VECTOR(int)	vec;
	for (size_t i = 0; i < 5; i++)
		vec.push_back(i);
	VECTOR(int)::iterator	b = vec.begin();
	VECTOR(int)::iterator	e = vec.end();

	VECTOR(int)::reverse_iterator	rb = vec.rbegin();
	VECTOR(int)::reverse_iterator	re = vec.rend();

	printVector(vec);
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

	printSubTitle("rbegin() - rend()");
	printVector(vec);
	std::cout << "rbegin() points to : " << *rb << std::endl;
	std::cout << "rend() points to : " << *re << std::endl;
	std::cout << "rend() - 1 points to : " << *(re - 1) << std::endl;
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
void	vectorCapacity(void)
{
	printTitle("CAPACITY");
	VECTOR(std::string)	vec(5, "Hello");
	printVector(vec);
	printSubTitle("size()");
	std::cout << "Vector size : " << vec.size() << std::endl;
	printSubTitle("max_size()");
	std::cout << "Vector max size : " << vec.max_size() << std::endl;
	printSubTitle("resize(3)");
	vec.resize(3);
	printVector(vec);
	std::cout << "Vector new size : " << vec.size() << " and new capacity : " << vec.capacity() << std::endl;
	printSubTitle("resize(6, 'yo')");
	vec.resize(6, "yo");
	printVector(vec);
	std::cout << "Vector new size : " << vec.size() << " and new capacity : " << vec.capacity() << std::endl;
	printSubTitle("capacity()");
	std::cout << "Vector capacity : " << vec.capacity() << std::endl;
	printSubTitle("empty()");
	std::cout << "Vector is empty : " << vec.empty() << std::endl;
	printSubTitle("reserve(12)");
	vec.reserve(12);
	std::cout << "Vector new capacity : " << vec.capacity() << std::endl;
	printSubTitle("reserve(5)");
	vec.reserve(5);
	std::cout << "Vector new capacity : " << vec.capacity() << std::endl;
}
void	vectorElementAccess(void)
{
	printTitle("ELEMENT ACCESS");
	VECTOR(double)	vec;
	for (size_t i = 0; i < 5; i++)
		vec.push_back(i + 1.2);
	printVector(vec);
	printSubTitle("at(4)");
	std::cout << "Accessing 4th element using at : " << vec.at(4) << std::endl;
	// std::cout << "Accessing out of range element using at : " << vec.at(8) << std::endl;
	printSubTitle("front()");
	std::cout << "Accessing the front element : " << vec.front() << std::endl;
	printSubTitle("back()");
	std::cout << "Accessing the back element : " << vec.back() << std::endl;
	printSubTitle("data()");
	void	*ptr;
	ptr = vec.data();
	std::cout << "Address of the first element using operator []: " << &(vec[0]) << " -- Address of the first element using data(): " << ptr << std::endl;
}
void	vectorModifiers(void)
{
	printTitle("MODIFIERS");
	VECTOR(int)	vec(5, 42);
	VECTOR(int)	vec2(6, 666);
	VECTOR(int)::iterator	first2 = vec2.begin();
	VECTOR(int)::iterator	end2 = vec2.end();

	printVector(vec);
	printVector(vec2);
	printSubTitle("assign(first, last) -- range ");
	vec.assign(first2, end2);
	printVector(vec);
	std::cout << "Infos after the assign; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("assign(8, 12) -- fill ");
	vec.assign(8, 12);
	printVector(vec);
	std::cout << "Infos after the assign; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("assign(4, 10) -- fill ");
	vec.assign(4, 10);
	printVector(vec);
	std::cout << "Infos after the assign; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	vec = VECTOR(int)(5, 42);
	printVector(vec);
	printSubTitle("push_back()");
	printInfo("3 value added");
	vec.push_back(13);
	vec.push_back(14);
	vec.push_back(15);
	printVector(vec);
	std::cout << "Infos after the push_back; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("pop_back()");
	printInfo("2 value removed");
	vec.pop_back();
	vec.pop_back();
	printVector(vec);
	std::cout << "Infos after the pop_back(); size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("insert(second_elem, 100) -- single element");
	VECTOR(int)::iterator	first = vec.begin();
	first++;
	vec.insert(first, 100);
	printVector(vec);
	std::cout << "Infos after the insert; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("insert(first_elem, 5, 1) -- fill");
	vec.insert(vec.begin(), 5, 1);
	printVector(vec);
	std::cout << "Infos after the range insert; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("insert(first_elem, first, last) -- range");
	vec.insert(vec.begin(), vec2.begin(), vec2.end());
	printVector(vec);
	std::cout << "Infos after the range insert; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("erase(second element)");
	printVector(vec);
	first = vec.begin();
	vec.erase(first);
	std::cout << "Infos after the erase; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printVector(vec);
	printSubTitle("erase(second element to fifth)");
	printVector(vec);
	first = vec.begin();
	VECTOR(int)::iterator	second = first + 3;
	vec.erase(first, second);
	std::cout << "Infos after the erase; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printVector(vec);
	printSubTitle("swap()");
	VECTOR(int)	vec1(5, 10);
	VECTOR(int)	vec3(3, 50);
	printVector(vec1);
	printVector(vec3);
	std::cout << "Vectors after the swap :" << std::endl;
	vec1.swap(vec3);
	printVector(vec1);
	printVector(vec3);
	printSubTitle("clear()");
	printVector(vec);
	std::cout << "Infos before the clear; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	vec.clear();
	printVector(vec);
	std::cout << "Infos after the clear; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
}
void	vectorRelationalOperators(void)
{
	VECTOR(float)	vec1(5, 10.2);
	VECTOR(float)	vec2(7, 14.2);

	printTitle("Relational Operators");
	printVector(vec1);
	printVector(vec2);
	printSubTitle(" == " );
	std::cout << "Are vector 1 and vector 2 equal : " << (vec1 == vec2) << std::endl;
	printSubTitle(" != ");
	std::cout << "Are vector 1 and vector 2 not equal : " << (vec1 != vec2) << std::endl;
	printSubTitle(" > ");
	std::cout << "Is vector 1 greater than vector 2 : " << (vec1 > vec2) << std::endl;
	printSubTitle(" >= ");
	std::cout << "Is vector 1 greater or equal than vector 2 : " << (vec1 >= vec2) << std::endl;
	printSubTitle(" < ");
	std::cout << "Is vector 1 less than vector 2 : " << (vec1 < vec2) << std::endl;
	printSubTitle(" <= ");
	std::cout << "Is vector 1 less or equal than vector 2 : " << (vec1 <= vec2) << std::endl;
}


template <class T>
void	printStack(STACK(T)& stack)
{
	STACK(T)	stack2(stack);
	if (stack2.size() == 0)
		return ;
	else
	{
		int x = stack2.top();
		stack2.pop();
		printStack(stack2);
		std::cout << x << " ";
		stack2.push(x);
	}
}
void	stackTests(void)
{
	STACK(int)	stack1;
	STACK(int)	stack2(stack1);

	printTitle("Stack Tests");
	printStack(stack1);
	printStack(stack2);
	printSubTitle("empty");
	std::cout << "Is the stack empty : " << stack1.empty() << std::endl;
	printSubTitle("push and size");
	for (int i = 1; i < 6; i++)
		stack1.push(i);
	printStack(stack1);
	std::cout << "Infos after pushing ; size : " << stack1.size() << std::endl;
	printSubTitle("top");
	std::cout << "Element at the top of the stack : " << stack1.top() << std::endl;
	printSubTitle("pop");
	stack1.pop();
	printStack(stack1);
	std::cout << "Infos after poping ; size : " << stack1.size() << std::endl;
}

template <class T, class P>
void	printMap(MAP(T, P)& map)
{
	if (map.size() == 0)
	{
		std::cout << "Map is empty ! " << std::endl;
		return ;
	}
	for (typename MAP(T, P)::iterator it = map.begin(); it != map.end(); it++)
		std::cout << "first : " << it->first << " | second : " << it->second << std::endl;
}

void	mapTests(void)
{
	// {
	// 	printTitle("ft::pair");
	// 	NAMESPACE::pair<std::string, int>	empty;
	// 	NAMESPACE::pair<std::string, int>	fill("Hello", 25);
	// 	NAMESPACE::pair<std::string, int>	copy(fill);

	// 	empty.show();
	// 	fill.show();
	// 	copy.show();
	// 	std::cout << "Is A == to B ? " << (empty == fill) << std::endl;
	// 	std::cout << "Is A != to B ? " << (empty != fill) << std::endl;
	// 	std::cout << "Is A > than B ? " << (empty > fill) << std::endl;
	// 	std::cout << "Is A >= than B ? " << (empty >= fill) << std::endl;
	// 	std::cout << "Is B == to C ? " << (fill == copy) << std::endl;

	// 	// ft::make_pair(42, 'A').show();
	// }

	// {
	// 	printTitle("Nodes");
	// 	ft::Node< ft::pair<std::string, int> >	empty;
	// 	ft::Node< ft::pair<std::string, int> >	valued(ft::make_pair("Ca va", 42), NULL);
	// 	ft::Node< ft::pair<std::string, int> >	copy(valued);

	// 	empty.show();
	// 	valued.show();
	// 	copy.show();
	// 	std::cout << "Is A == to B ? " << (empty == valued) << std::endl;
	// 	std::cout << "Is A != to B ? " << (empty != valued) << std::endl;
	// 	std::cout << "Is B == to C ? " << (valued == copy) << std::endl << std::endl;
	// }

	{
		MAP(std::string, int)		tree;

		printTitle("ft::map");
		printSubTitle("Capacity");
		std::cout << "Is the map empty : " << tree.empty() << std::endl;
		std::cout << "Map size : " << tree.size() << std::endl;
		std::cout << "Map max size : " << tree.max_size() << std::endl;

		tree.value_comp();
		tree.key_comp();
		tree.get_allocator();

		printSubTitle("Element access");
		std::cout << "Adding some values" << std::endl;
		tree.insert(NAMESPACE::make_pair("aaaa", 1111));
		tree.insert(NAMESPACE::make_pair("bbbb", 2222));
		tree.insert(NAMESPACE::make_pair("cccc", 3333));
		tree.insert(NAMESPACE::make_pair("gggg", 4444));
		tree.insert(NAMESPACE::make_pair("zzzz", 5555));
		printMap(tree);
		std::cout << "Is 'aaaa' in the map : " << tree["aaaa"] << std::endl;
		std::cout << "Is 'pppp' in the map : " << tree["pppp"] << std::endl;
		std::cout << "Assigning 9999 to the 'pppp' key" << std::endl;
		tree["pppp"] = 9999;
		printMap(tree);
		std::cout << "At 'bbbb' : " << tree.at("bbbb") << std::endl;
		// std::cout << "At 'xxxx' : " << tree.at("xxxx") << std::endl;
		
		printSubTitle("Operations");
		std::cout << "count('bbbb') : " << tree.count("bbbb") << std::endl;
		std::cout << "count('uuuu') : " << tree.count("uuuu") << std::endl;
		std::cout << "lower_bound('cccc') " << (tree.lower_bound("cccc"))->second << std::endl;
		std::cout << "upper_bound('cccc') " << (tree.upper_bound("cccc"))->second << std::endl;
		std::cout << "equal_bound('cccc') " << (tree.equal_range("cccc").first)->second << " | " << (tree.equal_range("cccc").second)->second << std::endl;
		printMap(tree);
		tree.erase(tree.begin());
		printMap(tree);
		tree.clear();
		printMap(tree);
	}
	
}

template <class T, class P>
void	mapAllocationProof(MAP(T, P)& map, std::string name, std::string param, int i)
{
	
	std::cout << "Map " << name << "( " << param << " ) was initialize with Size : " << map.size() << std::endl;
	printInfo("Doing some insertions to add values and see how the container reacts");
	std::cout << "\033[32m Allocation Proof\033[0m" << std::endl;
	printInfo("1 value added");
	map[0 + i] = "0000";
	std::cout << name << ": size = " << map.size() << std::endl;
	printInfo("1 value added");
	map[1 + i] = "1111";
	std::cout << name << ": size = " << map.size() << std::endl;
	printInfo("2 value added");
	map[2 + i] = "2222";
	map[3 + i] = "3333";
	std::cout << name << ": size = " << map.size() << std::endl;
	printInfo("3 value added");
	map[4 + i] = "4444";
	map[5 + i] = "5555";
	map[6 + i] = "6666";
	std::cout << name << ": size = " << map.size() << std::endl;
	printInfo("3 value added");
	map[7 + i] = "7777";
	map[8 + i] = "8888";
	map[9 + i] = "9999";
	std::cout << name << ": size = " << map.size() << std::endl << std::endl;
	printMap(map);
	std::cout << std::endl;
}

void	mapConstructor(void)
{
	printTitle("CONSTRUCTORS");
	printSubTitle("DEFAULT CONSTRUCTOR");
	MAP(int, std::string)	empty;
	mapAllocationProof(empty, "Empty", "", 0);

	printSubTitle("RANGE CONSTRUCTOR");
	MAP(int, std::string)	range(empty.begin(), empty.end());
	mapAllocationProof(range, "Range", "empty.begin(), empty.end()", 10);

	printSubTitle("COPY CONSTRUCTOR");
	MAP(int, std::string)	copy(range);
	mapAllocationProof(copy, "Copy", "Range", 20);
}

void	mapIterators(void)
{
	printTitle("ITERATORS");
	MAP(int, std::string)	map;
	map[4] = "4444";
	map[5] = "5555";
	map[6] = "6666";
	map[7] = "7777";
	map[8] = "8888";
	map[9] = "9999";
	printMap(map);
	printSubTitle("begin() - end()");
	printInfo("Printing map using iterators :");
	for (MAP(int, std::string)::iterator it = map.begin(); it != map.end(); it++)
		std::cout << "first : " << it->first << " | second : " << it->second << std::endl;
	printSubTitle("rbegin() - rend()");
	printInfo("Printing map using reverse iterators :");
	for (MAP(int, std::string)::reverse_iterator rit = map.rbegin(); rit != map.rend(); rit++)
		std::cout << "first : " << rit->first << " | second : " << rit->second << std::endl;
	printInfo("Modifying values using iterators");
	for (MAP(int, std::string)::iterator it = map.begin(); it != map.end(); it++)
		it->second = "Modified";
	printMap(map);
	printInfo("Modifying values using reverse iterators");
	for (MAP(int, std::string)::reverse_iterator rit = map.rbegin(); rit != map.rend(); rit++)
		rit->second = "Modified reverse";
	printMap(map);
}

void	mapCapacity(void)
{
	printTitle("CAPACITY");
	MAP(int, std::string)	empty;
	printSubTitle("empty()");
	printInfo("Is the map empty ?");
	std::cout << empty.empty() << std::endl;
	printInfo("One value added. Is the map stll empty ?");
	empty[0] = "0000";
	std::cout << empty.empty() << std::endl;
	printSubTitle("size()");
	printInfo("4 values added");
	empty[1] = "1111";
	empty[2] = "2222";
	empty[3] = "3333";
	empty[4] = "4444";
	std::cout << "The current size is : " << empty.size() << std::endl;
	printMap(empty);
	printSubTitle("max_size()");
	std::cout << "The current max size of the container is : " << empty.max_size() << std::endl;
}

void	mapElementAccess(void)
{
	printTitle("ELEMENT ACCESS");
	MAP(int, std::string)	map;
	printSubTitle("operator[]");
	printInfo("Using the [] operator with new keys will insert the value into the container :");
	map[0] = "0000";
	map[1] = "1111";
	map[2] = "2222";
	map[3] = "3333";
	map[4] = "4444";
	printMap(map);
	printInfo("Using the [] operator with an existing keys will retrieve the value from the container :");
	std::cout << "Trying key '3' : " << map[3] << std::endl;
	std::cout << "Trying key '1' : " << map[1] << std::endl;
	std::cout << "Trying key '4' : " << map[4] << std::endl;
	printInfo("What if trying to go too far");
	std::cout << "Trying key '6' : " << map[6] << std::endl;
	printSubTitle("at()");
	printInfo("at() has the same behaviour as operator[] with exitsting keys");
	std::cout << "Trying at(3) : " << map.at(3) << std::endl;
	std::cout << "Trying at(1) : " << map.at(1) << std::endl;
	std::cout << "Trying at(4) : " << map.at(4) << std::endl;
	// printInfo("What if trying to go too far");
	// std::cout << "Trying at(6) : " << map.at(6) << std::endl;
}

void	mapModifiers(void)
{
	
}

int	main(void)
{
	/*	INITIALIZATION	*/

	struct timeval begin, end;
	gettimeofday(&begin, 0);

	/*	CODE	*/
	{
		{
			// Vector

			// vectorConstructor();
			// vectorIterator();
			// vectorCapacity();
			// vectorElementAccess();
			// vectorModifiers();
			// vectorRelationalOperators();
		}

		{
			// Stack
			// stackTests(); // LLEEAAKS
		}
	
		{
			// mapConstructor(); // LLEEAAAKKSS
			// mapIterators();
			// mapCapacity();
			// mapElementAccess();
			// mapModifiers();
		}

	}
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
