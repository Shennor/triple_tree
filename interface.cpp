#include "interface.h"
#include "tree3.h"
#include "test_tree3.h"
#include "speed_tests_tree3.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace tree3;

vector<Tree3<int>> int_base{};
std::vector<Tree3<float>> float_base{};

int get_value()
{
	cout << "Enter number >> ";
	int value;
	cin >> value;
	return value;
}

void show_trees()
{
	if (!int_base.empty())
	{
		cout << "Trees in INTEGER space:\n";
	}
	for (size_t i = 0; i < int_base.size(); ++i)
	{
		cout << i << " : ";
		cout << int_base[i].ToString() << endl;
	}

	if (!float_base.empty())
	{
		cout << "Vectors in FLOAT space:\n";
	}
	for (size_t i = 0; i < float_base.size(); ++i)
	{
		cout << i << " : ";
		cout << float_base[i].ToString() << endl;
	}
}

void delete_tree()
{
	show_trees();
	cout << "What kind of tree do you want to delete?\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	int type = get_value();
	while (type < 1 || type > 2)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}
	int count = int_base.size();
	if (type == 2)
	{
		count = float_base.size();
	}
	cout << "Choose tree number\n";
	int num = get_value();
	while (num < 0 || num >= count)
	{
		cout << "You've written the wrong number!\n";
		num = get_value();
	}
	switch (type)
	{
	case 1:
		int_base.erase(int_base.begin() + num);
		break;
	case 2:
		float_base.erase(float_base.begin() + num);
		break;
	}
}

void print_hello()
{
	cout << "Hello! Let's test our class Tree3!\n";
}

int menu()
{
	cout << "MENU\n";
	cout << "1 : Create new tree\n";
	cout << "2 : Show trees\n";
	cout << "3 : Delete tree\n";
	cout << "4 : Operations\n";
	cout << "5 : Launch tests\n";
	cout << "6 : End program\n";
	int res = get_value();
	while (res < 1 || res > 6)
	{
		cout << "You've written the wrong number!\n";
		res = get_value();
	}
	return res;
}

int operations_menu()
{
	cout << "OPERATIONS\n";
	cout << "1 : Add new element\n";
	cout << "2 : Delete sought element\n";
	cout << "3 : Delete sought element recursive\n";
	cout << "4 : Get branch from sought element\n";
	cout << "5 : To string\n";
	cout << "6 : Map\n";
	cout << "7 : Reduce\n";
	cout << "8 : Go back to the MENU\n";
	int res = get_value();
	while (res < 1 || res > 8)
	{
		cout << "You've written the wrong number!\n";
		res = get_value();
	}
	return res;
}

void create_int_tree_from_string(string& s, string& format)
{
	Tree3<int> t{ s, format };
	cout << t.ToString() << endl;
	int_base.push_back(t);
}

void create_float_tree_from_string(string& s, string& format)
{
	Tree3<float> t{ s, format };
	cout << t.ToString() << endl;
	float_base.push_back(t);
}

void create_int_tree_input(size_t num)
{
	int tmp = 0;
	cout << "Enter elements:\n";
	cin >> tmp;
	Tree3<int> t{tmp};
	for (size_t i = 1; i < num; ++i)
	{
		cin >> tmp;
		t.Add(tmp);
	}
	cout << t.ToString() << endl;
	int_base.push_back(t);
}

void create_float_tree_input(size_t num)
{
	float tmp = 0.0;
	cout << "Enter elements:\n";
	cin >> tmp;
	Tree3<float> t{tmp};
	for (size_t i = 1; i < num; ++i)
	{
		cin >> tmp;
		t.Add(tmp);
	}
	cout << t.ToString() << endl;
	float_base.push_back(t);
}

void create_tree()
{
	cout << "Type of space\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	int type = get_value();
	while (type < 0 || type > 2)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}

	cout << "Make it from...\n";
	cout << "1 : input elements\n";
	cout << "2 : string format <K>(1)[2]{3}\n";
	cout << "3 : string another format\n";
	int source = get_value();
	while (source < 0 || source > 3)
	{
		cout << "You've written the wrong number!\n";
		source = get_value();
	}

	switch (type)
	{
	case 1:
		if (source == 1)
		{
			cout << "What number of elements? ";
			int num = get_value();
			while (type < 0)
			{
				cout << "Number must be >= 0!\n";
				type = get_value();
			}
			create_int_tree_input(num);
		}
		else
		{
			string format = "<K>(1)[2]{3}";
			if (source == 3)
			{
				cout << "Enter format >> ";
				cin >> format;
				cout << endl;
			}
			string s;
			cout << "Enter string >> ";
			cin >> s;
			cout << endl;
			create_int_tree_from_string(s, format);
		}
		break;
	case 2:
		if (source == 1)
		{
			cout << "What number of elements?";
			int num = get_value();
			while (type < 0)
			{
				cout << "Number must be >= 0!\n";
				type = get_value();
			}
			create_float_tree_input(num);
		}
		else
		{
			string format = "<K>(1)[2]{3}";
			if (source == 3)
			{
				cout << "Enter format >> ";
				cin >> format;
				cout << endl;
			}
			string s;
			cout << "Enter string >> ";
			cin >> s;
			cout << endl;
			create_float_tree_from_string(s, format);
		}
		break;
	}
}

void add()
{
	show_trees();
	cout << "What kind of tree do you want to add to?\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	int type = get_value();
	while (type < 1 || type > 2)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}
	int count = int_base.size();
	if (type == 2)
	{
		count = float_base.size();
	}
	cout << "Choose tree number. ";
	int num = get_value();
	while (num < 0 || num >= count)
	{
		cout << "You've written the wrong number!\n";
		num = get_value();
	}
	
	switch (type)
	{
	case 1:
		int a;
		cout << "Enter new element >> ";
		cin >> a;
		cout << endl;
		int_base[num].Add(a);
		cout << int_base[num].ToString() << endl;
		break;
	case 2:
		float b;
		cout << "Enter new element >> ";
		cin >> b;
		cout << endl;
		float_base[num].Add(b);
		cout << float_base[num].ToString() << endl;
		break;
	}
}

void delete_sought()
{
	show_trees();
	cout << "What kind of tree do you want to delete in?\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	int type = get_value();
	while (type < 1 || type > 2)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}
	int count = int_base.size();
	if (type == 2)
	{
		count = float_base.size();
	}
	cout << "Choose tree number. ";
	int num = get_value();
	while (num < 0 || num >= count)
	{
		cout << "You've written the wrong number!\n";
		num = get_value();
	}
	
	switch (type)
	{
	case 1:
		int a;
		cout << "Enter sought element >> ";
		cin >> a;
		cout << endl;
		int_base[num].Delete(int_base[num].Search(a));
		cout << int_base[num].ToString() << endl;
		break;
	case 2:
		float b;
		cout << "Enter sought element >> ";
		cin >> b;
		cout << endl;
		float_base[num].Delete(float_base[num].Search(b));
		cout << float_base[num].ToString() << endl;
		break;
	}
}

void delete_sought_recursive()
{
	show_trees();
	cout << "What kind of tree do you want to delete in?\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	int type = get_value();
	while (type < 1 || type > 2)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}
	int count = int_base.size();
	if (type == 2)
	{
		count = float_base.size();
	}
	cout << "Choose tree number. ";
	int num = get_value();
	while (num < 0 || num >= count)
	{
		cout << "You've written the wrong number!\n";
		num = get_value();
	}

	switch (type)
	{
	case 1:
		int a;
		cout << "Enter sought element >> ";
		cin >> a;
		cout << endl;
		int_base[num].DeleteRecursive(int_base[num].Search(a));
		cout << int_base[num].ToString() << endl;
		break;
	case 2:
		float b;
		cout << "Enter sought element >> ";
		cin >> b;
		cout << endl;
		float_base[num].DeleteRecursive(float_base[num].Search(b));
		cout << float_base[num].ToString() << endl;
		break;
	}
}

void get_branch()
{
	show_trees();
	cout << "What kind of tree do you want to delete in?\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	int type = get_value();
	while (type < 1 || type > 2)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}
	int count = int_base.size();
	if (type == 2)
	{
		count = float_base.size();
	}
	cout << "Choose tree number. ";
	int num = get_value();
	while (num < 0 || num >= count)
	{
		cout << "You've written the wrong number!\n";
		num = get_value();
	}
	int a;
	float b;
	if (type == 1)
	{
		cout << "Enter sought element >> ";
		cin >> a;
		cout << endl;
		Tree3<int> t1{ int_base[num].Search(a) };
		cout << t1.ToString() << endl;
		int_base.push_back(t1);
	}
	else
	{
		cout << "Enter sought element >> ";
		cin >> b;
		cout << endl;
		Tree3<float> t2{ float_base[num].Search(b) };
		cout << t2.ToString() << endl;
		float_base.push_back(t2);
	}
}

void to_string()
{
	show_trees();
	cout << "What kind of tree do you want to make a string?\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	int type = get_value();
	while (type < 1 || type > 2)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}
	int count = int_base.size();
	if (type == 2)
	{
		count = float_base.size();
	}
	cout << "Choose tree number. ";
	int num = get_value();
	while (num < 0 || num >= count)
	{
		cout << "You've written the wrong number!\n";
		num = get_value();
	}

	cout << "What format of string?\n";
	cout << "1 : <K>(1)[2]{3}\n";
	cout << "2 : another like that\n";
	cout << "3 : node - parent\n";
	int f = get_value();
	while (f < 1 || f > 3)
	{
		cout << "You've written the wrong number!\n";
		f = get_value();
	}
	
	switch (type)
	{
	case 1:
	{
		if (f == 3)
		{
			cout << int_base[num].ToStringParentChild() << endl;
		}
		else
		{
			string format = "<K>(1)[2]{3}";
			if (f == 2)
			{
				cout << "Enter format >> ";
				cin >> format;
				cout << endl;
			}
			string s;
			cout << "Enter string >> ";
			cin >> s;
			cout << endl;
			cout << int_base[num].ToString(
				int_base[num].GetRoot(), format) << endl;
		}
		break;
	}
	case 2:
	{
		if (f == 3)
		{
			cout << float_base[num].ToStringParentChild() << endl;
		}
		else
		{
			string format = "<K>(1)[2]{3}";
			if (f == 2)
			{
				cout << "Enter format >> ";
				cin >> format;
				cout << endl;
			}
			string s;
			cout << "Enter string >> ";
			cin >> s;
			cout << endl;
			cout << float_base[num].ToString(
				float_base[num].GetRoot(), format) << endl;
		}
		break;
	}
	}
}

template<class T>
T inc(T a)
{
	return a + 1;
}

void map_tree()
{
	show_trees();
	cout << "What kind of tree do you want to make a map?\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	int type = get_value();
	while (type < 1 || type > 2)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}
	int count = int_base.size();
	if (type == 2)
	{
		count = float_base.size();
	}
	cout << "Choose tree number. ";
	int num = get_value();
	while (num < 0 || num >= count)
	{
		cout << "You've written the wrong number!\n";
		num = get_value();
	}
	cout << "We have function that increments the number by 1. There's result:\n\n";

	switch (type)
	{
	case 1:
	{
		Tree3<int> a = map_tree3(&int_base[num], inc);
		cout << a.ToString() << endl;
		cout << endl;
		int_base.push_back(a);
		break;
	}
	case 2:
	{
		Tree3<float> a = map_tree3(&float_base[num], inc);
		cout << a.ToString() << endl;
		cout << endl;
		float_base.push_back(a);
		break;
	}
	}
}

template<class T>
T sum_elements(T a, T b)
{
	return a + b;
}

void reduce_tree()
{
	show_trees();
	cout << "What kind of tree do you want to reduce?\n";
	cout << "1 : int\n";
	cout << "2 : float\n";
	int type = get_value();
	while (type < 1 || type > 2)
	{
		cout << "You've written the wrong number!\n";
		type = get_value();
	}
	int count = int_base.size();
	if (type == 2)
	{
		count = float_base.size();
	}
	cout << "Choose tree number. ";
	int num = get_value();
	while (num < 0 || num >= count)
	{
		cout << "You've written the wrong number!\n";
		num = get_value();
	}
	cout << "We have function that adds elements. There's reduce result:\n\n";

	switch (type)
	{
	case 1:
	{
		int a = reduce_lnr(sum_elements, int_base[num].GetRoot());
		cout << a << endl;
		cout << endl;
		break;
	}
	case 2:
	{
		float a = reduce_lnr(sum_elements, float_base[num].GetRoot());
		cout << a << endl;
		cout << endl;
		break;
	}
	}
}

void interface()
{
	print_hello();
	cout << endl;
	int_base = vector<Tree3<int>>();
	float_base = vector<Tree3<float>>();
	int menu_res = menu();
	while (menu_res != 6)
	{
		int op;
		switch (menu_res)
		{
		case 1:
			create_tree();
			cout << endl;
			break;
		case 2:
			show_trees();
			break;
		case 3:
			delete_tree();
			cout << endl;
			break;
		case 4:
			op = operations_menu();
			cout << endl;
			while (op != 8)
			{
				switch (op)
				{
				case 1:
					add();
					cout << endl;
					break;
				case 2:
					delete_sought();
					cout << endl;
					break;
				case 3:
					delete_sought_recursive();
					cout << endl;
					break;
				case 4:
					get_branch();
					cout << endl;
					break;
				case 5:
					to_string();
					break;
				case 6:
					map_tree();
					break;
				case 7:
					reduce_tree();
					break;
				}
				op = operations_menu();
			}
			break;
		case 5:
			tests::tree3::test_all();
			cout << "tree3 tests OK\n";
			break;
		}
		cout << endl;
		menu_res = menu();
		cout << endl;
		cout << "There are:\n";
		cout << int_base.size() << " int trees\n";
		cout << float_base.size() << " float trees\n";
		cout << endl;
	}

}