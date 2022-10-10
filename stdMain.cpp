#define VECTOR(T) std::vector<T>
#define STACK(T) std::stack<T>
#define MAP(T, P) std::map<T, P>
#define NAMESPACE std

#include <iostream>
#include <sys/time.h>
#include <vector>
#include <stack>
#include <map>

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
void	constructorTests(void)
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
void	iteratorTests(void)
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
void	elementAccessTests(void)
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
void	modifiersTests(void)
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
void	relationalOperators(void)
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


int	main(void)
{
	/*	INITIALIZATION	*/

	struct timeval begin, end;
	gettimeofday(&begin, 0);

	/*	CODE	*/
	{
		{
			// Vector

			// constructorTests();
			// iteratorTests();
			// capacityTests();
			// elementAccessTests();
			// modifiersTests();
			// relationalOperators();
		}

		{
			// Stack
			// stackTests();
		}
	
		{
			mapTests();
		}

	}
	/*	OUTPUT AND DEBBUG	*/

	gettimeofday(&end, 0);
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	double elapsed = seconds + microseconds * 1e-6;
	printf("Time measured: %.3f seconds.\n", elapsed);
	// std::cin.get();
	// system("leaks a.out");
	return (0);
}
