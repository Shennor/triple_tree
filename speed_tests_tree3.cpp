#include "speed_tests_tree3.h"
#include <iostream>
#include <ctime>
#include <vector>
#include "tree3.h"

namespace speed_tests_tree3
{
	double test_add(size_t num)
	{
		tree3::Tree3<int> t{};
		int start = clock();
		int end;
		double res = 0;
		for (size_t i = 0; i < num; ++i)
		{
			t.Add(std::rand());
			end = clock();
			if (double(end - start) / CLOCKS_PER_SEC > 0.001) {
				res += double(end - start) / CLOCKS_PER_SEC;
				start = clock();
			}
		}
		return res;
	}

	double test_search(size_t num)
	{
		tree3::Tree3<int> t{};
		std::vector<int> v{};
		for (size_t i = 0; i < num; ++i)
		{
			int a = std::rand();
			t.Add(a);
			v.push_back(a);
		}
		int start = clock();
		int end;
		double res = 0;
		for (size_t i = 0; i < num; ++i)
		{
			t.Search(v[rand() % v.size()]);
			end = clock();
			if (double(end - start) / CLOCKS_PER_SEC > 0.001) {
				res += double(end - start) / CLOCKS_PER_SEC;
				start = clock();
			}
		}
		return res;
	}

	/*
	int test_delete(size_t num)
	{
		tree3::Tree3<int> t{};
		std::vector<tree3::Node3<int>*> v{};
		for (size_t i = 0; i < num; ++i)
		{
			int a = std::rand();
			t.Add(a);
			v.push_back(t.Search(a));
		}
		const int start = clock();
		for (size_t i = 0; i < num; ++i)
		{
			t.Delete(v[rand() % v.size()]);
		}
		const int end = clock();
		return end - start;
	}
	*/
	void test_all()
	{
		std::cout << "speed test for add started\n";
		double add_sec_4 = 0;
		for (int i = 0; i < 1; ++i)
		{
			add_sec_4 += test_add(50000);
		}
		double add_sec_7 = 0;
		for (int i = 0; i < 1; ++i)
		{
			add_sec_7 += test_add(10000000);
		}
		std::cout << "speed test for add ended\n";
		std::cout << "speed test for search started\n";
		double search_sec_4 = 0;
		for (int i = 0; i < 1; ++i)
		{
			search_sec_4 += test_search(50000);
		}
		double search_sec_7 = 0;
		for (int i = 0; i < 1; ++i)
		{
			search_sec_7 += test_search(10000000);
		}
		std::cout << "speed test for search ended\n";
		/*
		std::cout << "speed test for delete started\n";
		float delete_sec_4 = 0;
		for (int i = 0; i < 1; ++i)
		{
			delete_sec_4 += float(test_delete(50000)) / CLOCKS_PER_SEC;
		}
		float delete_sec_7 = 0;
		for (int i = 0; i < 1; ++i)
		{
			delete_sec_7 += float(test_delete(10000000)) / CLOCKS_PER_SEC;
		}
		std::cout << "speed test for delete ended\n\n";
		*/
		std::cout << "Speed test for Tree3:\n";
		std::cout << "Add:\n";
		std::cout << "5*10^4 elements - " << add_sec_4 << " seconds. \n";
		std::cout << "10^7 elements - " << add_sec_7 << " seconds. \n";
		std::cout << "Search:\n";
		std::cout << "5*10^4 elements - " << search_sec_4 << " seconds. \n";
		std::cout << "10^7 elements - " << search_sec_7 << " seconds. \n";
		//std::cout << "Delete:\n";
		//std::cout << "5*10^4 elements - " << delete_sec_4 << "seconds. \n";
		//std::cout << "10^7 elements - " << delete_sec_7 << "seconds. \n";
	}

}