#include "vector.hpp"
#include "iterator.hpp"
#include <iostream>
#include <iterator>
#include <vector>

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



# include "containers_test/srcs/vector/common.hpp"

#define TESTED_TYPE int
//#define USING_STD 1

int		main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(7);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_two(4);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_three;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	printSize(vct);
	printSize(vct_two);

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	printSize(vct);
	printSize(vct_two);
	printSize(vct_three);
	printSize(vct_four);

	vct_four.assign(6, 84);
	printSize(vct_four);

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	printSize(vct);
	printSize(vct_two);

	return (0);
}