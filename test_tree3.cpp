#include "test_tree3.h"
#include "tree3.h"
#include <cassert>

using namespace tree3;

namespace tests::tree3
{
	
void test_constructors()
{
	Tree3<int> t0{};
	assert(t0.Depth() == 0);
	assert(t0.PathSearch("") == nullptr);
	
	Tree3<int> t1(12);
	assert(t1.Depth() == 1);
	assert(t1.PathSearch("")->data == 12);

	Tree3<char> t2('d');
	assert(t2.Depth() == 1);
	assert(t2.PathSearch("")->data == 'd');

	Tree3<float> t3(3.45);
	assert(t3.Depth() == 1);
	assert(abs(t3.PathSearch("")->data - 3.45) < 0.00001);

	t1.Add(2);
	Tree3<int> t4(t1);
	assert(t4.Depth() == 2);
	assert(t4.PathSearch("")->data == 12);
	assert(t4.PathSearch("l")->data == 2);

	t4.Add(1);
	t4.Add(2);
	t4.Add(0);
	Tree3<int> t5(t4.PathSearch("l"));
	assert(t5.Depth() == 3);
	assert(t5.PathSearch("")->data == 2);
	assert(t5.PathSearch("c")->data == 2);
	assert(t5.PathSearch("l")->data == 1);
	assert(t5.PathSearch("ll")->data == 0);
}

int float_cmp(const float& l, const float& r)
{
	if(abs(l - r) < 0.00001)
	{
		return 0;
	}
	if(l > r)
	{
		return 1;
	}
	return -1;
}
	
void test_add_search()
{
	Tree3<int> t1(10);
	t1.Add(1);
	t1.Add(4);
	t1.Add(5);
	t1.Add(3);
	t1.Add(2);
	t1.Add(11);
	t1.Add(14);
	t1.Add(1);
	assert(t1.PathSearch("")->data == 10);
	assert(t1.PathSearch("l")->data == 1);
	assert(t1.PathSearch("lc")->data == 1);
	assert(t1.PathSearch("lr")->data == 4);
	assert(t1.PathSearch("lrr")->data == 5);
	assert(t1.PathSearch("lrl")->data == 3);
	assert(t1.PathSearch("lrll")->data == 2);
	assert(t1.PathSearch("r")->data == 11);
	assert(t1.PathSearch("rr")->data == 14);
	assert(t1.Depth() == 5);

	
	bool error = false;
	try
	{
		t1.PathSearch("lrf");
	}
	catch (std::exception& e)
	{
		error = true;
		assert(strcmp(e.what(), "Tree3 PathSearch: path must contain only 'lcr' symbols") == 0);
	}
	assert(error);
	
	assert(t1.Search(20) == nullptr);
	assert(t1.Search(-1) == nullptr);
	assert(t1.Search(4)->data == 4);
	assert(t1.Search(4)->right->data == 5);
	assert(t1.Search(4)->left->data == 3);
	assert(t1.Depth(t1.Search(4), 0) == 3);

	assert(t1.Search(1)->data == 1);
	assert(t1.Search(1)->central->data == 1);
	assert(t1.Search(1)->central->central == nullptr);

	Tree3<float> t2(10.0);
	t2.Add(1.0);
	t2.Add(4.0);
	t2.Add(5.0);
	t2.Add(3.0);
	assert(t2.Search(5.01, float_cmp) == nullptr);
	assert(t2.Search(2.99, float_cmp) == nullptr);
	assert(t2.Search(1.02, float_cmp) == nullptr);
	assert(float_cmp(t2.Search(5.00, float_cmp)->data, 5.0) == 0);
	assert(float_cmp(t2.Search(4.000, float_cmp)->data, 4.0) == 0);
}
	
void test_delete()
{
	Tree3<int> t1(10);
	t1.Add(1);
	t1.Add(4);
	t1.Add(5);
	t1.Add(3);
	t1.Add(2);
	t1.Add(11);
	t1.Add(14);
	t1.Add(1);

	t1.Delete(t1.Search(4));
	assert(t1.Depth() == 4);
	assert(t1.PathSearch("lr")->data == 3);
	assert(t1.PathSearch("lrr")->data == 5);
	assert(t1.PathSearch("lrl")->data == 2);
	assert(t1.PathSearch("lrll") == nullptr);

	t1.DeleteRecursive(t1.Search(3));
	assert(t1.Depth() == 3);
	assert(t1.PathSearch("lr") == nullptr);
	assert(t1.PathSearch("l")->data == 1);
	assert(t1.PathSearch("lc")->data == 1);
	assert(t1.PathSearch("")->data == 10);
	assert(t1.PathSearch("r")->data == 11);
	assert(t1.PathSearch("rr")->data == 14);
}
	
void test_branch()
{
	Tree3<int> t1(10);
	t1.Add(1);
	t1.Add(4);
	t1.Add(5);
	t1.Add(3);
	t1.Add(2);
	t1.Add(11);
	t1.Add(14);
	t1.Add(1);

	Tree3<int> b1{ t1.Search(4) };
	assert(b1.Depth() == 3);
	assert(b1.PathSearch("")->data == 4);
	assert(b1.PathSearch("r")->data == 5);
	assert(b1.PathSearch("l")->data == 3);
	assert(b1.PathSearch("ll")->data == 2);

	Tree3<int> b2{ t1.Search(11) };
	assert(b2.Depth() == 2);
	assert(b2.PathSearch("")->data == 11);
	assert(b2.PathSearch("r")->data == 14);

	assert(t1.PathSearch("")->data == 10);
	assert(t1.PathSearch("l")->data == 1);
	assert(t1.PathSearch("lc")->data == 1);
	assert(t1.PathSearch("lr")->data == 4);
	assert(t1.PathSearch("lrr")->data == 5);
	assert(t1.PathSearch("lrl")->data == 3);
	assert(t1.PathSearch("lrll")->data == 2);
	assert(t1.PathSearch("r")->data == 11);
	assert(t1.PathSearch("rr")->data == 14);
	assert(t1.Depth() == 5);
}
	
void test_to_from_string()
{
	Tree3<int> t1(3);
	t1.Add(1);
	t1.Add(4);
	t1.Add(5);
	t1.Add(4);
	std::string s1 = t1.ToString();
	assert(strcmp(s1.c_str(), "<3>(<1>){<4>[<4>]{<5>}}") == 0);
	std::string s2 = t1.ToString("(3)*K*{1}[2]");
	assert(strcmp(s2.c_str(), "((*5*)*4*[*4*])*3*{*1*}") == 0);
	std::string s3 = t1.ToStringParentChild();
	assert(strcmp(s3.c_str(), "(3 1) (3 4) (4 4) (4 5) ") == 0);

	Tree3<int> t2(s1);
	assert(t2.Depth() == 3);
	assert(t2.PathSearch("")->data == 3);
	assert(t2.PathSearch("l")->data == 1);
	assert(t2.PathSearch("r")->data == 4);
	assert(t2.PathSearch("rc")->data == 4);
	assert(t2.PathSearch("rr")->data == 5);

	Tree3<int> t3("((*5+)*4+[*4+])*3+{*1+}", "(3)*K+{1}[2]");
	assert(t3.Depth() == 3);
	assert(t3.PathSearch("")->data == 3);
	assert(t3.PathSearch("l")->data == 1);
	assert(t3.PathSearch("r")->data == 4);
	assert(t3.PathSearch("rc")->data == 4);
	assert(t3.PathSearch("rr")->data == 5);

	bool error = false;
	try
	{
		Tree3<int> t(s1, "456789");
	}
	catch (std::exception& e)
	{
		error = true;
		assert(strcmp(e.what(), "Tree3 FromString: format must have 12 "
			"non_space latin symbols, brackets around elements must be unique "
			"for each branch and pair, there is an example - '<K>(1)[2]{3}'") == 0);
	}
	assert(error);
}

int char_to_int(char item)
{
	return item;
}
	
void test_map()
{
	Tree3<char> t('a');
	t.Add('g');
	t.Add('r');
	t.Add('p');
	t.Add('s');

	Tree3<int> t1 = map_tree3(&t, char_to_int);
	assert(t.Depth() == 4);
	assert(t.PathSearch("")->data == 97);
	assert(t.PathSearch("r")->data == 103);
	assert(t.PathSearch("rr")->data == 114);
	assert(t.PathSearch("rrl")->data == 112);
	assert(t.PathSearch("rrr")->data == 115);

	Tree3<char> t2{};
	Tree3<int> t3 = map_tree3(&t2, char_to_int);
	assert(t3.Depth() == 0);
}

int sum_integer(int a, int b)
{
	return a + b;
}

void test_reduce()
{
	Tree3<int> t1(10);
	t1.Add(1);
	t1.Add(4);
	t1.Add(5);
	t1.Add(3);
	t1.Add(2);
	t1.Add(11);
	t1.Add(14);
	t1.Add(1);

	int res = reduce_lrn(sum_integer, t1.GetRoot());
	assert(res == 51);
	res = reduce_lrn(sum_integer, t1.Search(4));
	assert(res == 14);
}

void test_all()
{
	test_constructors();
	test_add_search();
	test_delete();
	test_branch();
	test_to_from_string();
	test_map();
	test_reduce();
}

}