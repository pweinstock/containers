// #include "vector.hpp"
// #include "iterator.hpp"
// #include <iostream>
// #include <iterator>
// #include <vector>

// template<class T>
// void	print(ft::vector<T> &vec)
// {
// 	std::cout << "vector:";
// 	for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
// 		std::cout << " - " << *it;
// 	std::cout << std::endl;
// }

// int	main()
// {
// 	ft::vector<int> empty;
// 	int myints[] = {16,2,77,29};
// 	ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
// 	int myints2[] = {17,3,78,30};
// 	ft::vector<int> sixth (myints2, myints2 + sizeof(myints2) / sizeof(int) );
// 	//fifth.assign(sixth.begin(), sixth.end());
// 	//fifth.swap(sixth);
// 	// std::cout << "vector:";
// 	// for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
// 	// 	std::cout << " - " << *it;
// 	// std::cout << std::endl;
// 	print(fifth);
// 	//std::cout << "insert: " << *((fifth.insert(fifth.begin() + 2, 42)).base()) << std::endl;
// 	fifth.insert(fifth.begin() + 2, sixth.begin(), sixth.end());
// 	print(fifth);
// 	//fifth.clear();
// 	try
// 	{
// 		std::cout << fifth.at(2) << std::endl;
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}
// 	std::cout << "capacity: " << fifth.capacity() << std::endl;
// 	std::cout << "size: " << fifth.size() << std::endl;
// 	std::cout << "empty: " << fifth.empty() << std::endl;
// 	//for (ft::iterator it = fifth.begin())
// 	// ft::vector<int>	vec(10, 42);
// 	// std::cout << vec[5] <<  std::endl;
// 	return 0;
// }



// # include "containers_test/srcs/vector/common.hpp"

// #define TESTED_TYPE int
// //#define USING_STD 1

// int		main(void)
// {
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(7);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_two(4);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_three;
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_four;

// 	for (unsigned long int i = 0; i < vct.size(); ++i)
// 		vct[i] = (vct.size() - i) * 3;
// 	for (unsigned long int i = 0; i < vct_two.size(); ++i)
// 		vct_two[i] = (vct_two.size() - i) * 5;
// 	printSize(vct);
// 	printSize(vct_two);

// 	vct_three.assign(vct.begin(), vct.end());
// 	vct.assign(vct_two.begin(), vct_two.end());
// 	vct_two.assign(2, 42);
// 	vct_four.assign(4, 21);

// 	std::cout << "\t### After assign(): ###" << std::endl;

// 	printSize(vct);
// 	printSize(vct_two);
// 	printSize(vct_three);
// 	printSize(vct_four);

// 	vct_four.assign(6, 84);
// 	printSize(vct_four);

// 	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

// 	vct.assign(5, 53);
// 	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

// 	printSize(vct);
// 	printSize(vct_two);

// 	return (0);
// }

//#include <map>
#include "map.hpp"
#include <map>
#include <utility>
#include <list>
#define T1 float
#define T2 int
typedef ft::pair<const T1, T2> T3;

int	main(void)
{
	// std::map<int, int>	stdmap;
	// ft::map<int, int>	mymap;
	// stdmap.insert(std::pair<int, int>(1, 42));
	// mymap.insert(ft::pair<int, int>(1, 42));
	// std::cout << "mymap				stdmap" << std::endl;
	
	// std::cout << "[1]: " << mymap[1] << "				";
	// std::cout << "[1]: " << stdmap[1] << std::endl;
	
	// mymap[2] = 43;
	// stdmap[2] = 43;
	// mymap[3] = 44;
	// stdmap[3] = 44;
	// mymap[4] = 45;
	// stdmap[4] = 45;
	// mymap[5] = 46;
	// stdmap[5] = 46;
	
	// //std::cout << "rend(): " << (*(--mymap.rend())).second << "				";
	// //std::cout << "rend(): " << (*(--stdmap.rend())).second << std::endl;
	
	// std::cout << "size(): " << mymap.size() << "			";
	// std::cout << "size(): " << stdmap.size() << std::endl;

	// ft::map<int, int>::iterator	it = mymap.begin(), ite = mymap.end();
	// std::cout << "begin: " << it._ptr << std::endl;
	// std::cout << "end: " << ite._ptr << std::endl;
	// for (; it != ite; it++)
	// 	std::cout << (*it).second << std::endl;

	std::list<T3> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(2.5 + i, i + 1));

	ft::map<T1, T2> mp(lst.begin(), lst.end());
	std::cout << "test" << std::endl;
	ft::map<T1, T2>::iterator it(mp.begin());
	ft::map<T1, T2>::const_iterator ite(mp.begin());
	return 0;
}