#include<bits/extc++.h>
using namespace __gnu_pbds;

// hash_table：用法和map差不多 //均攤O(1)
gp_hash_table <string,int> mp;
mp.find(); mp[]=;
mp.insert(make_pair())

// heaps
priority_queue<int, greater<int>, TAG> Q;
/*
Tag                 | push  | pop   | join  | modify |
pairing_heap_tag    | O(1)  | O(lgN)| O(1)  | O(lgN) |
thin_heap_tag       | O(lgN)| O(lgN)| 慢    | 慢      |
binomial_heap_tag   | O(1)  | O(lgN)| O(lgN)| O(lgN) |
rc_binomial_heap_tag| O(1)  | O(lgN)| O(lgN)| O(lgN) |
binary_heap_tag     | O(1)  | O(lgN)| 慢    | O(lgN) |
*/   //可以用迭代器遍歷
Q.push(x); Q.pop(); Q.top();
Q.join(b); //merge two heap
Q.empty(); Q.size(); 
Q.modify(it, 6); Q.erase(it);

// k-th
typedef tree<int,null_type,less<int>,rb_tree_tag,
        tree_order_statistics_node_update> set_t;
set_t s; s.insert(12); s.insert(505);
assert(*s.find_by_order(0) == 12);
assert(*s.find_by_order(3) == 505);
assert(s.order_of_key(12) == 0);
assert(s.order_of_key(505) == 1);
s.erase(12);
assert(*s.find_by_order(0) == 505);
assert(s.order_of_key(505) == 0);