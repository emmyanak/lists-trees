//Emma Yanakiev

#include <iostream>
#include "recursive.h"
#include <cassert>
#include "p2.h"
#include "Binary_tree.h"
#include <stdlib.h>
//using namespace std;

//SUM Effects: returns the sum of each elements in list zero if the list is empty 

static int sum_helper(list_t list, int result) //helper function for sum 
{
if (list_isEmpty(list)) return result; 
else 
   {
	return sum_helper(list_rest(list), list_first(list) + result);
   }
} 

int sum(list_t list) //sum function 
{
	return sum_helper(list, 0); 
}

//PRODUCT Effects: returns the product of each element in list one if the list is empty 

static int product_helper(list_t list, int result) //helper function for product 
{
if (list_isEmpty(list)) return result;
else 
   {
	return product_helper(list_rest(list), result*list_first(list));
   }
}

int product(list_t list) //product function 
{
	return product_helper(list, 1);
}

//ACCUMULATE Requires: fn must be associative.
//Effects: return identity if list is empty. Otherwise, return the tail recursive equivalent of fn(list_first(list), fn, identity)

static int accumulate_helper(list_t list, int (*fn)(int, int), int identity)
{

if (list_isEmpty(list)) return identity;
else 
    { 
	return accumulate_helper(list_rest(list), fn, fn(list_first(list), identity)); 
    }
       

}

int accumulate(list_t list, int (*fn)(int, int), int identity)
{

if (list_isEmpty(list)) return identity;
else 
    {
	return accumulate_helper(list, fn, identity);  
    }
}

//REVERSE Effects: returns the reverse of the list
list_t reverse_helper(list_t list, list_t helper)
{
if (list_isEmpty(list)) return helper;
else
   {
	return reverse_helper(list_rest(list), list_make(list_first(list), helper));
   }

}

list_t reverse(list_t list)
{
	return reverse_helper(list, list_make());
}

//APPEND Effects: returns the list(first second)


static list_t append_helper(list_t first, list_t second) //helper function for append 
{
if (list_isEmpty(first) && list_isEmpty(second)) return list_make();
else if (!list_isEmpty(second) && list_isEmpty(first)) return second;
else
   {
	return append_helper(list_rest(first), list_make(list_first(first), second));
   }

} 

list_t append(list_t first, list_t second) //append function 
{
	first = reverse(first);
	return append_helper(first, second);
}

//FILTER ODD Effects: returns a new list containing only the elements of the original list which are odd in value, in the order which they appeared in the list

static int odd(int a) //checks if an integer is odd
{
if ((a % 2) != 0) return 1;
else return 0;
}

static list_t filter_odd_helper(list_t list, list_t helper) //filter odd helper 
{
if (list_isEmpty(list)) return helper;
if (odd(list_first(list)) == 1)
  {
	return filter_odd_helper(list_rest(list), list_make(list_first(list), helper));
  }
else
  {
	return filter_odd_helper(list_rest(list), helper);
  }
}

list_t filter_odd(list_t list) //filter odd function 
{
	list = reverse(list);
	return filter_odd_helper(list, list_make());
}

//FILTER EVEN Effects: returns a new list containing only the elements of the original list which are odd in value, in the order which they appeared in the list

static int even(int a) //checks if integer is even 
{
	if ((a % 2) == 0) return 1;
	else return 0;
}

static list_t filter_even_helper(list_t list, list_t helper) //filter even helper 
{
if (list_isEmpty(list)) return helper;
if (even(list_first(list)) == 1)
  {
	return filter_even_helper(list_rest(list), list_make(list_first(list), helper));
  }
else
  {
	return filter_even_helper(list_rest(list), helper);
  }
}

list_t filter_even(list_t list) //filter even function 
{
	list = reverse(list);
	return filter_even_helper(list, list_make()); 
}

//FILTER// Effects: returns a new list containing precisely the elements of a list for which the predicate fn() evaluates to true, in the order which they appeared in the list 

static list_t filter_helper(list_t list, bool (*fn)(int), list_t helper) //helper for filter
{
if (list_isEmpty(list)) return helper; 
if (fn(list_first(list)))
 {
 	return filter_helper(list_rest(list), fn,  list_make(list_first(list), helper));
 }
else
 {
 	return filter_helper(list_rest(list), fn,  helper);
 }
}


list_t filter(list_t list, bool (*fn)(int))
{
	list = reverse(list);
	return filter_helper(list, fn, list_make());
}

//ROTATE//Requires: n >= 0;
//Effects: Returns a new list whose elements are in the order that would result from moving the front element of this list to the back, repeated n times

static list_t rotate_helper(list_t list, int n) //rotate helper ****CHECK FOR REVERSE
{
if (list_isEmpty(list)) return list;
if (n == 0) return list;

else return rotate_helper(list_make(list_first(reverse(list)), chop(list,1)), n-1);
}

list_t rotate(list_t list, int n) //rotate helper 
{
	list = reverse(list); 
	return reverse(rotate_helper(list, n)); 
}

//INSERT LIST Requires n >= 0 and n <= the number of elements in the first
//Effects: returns a list comprising the first n elements of "first", followed by all the elements of "second", followed by any remaining elements of "first"
 
static list_t insert_list_helper(list_t first, list_t second, int n, list_t helper) //insert list helper 

{
if (list_isEmpty(first) && list_isEmpty(second)) return list_make();
if (n == 0) 
  {
	return append(append(reverse(helper), second), first);
  }

else 
  {
	return insert_list_helper(list_rest(first), second, n-1, list_make(list_first(first), helper));
  }
}

list_t insert_list(list_t first, list_t second, int n) //insert list 
{
if (n == 0) return second;
else 
	return insert_list_helper(first, second, n, list_make());
}

//CHOP Requires: n >= 0 and a list has at least n elements
//Effects: returns the list equal to list without its last n elements

static list_t chop_helper(list_t list, int n, list_t helper) //chop helper
{
if (list_isEmpty(list)) 
{
	return list; 
}
if (n == 0) 
 {	
	return list;
 }
else 
 {
	return chop_helper(list_rest(list), n-1,list_make(list_first(list), helper));
 }
} 



list_t chop(list_t list, int n) //chop function
{
	list = reverse(list); 
	return reverse((chop_helper(list, n, list_make())));   
}


//FIBONACCI RECURSION
//Requires: n >= 0;
//Effects: computes the Nth fibonacci number

int fib(int n)
{
if (n == 0) return 0;
else if (n == 1) return 1;
else return fib(n-1) + fib(n-2);
}


//FIBONACCI TAIL RECURSION
//Requires: n >= 0;
//Effects: computes Nth fibonacci number

static int fib_tail_helper(int n, int a, int b)
{
if (n == 1) return a; 
else return fib_tail_helper(n-1,a+b, a);  
}

int fib_tail(int n)
{
if (n == 0) return 0; 
else if (n == 1) return 1;
else return fib_tail_helper(n, 1, 0); 
}



//TREE SUM 
int tree_sum(tree_t tree)
{
if (!tree_isEmpty(tree))
{ 
      return (tree_elt(tree)) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));   
}
else 
return 0; 
}


//TREE TRAVERSAL 
list_t helper_traversal(tree_t tree, list_t list) 
{

 if (!tree_isEmpty(tree))
    
    { 
	list = helper_traversal(tree_left(tree), list);   
	list = list_make(tree_elt(tree),list);
	list = helper_traversal(tree_right(tree), list); 
     }   
	return list;
}

list_t traversal(tree_t tree)
{
return reverse(helper_traversal(tree, list_make()));
}


//COVERED BY (helper to contained by)
bool covered_by(tree_t A, tree_t B)
{
bool result = false;
if (!tree_isEmpty(A) && !tree_isEmpty(B))
   {
    if (tree_elt(A) == tree_elt(B))
	result = true;
    else 
	result = false;
    result = result && covered_by(tree_left(A), tree_left(B));
    result = result && covered_by(tree_right(A), tree_right(B));  
   }
else if (tree_isEmpty(A))
   {
	result = true;
   }
	return result; 
}

//CONTAINED BY 
bool contained_by(tree_t A, tree_t B) 
{
bool result = false;

if (!tree_isEmpty(A) && !tree_isEmpty(B))
  { 
   result = covered_by(A, B);
   result = result || covered_by(A, tree_left(B));
   result = result || covered_by(A, tree_right(B));  
  }
else if (tree_isEmpty(A))
  {
   result = true;
  }

return result; 
}



//TREE INSERT 
tree_t insert_tree(int elt, tree_t tree)
{

//assert(false);
if(tree_isEmpty(tree)) //if empty, just put the new element in
{
  return tree_make(elt, tree_make(), tree_make());
}

if (elt < tree_elt(tree))  //if new element smaller than node, needs to go left
{
  if(tree_isEmpty(tree_left(tree)))  //once found an empty spot to the left, put it there
  {  
    return tree_make(tree_elt(tree), tree_make(elt,tree_make(),tree_make()), tree_right(tree));
  }                                  // and reconstruct the right side
  else
  {
    tree_t left = insert_tree(elt, tree_left(tree)); //save left tree for reconstruction (down)
    return tree_make(tree_elt(tree), left, tree_right(tree)); //reconstruct tree going up
  }     
}     
else  //if elt >= tree_elt(tree) needs to go right
{
  if(tree_isEmpty(tree_right(tree)))  //empty spot to the right, put it there
  {
    return tree_make(tree_elt(tree), tree_left(tree), tree_make(elt,tree_make(),tree_make()));     
  }                                   //and reconstruct the left side
  else
  {
    tree_t right = insert_tree(elt, tree_right(tree)); //save right tree for reconstruction (down)
    return tree_make(tree_elt(tree), tree_left(tree), right);  //reconstruct tree going up  
  }     

}  //end of search for placement of new element

}
	

//TREE FOLD 
tree_t fold(tree_t tree, int level)
{

   if (tree_isEmpty(tree))
   {
      return tree_make(); 
   }
   if (level == 0)
   {    
	return tree_make(tree_sum(tree), tree_make(), tree_make());
   }
   else  
   {
      tree_t left = fold(tree_left(tree), level-1);
      tree_t right = fold(tree_right(tree), level-1);
      return tree_make(tree_elt(tree), left, right);

   }
}



















