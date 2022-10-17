#include <iostream>
#include <vector>
#include <sys/time.h>
#include <map>

#define NAMESPACE std
// #define PAIR(U, V) NAMESPACE::pair<U, V>
// #define NODE(T) NAMESPACE::Node<T>
// #define TREE(T) NAMESPACE::Tree<T>
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
// template <class U, class V>
// void	printPair(const PAIR(U, V)& pair, const std::string& name)
// {
// 	std::cout << name << " : (" << pair.first << "; " << pair.second << ")" << std::endl;
// }
// template <class T>
// void	printNode(const NODE(T)& node)
// {
// 	if (node.pair)
// 		printPair(*(node.pair), "Pair");
// 	else
// 		std::cout << "Empty" << std::endl;
// 	std::cout << "Has parent : " << node.parent << std::endl;
// 	std::cout << "Has left child : " << node.left << std::endl;
// 	std::cout << "Has right child : " << node.right << std::endl;
// 	std::cout << "Colored : " << node.color << std::endl;
// 	std::cout << "Is nil : " << node.is_nil << std::endl << std::endl;
// }
// template <class T>
// void	printTree(TREE(T)& tree)
// {
// 	for (typename ft::Tree<T>::iterator it = tree.begin(); it != tree.end(); it++)
// 		printNode(*(it.base()));
// }
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
	}

	// -- MAIN END --
	gettimeofday(&end, 0);
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	double elapsed = seconds + microseconds * 1e-6;
	printf("Time measured: %.3f seconds.\n", elapsed);
	// std::cin.get();
	system("leaks a.out");
	return (0);
}