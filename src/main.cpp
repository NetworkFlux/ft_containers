#include <sys/time.h>
#include "../include/stack/stack.hpp"
#include "../include/map/map.hpp"
#include <map>

#define NAMESPACE ft
#define VECTOR(T) NAMESPACE::vector<T>
#define STACK(T) NAMESPACE::stack<T>
#define PAIR(U, V) NAMESPACE::pair<U, V>
#define NODE(T) NAMESPACE::Node<T>
#define TREE(T) NAMESPACE::Tree<T>
#define MAP(T, P) NAMESPACE::map<T, P>

// -- OUTPUT MANAGING --
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

// -- VECTOR OUTPUT --
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

// -- STACK OUTPUT--
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

// -- MAP OUTPUT --
template <class U, class V>
void	printPair(const PAIR(U, V)& pair, const std::string& name)
{
	std::cout << name << " : (" << pair.first << "; " << pair.second << ")" << std::endl;
}
template <class T>
void	printNode(const NODE(T)& node)
{
	if (node.pair)
		printPair(*(node.pair), "Pair");
	else
		std::cout << "Empty" << std::endl;
	std::cout << "Has parent : " << node.parent << std::endl;
	std::cout << "Has left child : " << node.left << std::endl;
	std::cout << "Has right child : " << node.right << std::endl;
	std::cout << "Colored : " << node.color << std::endl;
	std::cout << "Is nil : " << node.is_nil << std::endl << std::endl;
}
template <class T>
void	printTree(TREE(T)& tree)
{
	for (typename ft::Tree<T>::iterator it = tree.begin(); it != tree.end(); it++)
		printNode(*(it.base()));
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
	std::cout << "Map size : " << map.size() << std::endl;
}

// -- VECTOR TESTS --
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
	printSubTitle("insert(second_elem, 5, 1) -- fill");
	vec.insert(++vec.begin(), 5, 1);
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

// -- STACK TESTS --
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
void	stackRealtionalOperators(void)
{
	VECTOR(int)	vec1(2, 10);
	VECTOR(int)	vec2(1, 14);
	STACK(int)	stack1(vec1);
	STACK(int)	stack2(vec2);

	printTitle("Relational Operators");
	printStack(stack1);
	std::cout << std::endl;
	printStack(stack2);
	std::cout << std::endl;
	printSubTitle(" == " );
	std::cout << "Are stack 1 and stack 2 equal : " << (stack1 == stack2) << std::endl;
	printSubTitle(" != ");
	std::cout << "Are stack 1 and stack 2 not equal : " << (stack1 != stack2) << std::endl;
	printSubTitle(" > ");
	std::cout << "Is stack 1 greater than stack 2 : " << (stack1 > stack2) << std::endl;
	printSubTitle(" >= ");
	std::cout << "Is stack 1 greater or equal than stack 2 : " << (stack1 >= stack2) << std::endl;
	printSubTitle(" < ");
	std::cout << "Is stack 1 less than stack 2 : " << (stack1 < stack2) << std::endl;
	printSubTitle(" <= ");
	std::cout << "Is stack 1 less or equal than stack 2 : " << (stack1 <= stack2) << std::endl;
}

// -- PAIR TESTS --
void	pairTests(void)
{
	printTitle("FT::PAIR");

	printSubTitle("Default constructor");
	PAIR(std::string, int)	a;
	printPair(a, "a");
	std::cout << std::endl;

	printSubTitle("Initialization constructor");
	PAIR(std::string, int)	b("Hi", 1010);
	printPair(b, "b");
	std::cout << std::endl;

	printSubTitle("Copy constructor");
	PAIR(std::string, int)	c(b);
	printPair(c, "c");
	std::cout << std::endl;

	printSubTitle("Operator =");
	PAIR(std::string, int)	d = c;
	printPair(d, "d");
	std::cout << std::endl;

	printSubTitle("Relational Operators");
	PAIR(std::string, int)	low("aaa", 0);
	PAIR(std::string, int)	middle("bbb", 1);
	PAIR(std::string, int)	high("ccc", 2);
	printPair(low, "low");
	printPair(middle, "middle");
	printPair(high, "high");
	std::cout << std::endl;
	std::cout << "low == middle : " << (low == middle) << std::endl;
	std::cout << "low == low : " << (low == low) << std::endl;
	std::cout << "low != middle : " << (low != middle) << std::endl;
	std::cout << "low != low : " << (low != low) << std::endl;
	std::cout << "low < middle : " << (low < middle) << std::endl;
	std::cout << "high < middle : " << (high < middle) << std::endl;
	std::cout << "middle <= middle : " << (middle <= middle) << std::endl;
	std::cout << "high <= middle : " << (high <= middle) << std::endl;
	std::cout << "high > low : " << (high > low) << std::endl;
	std::cout << "middle > high : " << (middle > high) << std::endl;
	std::cout << "high >= high : " << (high >= high) << std::endl;
	std::cout << "low >= middle : " << (low >= middle) << std::endl << std::endl;
}

// -- MAKE_PAIR TESTS --
void	makePairTests(void)
{
	printTitle("FT::MAKE_PAIR");

	printInfo("Doing the same tests as ft::pair but using ft::make_pair");
	PAIR(std::string, int)	mp = NAMESPACE::make_pair("Hi", 1010);
	printPair(mp, "mp");
	std::cout << std::endl;

	printSubTitle("Relational Operators");
	PAIR(std::string, int)	low = NAMESPACE::make_pair("aaa", 0);
	PAIR(std::string, int)	middle = NAMESPACE::make_pair("bbb", 1);
	PAIR(std::string, int)	high = NAMESPACE::make_pair("ccc", 2);
	printPair(low, "low");
	printPair(middle, "middle");
	printPair(high, "high");
	std::cout << std::endl;
	std::cout << "low == middle : " << (low == middle) << std::endl;
	std::cout << "low == low : " << (low == low) << std::endl;
	std::cout << "low != middle : " << (low != middle) << std::endl;
	std::cout << "low != low : " << (low != low) << std::endl;
	std::cout << "low < middle : " << (low < middle) << std::endl;
	std::cout << "high < middle : " << (high < middle) << std::endl;
	std::cout << "middle <= middle : " << (middle <= middle) << std::endl;
	std::cout << "high <= middle : " << (high <= middle) << std::endl;
	std::cout << "high > low : " << (high > low) << std::endl;
	std::cout << "middle > high : " << (middle > high) << std::endl;
	std::cout << "high >= high : " << (high >= high) << std::endl;
	std::cout << "low >= middle : " << (low >= middle) << std::endl << std::endl;
}

// -- NODE TESTS --
void	nodeTests(void)
{
	printTitle("NODE");
	printSubTitle("Constructors and memory checks");
	std::cout << std::endl;
	NODE(PAIR(std::string, int))	node1(NAMESPACE::make_pair("HI", 1010));
	NODE(PAIR(std::string, int))	node2(node1);
	NODE(PAIR(std::string, int))	node3 = node2;
	NODE(PAIR(std::string, int))	node4(NAMESPACE::make_pair("HELLO", 2020));
	printNode(node1);
	printNode(node2);
	printNode(node3);
	printNode(node4);
	printSubTitle("Relational Operators");
	std::cout << std::endl;
	std::cout << "node1 == node2 : " << (node1 == node2) << std::endl;
	std::cout << "node3 == node4 : " << (node3 == node4 ) << std::endl;
	std::cout << "node1 != node2 : " << (node1 != node2) << std::endl;
	std::cout << "node3 != node4 : " << (node3 != node4 ) << std::endl << std::endl;
}

// -- RED BLACK TREE TESTS--
void	treeTests(void)
{
	printTitle("RED BLACK TREE");
	printSubTitle("Constructors and memory checks");
	TREE(PAIR(std::string, int))	tree;
	std::cout << "Current size is : " << tree.size() << std::endl;
	tree.insert(NAMESPACE::make_pair("BO", 123));
	tree.insert(NAMESPACE::make_pair("AO", 234));
	tree.insert(NAMESPACE::make_pair("CO", 345));
	tree.insert(NAMESPACE::make_pair("CO", 456));
	std::cout << "Current size is : " << tree.size() << std::endl;
	tree.insert(NAMESPACE::make_pair("DO", 567));
	printTree(tree);
	std::cout << "Current size is : " << tree.size() << std::endl;
	std::cout << std::endl;
	printTree(tree);
}

// -- MAP TESTS --
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

	printSubTitle("COPY ASSIGNMENT");
	MAP(int, std::string)	copya = copy;
	mapAllocationProof(copya, "Copya", "Copy", 30);
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
	printTitle("MODIFIERS");
	MAP(int, std::string)	map;
	printSubTitle("insert(pair) -- single element");
	map.insert(NAMESPACE::make_pair(0, "0000"));
	printMap(map);
	printSubTitle("insert(iterator, pair -- hint");
	map.insert(map.begin(), NAMESPACE::make_pair(1, "1111"));
	printMap(map);
	MAP(int, std::string)	filled;
	filled[10] = "1010";
	filled[20] = "2020";
	filled[30] = "3030";
	filled[40] = "4040";
	filled[50] = "5050";
	printSubTitle("insert(first, last) -- range");
	map.insert(filled.begin(), filled.end());
	printMap(map);
	printSubTitle("erase(position)");
	printInfo("erasing 3rd element");
	MAP(int, std::string)::iterator	it = map.begin();
	it++;
	it++;
	map.erase(it);
	printMap(map);
	printSubTitle("erase(key) -- deletion by key");
	printInfo("erasing element with key '20'");
	map.erase(20);
	printMap(map);
	printInfo("erasing element with key '5'");
	map.erase(5);
	printMap(map);
	printSubTitle("erase(2nd, last)");
	it = map.begin();
	it++;
	printMap(map);
	map.erase(it, map.end());
	printMap(map);
	printSubTitle("swap()");
	MAP(int, std::string)	map1;
	MAP(int, std::string)	map2;
	map1[0] = "0000";
	map1[1] = "1111";
	map1[2] = "2222";
	map2[3] = "3333";
	map2[4] = "4444";
	map2[5] = "5555";
	map2[6] = "6666";
	map2[7] = "7777";
	printMap(map1);
	printMap(map2);
	map1.swap(map2);
	printInfo("SWAPED");
	printMap(map1);
	printMap(map2);
}
void	mapObservers(void)
{
	printTitle("OBSERVERS");
	printSubTitle("key_comp()");
	printInfo("Iterating through the map using the retrieved key_comp object");
	MAP(char, int)	map;
	MAP(char, int)::key_compare	comp = map.key_comp();

	map['a'] = 100;
	map['b'] = 200;
	map['c'] = 300;
	map['d'] = 400;
	map['e'] = 500;
	map['f'] = 600;

	MAP(char, int)::iterator	it = map.begin();
	char	higher = map.rbegin()->first;

	while (comp(it->first, higher))
	{
		std::cout << it->first << " => " << it->second << std::endl;
		it++;
	}
	std::cout << it->first << " => " << it->second << std::endl;

	printSubTitle("value_comp()");
	printInfo("Iterating through the map using the retrieved value_comp object");
	MAP(char, int)	map2;

	map2['a'] = 100;
	map2['b'] = 200;
	map2['c'] = 300;
	map2['d'] = 400;
	map2['e'] = 500;
	map2['f'] = 600;

	it = map.begin();
	NAMESPACE::pair<char, int>	highest = *map.rbegin();

	while (map.value_comp()(*it, highest))
	{
		std::cout << it->first << " => " << it->second << std::endl;
		it++;
	}
	std::cout << it->first << " => " << it->second << std::endl;
}
void	mapOperations(void)
{
	MAP(int, std::string)	map;
	printTitle("OPERATIONS");
	printSubTitle("find()");
	map[0] = "0000";
	map[1] = "1111";
	map[2] = "2222";
	map[3] = "3333";
	map[4] = "4444";
	map[5] = "5555";
	MAP(int, std::string)::iterator	it;
	printInfo("Finding element with key '2'");
	it = map.find(2);
	std::cout << "Found element " << it->second << std::endl;
	// printInfo("Finding element with key '8'");
	// it = map.find(8);
	printSubTitle("count()");
	printInfo("Counting elements with key '4'");
	std::cout << "Count : " << map.count(4) << std::endl;
	printInfo("Counting elements with key '8'");
	std::cout << "Count : " << map.count(8) << std::endl;

	printSubTitle("lower_bound");
	printInfo("Finding the lower_bound of '3'");
	std::cout << "lower_bound : " << map.lower_bound(3)->second << std::endl;
	printSubTitle("upper_bound");
	printInfo("Finding the upper_bound of '3'");
	std::cout << "upper_bound : " << map.upper_bound(3)->second << std::endl;
	printSubTitle("equal_range");
	std::cout << "equal_range of 3 : " << map.equal_range(3).first->second << " | " << map.equal_range(3).second->second << std::endl;
}

int		main(void)
{
	// -- MAIN INIT --
	struct timeval begin, end;
	gettimeofday(&begin, 0);

	// -- TESTS --
	{
		// Vector
		vectorConstructor();
		vectorIterator();
		vectorCapacity();
		vectorElementAccess();
		vectorModifiers();
		vectorRelationalOperators();

		// Stack
		stackTests();
		stackRealtionalOperators();

		// Map
		// pairTests();
		// makePairTests();
		// nodeTests();
		// treeTests();

		mapConstructor();
		mapIterators();
		mapCapacity();
		mapElementAccess();
		mapModifiers();
		mapObservers();
		mapOperations();

		// test();
	}

	// -- MAIN END --
	gettimeofday(&end, 0);
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	double elapsed = seconds + microseconds * 1e-6;
	printf("Time measured: %.3f seconds.\n", elapsed);
	// std::cin.get();
	// system("leaks ft_containers");
	return (0);
}
