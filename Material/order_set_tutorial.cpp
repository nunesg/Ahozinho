Let's get started. In this article I will talk about IMO the most interesting of the implemented structures — tree. We need to include the following headers:

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

After closer inspection you may find that the last two files contained in the library

#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace __gnu_pbds; //tem que incluir no codigo

Namespace, which we will have to work in newer versions of C++ is called __gnu_pbds; earlier it was called pb_ds;
Now let's look at the concrete structure.

The tree-based container has the following declaration:
	  template<
	  typename Key, // Key type
	  typename Mapped, // Mapped-policy
	  typename Cmp_Fn = std::less<Key>, // Key comparison functor
	  typename Tag = rb_tree_tag, // Specifies which underlying data structure to use
	  template<
	  typename Const_Node_Iterator,
	  typename Node_Iterator,
	  typename Cmp_Fn_,
	  typename Allocator_>
	  class Node_Update = null_node_update, // A policy for updating node invariants
	  typename Allocator = std::allocator<char> > // An allocator type
	  class tree;
	
Experienced participants may have already noticed that if initialize the template only the first two types, we obtain almost exact copy of the container map. Just say, that this container can be set, for this you just need to specify the second argument template type as null_type ( in older versions it is null_mapped_type).
By the way Tag and Node_Update are missing in map. Let us examine them in more detail.
Tag — class denoting a tree structure, which we will use. There are three base-classes provided in STL for this, it is rb_tree_tag (red-black tree), splay_tree_tag (splay tree) and ov_tree_tag (ordered-vector tree). Sadly, at competitions we can use only red-black trees for this because splay tree and OV-tree using linear-timed split operation that prevents us to use them.
Node_Update — class denoting policy for updating node invariants. By default it is set to null_node_update, ie, additional information not stored in the vertices. In addition, C++ implemented an update policy tree_order_statistics_node_update, which, in fact, carries the necessary operations. Consider them. Most likely, the best way to set the tree is as follows:


typedef tree<int, null_type,  less<int>,  rb_tree_tag,  tree_order_statistics_node_update>  ordered_set;

If we want to get map but not the set, as the second argument type must be used mapped type. Apparently, the tree supports the same operations as the set (at least I haven't any problems with them before), but also there are two new features — it is find_by_order() and order_of_key(). The first returns an iterator to the k-th largest element (counting from zero), the second — the number of items in a set that are strictly smaller than our item. Example of use:

    ordered_set X;
    X.insert(1);
    X.insert(2);
    X.insert(4);
    X.insert(8);
    X.insert(16);

    //find_by_order(0 indexado) - retorna o kesimo menor (se usar less, usando greater é kesimo maior)
    //order_of_key(k) - retorna quantos menores que k tem (se usar less, usando greater é quantos maiores tem)


    cout<<*X.find_by_order(1)<<endl; // 2
    cout<<*X.find_by_order(2)<<endl; // 4
    cout<<*X.find_by_order(4)<<endl; // 16
    cout<<(end(X)==X.find_by_order(6))<<endl; // true

    cout<<X.order_of_key(-5)<<endl;  // 0
    cout<<X.order_of_key(1)<<endl;   // 0
    cout<<X.order_of_key(3)<<endl;   // 2
    cout<<X.order_of_key(4)<<endl;   // 2
    cout<<X.order_of_key(400)<<endl; // 5
