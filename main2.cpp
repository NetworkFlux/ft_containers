#include <iostream>
#include "include/vector.hpp"
#include <stack>
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

/*	Shows the allocation mechanisme by adding some values to the vector
	and by showing its size and capacity	*/
template <class T>
void	vectorAllocationProof(std::vector<T>& vec, std::string name)
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
	std::vector<int>	empty;
	vectorAllocationProof(empty, "EMPTY");

	printSubTitle("FILL CONSTRUCTOR");
	std::vector<int>	fill(9, 20);
	vectorAllocationProof(fill, "FILL");

	std::vector<int>::iterator	first = fill.begin();
	std::vector<int>::iterator	last = fill.end();
	printSubTitle("RANGE CONSTRUCTOR");
	std::vector<int>	range(first, last);
	vectorAllocationProof(range, "RANGE");

	printSubTitle("COPY CONSTRUCTOR");
	std::vector<int>	copy(fill);
	vectorAllocationProof(copy, "COPY");
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

void	modifiersTests(void)
{
	printTitle("MODIFIERS");
	std::vector<int>	vec(5, 42);
	std::vector<int>	vec3(6, 666);
	std::vector<int>::iterator	first2 = vec3.begin();
	std::vector<int>::iterator	end2 = vec3.end();

	printVector(vec);
	printSubTitle("assign() -- range ");
	vec.assign(first2, end2);
	printVector(vec);
	std::cout << "Infos after the assign; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("assign() -- fill ");
	vec.assign(8, 12);
	printVector(vec);
	std::cout << "Infos after the assign; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("push_back()");
	vec.push_back(13);
	vec.push_back(14);
	vec.push_back(15);
	printVector(vec);
	std::cout << "Infos after the push_back; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("pop_back()");
	vec.pop_back();
	vec.pop_back();
	printVector(vec);
	std::cout << "Infos after the pop_back(); size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("insert()");
	std::vector<int>::iterator	first = vec.begin();
	first++;
	first = vec.insert(first, 100);
	printVector(vec);
	std::cout << "Infos after the insert; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	first = vec.insert(first, 5, 1);
	printVector(vec);
	std::cout << "Infos after the range insert; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	// vec.insert(first, first2, end2);
	// printVector(vec);
	// std::cout << "Infos after the range insert; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("erase()");
	first = vec.begin();
	vec.erase(first);
	printVector(vec);
	std::cout << "Infos after the erase; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	first = vec.begin();
	std::vector<int>::iterator	second = first + 3;
	vec.erase(first, second);
	printVector(vec);
	std::cout << "Infos after the erase; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	printSubTitle("swap()");
	std::vector<int>	vec1(5, 10);
	std::vector<int>	vec2(3, 50);
	printVector(vec1);
	printVector(vec2);
	std::cout << "Vectors after the swap :" << std::endl;
	vec1.swap(vec2);
	printVector(vec1);
	printVector(vec2);
	printSubTitle("clear()");
	printVector(vec);
	std::cout << "Infos before the clear; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
	vec.clear();
	printVector(vec);
	std::cout << "Infos after the clear; size : " << vec.size() << " capacity : " << vec.capacity() << std::endl;
}

void	relationalOperators(void)
{
	std::vector<float>	vec1(5, 10.2);
	std::vector<float>	vec2(7, 14.2);

	printTitle("Relational Operators");
	printVector(vec1);
	printVector(vec2);
	printSubTitle(" ==" );
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

// template <class T>
// void	printStack(std::stack<T, std::vector<T> >& stack)
// {
// 	if (stack.size() == 0)
// 		std::cout << "\033[32m Stack content : \033[0m[]" << std::endl;
// 	else
// 	{
// 		std::cout << "\033[32m Stack content : \033[0m[";
// 		for (size_t i = 0; i < stack.size() - 1; i++)
// 			std::cout << stack.getContainer()[i] << " ";
// 		std::cout << stack.getContainer()[stack.size() - 1] << "]"<< std::endl;
// 	}
// }

void	stackTests(void)
{
	std::stack<int, ft::vector<int> >	stack1;
	std::stack<int, ft::vector<int> >	stack2(stack1);

	printTitle("Stack Tests");
	// printStack(stack1);
	// printStack(stack2);
	printSubTitle("empty");
	std::cout << "Is the stack empty : " << stack1.empty() << std::endl;
	printSubTitle("push and size");
	for (int i = 1; i < 6; i++)
		stack1.push(i);
	// printStack(stack1);
	std::cout << "Infos after pushing ; size : " << stack1.size() << std::endl;
	printSubTitle("top");
	std::cout << "Element at the top of the stack : " << stack1.top() << std::endl;
	printSubTitle("pop");
	stack1.pop();
	// printStack(stack1);
	std::cout << "Infos after poping ; size : " << stack1.size() << std::endl;
}

int	main(void)
{
	/*	INITIALIZATION	*/

	struct timeval begin, end;
	gettimeofday(&begin, 0);

	/*	CODE	*/
	{
		// Vector

		// constructorTests();
		// iteratorTests();
		// capacityTests();
		// elementAccessTests();
		// modifiersTests();
		// relationalOperators();

		stackTests();

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