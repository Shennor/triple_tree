#pragma once
#include <string>
#include <sstream>
#include <stdexcept>
#include <set>

namespace tree3 {

	template<class T>
	struct Node3
	{
		T data = T{};
		Node3<T>* parent = nullptr;
		Node3<T>* left = nullptr;
		Node3<T>* central = nullptr;
		Node3<T>* right = nullptr;
	};

	// left < central (at the central we have equal elements) < right
	template<class T>
	class Tree3
	{
	private:
		Node3<T>* _root = nullptr;

	public:

		// Constructors

		Tree3() = default;
		Tree3(const T& data);
		Tree3(const Tree3<T>& other);
		Tree3(const Node3<T>* const branch);
		Tree3(std::string s, const std::string format = "<K>(1)[2]{3}");

		// Operations

		Node3<T>* GetRoot();

		void Add(Node3<T>* tree, const T& data);
		void Add(const T& data);
		void AddBranch(Node3<T>* tree, Node3<T>* branch);
		void AddBranch(Node3<T>* branch);

		// if > < == overloaded
		Node3<T>* Search(Node3<T>* tree, const T& sought);
		Node3<T>* Search(const T& sought);
		// with comparator
		Node3<T>* Search(Node3<T>* tree, const T& sought, int (*cmp)(const T&, const T&));
		Node3<T>* Search(const T& sought, int (*cmp)(const T&, const T&));
		Node3<T>* PathSearch(Node3<T>* source, std::string path);
		Node3<T>* PathSearch(std::string path);

		size_t Depth(Node3<T>* tree, size_t cnt);
		size_t Depth();

		void Delete(Node3<T>* tree);
		void DeleteRecursive(Node3<T>* tree);

		std::string ToString(Node3<T>* tree, 
			const std::string format = "<K>(1)[2]{3}");
		std::string ToString(const std::string format = "<K>(1)[2]{3}");
		std::string ToStringParentChild(const Node3<T>* tree);
		std::string ToStringParentChild();

		~Tree3();
	};


	template <class T, class C>
	Tree3<C> map_tree3(Node3<T>* tree, C(*f)(T));
	template <class T, class C>
	Tree3<C> map_tree3(Tree3<T>* tree, C(*f)(T));
	template <class T>
	Tree3<T> map_tree3(Tree3<T>* tree, T(*f)(T));

	// reduce with LRN (post-order) algorithm
	template<class T>
	T reduce_lrn(T(*f)(T, T), Node3<T>* tree, const T& c = T{});
	// reduce with LNR (pre-order) algorithm 
	template<class T>
	T reduce_lnr(T(*f)(T, T), Node3<T>* tree, const T& c = T{});
	// reduce with after-left algorithm 
	template<class T>
	T reduce_al(T(*f)(T, T), Node3<T>* tree, const T& c = T{});
	// reduce with after-center algorithm
	template<class T>
	T reduce_ac(T(*f)(T, T), Node3<T>* tree, const T& c = T{});
	
	// Realization
	
	template<class T>
	std::string tree_to_string(const Node3<T>* tree, std::string res, const std::string format)
	{
		if (tree == nullptr)
		{
			return res;
		}
		for (size_t i = 0; i < 11; i += 3) {
			switch (format[i + 1])
			{
			case 'K':
				res += format[i];
				res += std::to_string(tree->data);
				res += format[i + 2];
				break;
			case '1':
				if(tree->left != nullptr)
				{
					res += format[i];
					res = tree_to_string(tree->left, res, format);
					res += format[i + 2];
				}
				break;
			case '2':
				if (tree->central != nullptr)
				{
					res += format[i];
					res = tree_to_string(tree->central, res, format);
					res += format[i + 2];
				}
				break;
			default: // '3'
				if (tree->right != nullptr)
				{
					res += format[i];
					res = tree_to_string(tree->right, res, format);
					res += format[i + 2];
				}
				break;
			}
		}
		return res;
	}

	template<class T>
	std::string tree_to_string_parent_child(const Node3<T>* tree, std::string res)
	{
		if (tree == nullptr) {
			return res;
		}

		if (tree->left != nullptr)
		{
			res += '(' + std::to_string(tree->data) + ' '
				+ std::to_string(tree->left->data) + ')' + ' ';
			res = tree_to_string_parent_child(tree->left, res);
		}
		if (tree->central != nullptr) {
			res += '(' + std::to_string(tree->data) + ' '
				+ std::to_string(tree->central->data) + ')' + ' ';
			res = tree_to_string_parent_child(tree->central, res);
		}
		if (tree->right != nullptr)
		{
			res += '(' + std::to_string(tree->data) + ' '
				+ std::to_string(tree->right->data) + ')' + ' ';
			res = tree_to_string_parent_child(tree->right, res);
		}
		return res;
	}

	template <class T>
	void tree_from_string(std::string s, std::string format, Node3<T>* const res)
	{
		if (s.empty())
		{
			return;
		}
		for (size_t i = 0; i < 11; i += 3) {
			if (s[0] != format[i])
			{
				continue;
			}
			size_t r;
			if(format[i + 1] == 'K')
			{
				r = s.find_first_of(format[i + 2]);
			}
			else
			{
				r = s.find_last_of(format[i + 2]);
			}
			std::string new_string = s.substr(1, r - 1);
			std::istringstream stream(new_string);
			switch (format[i + 1])
			{
			case 'K':
				stream >> res->data;
				break;
			case '1':
				res->left = new Node3<T>;
				tree_from_string(new_string, format, res->left);
				break;
			case '2':
				res->central = new Node3<T>;
				tree_from_string(new_string, format, res->central);
				break;
			default: // '3'
				res->right = new Node3<T>;
				tree_from_string(new_string, format, res->right);
				break;
			}
			s = s.substr(r + 1, std::string::npos);
		}
	}

	template <class T, class C>
	Tree3<C> tree_map(Node3<T>* tree, C(*f)(T), Tree3<C>& res);

	// copy with creating new Nodes3 in destination
	template<class T>
	void copy_nodes3(const Node3<T>* source, Node3<T>* destination, Node3<T>* destination_parent = nullptr)
	{
		if (source != nullptr || destination != nullptr)
		{
			destination->data = source->data;
			if(destination_parent != nullptr)
			{
				destination->parent = destination_parent;
			}

			if (source->left != nullptr)
			{
				if (destination->left == nullptr)
				{
					destination->left = new Node3<T>;
				}
				copy_nodes3(source->left, destination->left, destination);
			}

			if (source->central != nullptr)
			{
				if (destination->central == nullptr)
				{
					destination->central = new Node3<T>;
				}
				copy_nodes3(source->central, destination->central, destination);
			}
			
			if (source->right != nullptr)
			{
				if(destination->right == nullptr)
				{
					destination->right = new Node3<T>;
				}
				copy_nodes3(source->right, destination->right, destination);
			}
		}
	}

	template <class T, class C>
	Tree3<C> tree_map(Node3<T>* tree, C(*f)(T), Tree3<C>& res)
	{
		if (tree == nullptr)
		{
			return res;
		}
		res.Add(f(tree->data));
		if (tree->left != nullptr)
		{
			tree_map(tree->left, f, res);
		}
		if (tree->central != nullptr)
		{
			tree_map(tree->central, f, res);
		}
		if (tree->right != nullptr)
		{
			tree_map(tree->right, f, res);
		}
		return res;
	}

	template <class T>
	Tree3<T>::Tree3(const T& data)
	{
		_root = new Node3<T>;
		_root->data = data;
	}

	template <class T>
	Tree3<T>::Tree3(const Tree3<T>& other)
	{
		if (other._root != nullptr)
		{
			_root = new Node3<T>;
			copy_nodes3(other._root, _root);
		}
	}

	template <class T>
	Tree3<T>::Tree3(const Node3<T>* const branch)
	{
		_root = new Node3<T>;
		copy_nodes3(branch, _root);
	}

	template <class T>
	Tree3<T>::Tree3(std::string s, const std::string format)
	{
		std::string f = format;
		f.erase(remove_if(begin(f), end(f), isspace),
			end(f));
		std::string error_message = "Tree3 FromString: format must have 12 "
			"non_space latin symbols, brackets around elements must be unique "
			"for each branch and pair, there is an example - '<K>(1)[2]{3}'";

		if (f.size() != 12)
		{
			throw std::invalid_argument(error_message);
		}
		if (f[1] != '1' && f[1] != '2' && f[1] != '3' && f[1] != 'K' ||
			f[4] != '1' && f[4] != '2' && f[4] != '3' && f[4] != 'K' ||
			f[7] != '1' && f[7] != '2' && f[7] != '3' && f[7] != 'K' ||
			f[10] != '1' && f[10] != '2' && f[10] != '3' && f[10] != 'K')
		{
			throw std::invalid_argument(error_message);
		}
		std::set<char> m;
		for (int i = 0; i < 12; ++i)
		{
			m.insert(f[i]);
		}
		if (m.size() != 12)
		{
			throw std::invalid_argument(error_message);
		}
		_root = new Node3<T>;
		tree_from_string(s, f, _root);
	}

	template <class T>
	Node3<T>* Tree3<T>::GetRoot()
	{
		return _root;
	}


	template <class T>
	void Tree3<T>::Add(Node3<T>* tree, const T& data)
	{
		if (data > tree->data)
		{
			if(tree->right == nullptr)
			{
				tree->right = new Node3<T>;
				tree->right->parent = tree;
				tree->right->data = data;
				return;
			}
			Add(tree->right, data);
		}
		if (data < tree->data)
		{
			if (tree->left == nullptr)
			{
				tree->left = new Node3<T>;
				tree->left->parent = tree;
				tree->left->data = data;
				return;
			}
			Add(tree->left, data);
		}
		if (data == (tree)->data)
		{
			if (tree->central == nullptr)
			{
				tree->central = new Node3<T>;
				tree->central->parent = tree;
				tree->central->data = data;
				return;
			}
			Add(tree->central, data);
		}
	}

	template <class T>
	void Tree3<T>::Add(const T& data)
	{
		if(_root == nullptr)
		{
			_root = new Node3<T>;
		}
		Add(_root, data);
	}

	template <class T>
	void Tree3<T>::AddBranch(Node3<T>* tree, Node3<T>* branch)
	{
		if(branch == nullptr)
		{
			return;
		}
		this->Add(tree, branch->data);
		this->AddBranch(tree, branch->left);
		this->AddBranch(tree, branch->central);
		this->AddBranch(tree, branch->right);
	}

	template <class T>
	void Tree3<T>::AddBranch(Node3<T>* branch)
	{
		this->AddBranch(_root, branch);
	}

	template <class T>
	Node3<T>* Tree3<T>::Search(Node3<T>* tree, const T& sought)
	{
		if (tree != nullptr)
		{
			if (sought < tree->data)
				return Search(tree->left, sought);
			if (sought > tree->data)
				return Search(tree->right, sought);
			return tree;
		}
		return nullptr;
	}

	template <class T>
	Node3<T>* Tree3<T>::Search(const T& sought)
	{
		return Search(_root, sought);
	}

	template <class T>
	Node3<T>* Tree3<T>::Search(Node3<T>* tree, const T& sought, int (*cmp)(const T&, const T&))
	{
		if (tree != nullptr)
		{
			if (cmp(sought, tree->data) == 0)
				return tree;
			if (cmp(sought, tree->data) < 0)
				return Search(tree->left, sought);
			if (cmp(sought, tree->data) > 0)
				return Search(tree->right, sought);
		}
		return nullptr;
	}

	template <class T>
	Node3<T>* Tree3<T>::Search(const T& sought, int (* cmp)(const T&, const T&))
	{
		return Search(_root, sought, cmp);
	}


	template <class T>
	Node3<T>* Tree3<T>::PathSearch(Node3<T>* source, std::string path)
	{
		if (path.empty())
		{
			return source;
		}
		switch (path[0])
		{
		case 'l':
			if (source->left == nullptr)
			{
				return nullptr;
			}
			return PathSearch(source->left, path.substr(1));
		case 'c':
			if (source->central == nullptr)
			{
				return nullptr;
			}
			return PathSearch(source->central, path.substr(1));
		case 'r':
			if (source->right == nullptr)
			{
				return nullptr;
			}
			return PathSearch(source->right, path.substr(1));
		default:
			throw std::invalid_argument(
				"Tree3 PathSearch: path must contain only 'lcr' symbols");
		}
	}

	template <class T>
	Node3<T>* Tree3<T>::PathSearch(std::string path)
	{
		return PathSearch(_root, path);
	}

	template <class T>
	size_t Tree3<T>::Depth(Node3<T>* tree, size_t cnt)
	{
		if (tree == nullptr)
		{
			return cnt;
		}
		return std::max(Depth(tree->left, cnt + 1),
			std::max(Depth(tree->right, cnt + 1), 
			Depth(tree->central, cnt + 1)));
	}

	template <class T>
	size_t Tree3<T>::Depth()
	{
		return Depth(_root, 0);
	}

	template <class T>
	void make_me_nullptr_to_my_parent(Node3<T>* tree)
	{
		if (tree->parent->central == tree)
		{
			tree->parent->central = nullptr;
		}
		if (tree->parent->left == tree)
		{
			tree->parent->left = nullptr;
		}
		if (tree->parent->right == tree)
		{
			tree->parent->right = nullptr;
		}
	}
	
	template <class T>
	void Tree3<T>::Delete(Node3<T>* tree)
	{
		if(tree == nullptr)
		{
			return;
		}
		Node3<T>* destination;
		
		if(tree->parent == nullptr)
		{
			destination = _root;
		}
		else {
			destination = tree->parent;
		}
		if (tree->parent != nullptr)
		{
			make_me_nullptr_to_my_parent(tree);
		}
		
		AddBranch(destination, tree->left);
		AddBranch(destination, tree->central);
		AddBranch(destination, tree->right);
		this->DeleteRecursive(tree);
	}

	template <class T>
	void Tree3<T>::DeleteRecursive(Node3<T>* tree)
	{
		if (tree != nullptr)
		{
			if (tree->right != nullptr)
			{
				DeleteRecursive(tree->right);
				tree->right = nullptr;
			}
			if (tree->central != nullptr)
			{
				DeleteRecursive(tree->central);
				tree->central = nullptr;
			}
			if (tree->left != nullptr)
			{
				DeleteRecursive(tree->left);
				tree->left = nullptr;
			}
			
			if (tree->parent != nullptr)
			{
				make_me_nullptr_to_my_parent(tree);
			}
			
			delete tree;
		}
	}

	template <class T>
	std::string Tree3<T>::ToString(Node3<T>* tree, const std::string format)
	{
		std::string f = format;
		f.erase(remove_if(begin(f), end(f), isspace),
			end(f));
		std::string error_message = "Tree3 ToString: format must have 12 "
			"non_space latin symbols, example - '{K}(1)[2]{3}'";

		if (f.size() != 12)
		{
			throw std::invalid_argument(error_message);
		}
		if (f[1] != '1' && f[1] != '2' && f[1] != '3' && f[1] != 'K' ||
			f[4] != '1' && f[4] != '2' && f[4] != '3' && f[4] != 'K' ||
			f[7] != '1' && f[7] != '2' && f[7] != '3' && f[7] != 'K' ||
			f[10] != '1' && f[10] != '2' && f[10] != '3' && f[10] != 'K')
		{
			throw std::invalid_argument(error_message);
		}

		return tree_to_string(tree, "", f);
	}

	template <class T>
	std::string Tree3<T>::ToString(const std::string format)
	{
		return ToString(_root, format);
	}

	template <class T>
	std::string Tree3<T>::ToStringParentChild(const Node3<T>* tree)
	{
		return tree_to_string_parent_child(tree, "");
	}

	template <class T>
	std::string Tree3<T>::ToStringParentChild()
	{
		return ToStringParentChild(_root);
	}

	template <class T, class C>
	Tree3<C> map_tree3(Node3<T>* tree, C(*f)(T))
	{
		if(tree == nullptr)
		{
			Tree3<C> res{};
			return res;
		}
		Tree3<C> res{f(tree->data)};
		if (tree->left != nullptr)
		{
			tree_map(tree->left, f, res);
		}
		if (tree->central != nullptr)
		{
			tree_map(tree->central, f, res);
		}
		if (tree->right != nullptr)
		{
			tree_map(tree->right, f, res);
		}
		return res;
	}

	template <class T, class C>
	Tree3<C> map_tree3(Tree3<T>* tree, C(*f)(T))
	{
		return map_tree3(tree->GetRoot(), f);
	}

	template <class T>
	Tree3<T> map_tree3(Tree3<T>* tree, T(*f)(T))
	{
		return map_tree3(tree->GetRoot(), f);
	}

	template <class T>
	T reduce_lrn(T(*f)(T, T), Node3<T>* tree, const T& c)
	{
		if (tree == nullptr)
		{
			return c;
		}
		T res = c;
		res = reduce_lrn(f, tree->left, res);
		res = reduce_lrn(f, tree->central, res);
		res = reduce_lrn(f, tree->right, res);
		return f(tree->data, res);
	}

	template <class T>
	T reduce_lnr(T(*f)(T, T), Node3<T>* tree, const T& c)
	{
		if (tree == nullptr)
		{
			return c;
		}
		T res = c;
		res = f(tree->data, res);
		res = reduce_lnr(f, tree->left, res);
		res = reduce_lnr(f, tree->central, res);
		res = reduce_lnr(f, tree->right, res);
		return res;
	}

	template <class T>
	T reduce_al(T(*f)(T, T), Node3<T>* tree, const T& c)
	{
		if (tree == nullptr)
		{
			return c;
		}
		T res = c;
		res = reduce_al(f, tree->left, res);
		res = f(tree->data, res);
		res = reduce_al(f, tree->central, res);
		res = reduce_al(f, tree->right, res);
		return res;
	}

	template <class T>
	T reduce_ac(T(*f)(T, T), Node3<T>* tree, const T& c)
	{
		if (tree == nullptr)
		{
			return c;
		}
		T res = c;
		res = reduce_ac(f, tree->left, res);
		res = reduce_ac(f, tree->central, res);
		res = f(tree->data, res);
		res = reduce_ac(f, tree->right, res);
		return res;
	}

	template <class T>
	Tree3<T>::~Tree3()
	{
		this->DeleteRecursive(_root);
	}
}