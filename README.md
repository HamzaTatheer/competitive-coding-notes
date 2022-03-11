# Competitive Coding Practice notes
coding/maths questions with intuitive understanding and lessons learned


## MYSQL NOTES

COUNT(*) will count all the rows in the table, including NULL values. On the other hand, COUNT(column name) will count all the rows in the specified column while excluding NULL values

there is = operator for comparing strings in mysql. instead use strcmp().
For substring comparison, use substr(column_name,start,end) but remember that index starts at 1 not 0

in mysql, there is no top but limit

for subtracting from total - some rows

use select count(*) - count(DISTINCT CITY) from station


Query the list of CITY names starting with vowels (i.e., a, e, i, o, or u) from STATION. Your result cannot contain duplicates.

simple way

SELECT DISTINCT CITY FROM STATION 
WHERE 
STRCMP(SUBSTR(CITY,1,1),'a')=0
OR
STRCMP(SUBSTR(CITY,1,1),'e')=0
OR
STRCMP(SUBSTR(CITY,1,1),'i')=0
OR
STRCMP(SUBSTR(CITY,1,1),'o')=0
OR
STRCMP(SUBSTR(CITY,1,1),'u')=0
;

regular expression

SELECT DISTINCT CITY FROM STATION
WHERE REGEXP_LIKE(CITY,'^[aeiou]')

another way

SELECT DISTINCT CITY FROM STATION
WHERE REGEXP_LIKE(CITY,'a|e|i|o|u')

another

SELECT DISTINCT CITY FROM STATION
WHERE REGEXP_LIKE(CITY,'^a|^e|^i|^o|^u')

but second is better

SELECT COUNT(*) - COUNT(SELECT DISTINCT CITY FROM STATION) FROM STATION

The above wont work as Count expects data of table in the From clause
instead something like this works

SELECT COUNT(*) - (SELECT COUNT(DISTINCT CITY) FROM STATION) FROM STATION;

unlike sql, it is COUNT(DISTINCT CITY) not DISTINCT COUNT(CITY)


cities that start with and ends with vowels (notice use of '.')
SELECT CITY FROM STATION WHERE CITY REGEXP '^[aeiou].*.[aeiou]$';


I had to change some values from select query. I tried update but it was wrong as update only works on created tables

SELECT (CASE WHEN GRADE < 8 THEN NULL ELSE NAME END) AS NAME,GRADE,MARKS
FROM
(
SELECT NAME,(SELECT GRADE FROM GRADES AS G WHERE S.MARKS BETWEEN G.MIN_MARK AND G.MAX_MARK) AS GRADE,MARKS
FROM STUDENTS AS S
ORDER BY GRADE DESC, NAME ASC
) AS REPORT;




## Question 1

<img src='https://github.com/HamzaTatheer/competitive-coding-notes/blob/main/images/stats_question.png?raw=true'/>

### Solution 1

Simply use dynamic programing. If i tell you there are two paths leading to a point and those paths themselves have 3 and 4 different paths leading to them respectively, then the current point will have 3+4 = 7 paths leading to. You can build up the solution for the points ahead of it

<img src='https://github.com/HamzaTatheer/competitive-coding-notes/blob/main/images/solution1.png?raw=true'/>

### Solution 2

One thing is for sure. you need to take 7 steps in or to reach to the end point.
3 of them are UP (lets call it U)
4 of them are RIGHT (lets call it R)

so if we write that as a string we can have a pattern like
UUURRRR

and this pattern could also be

RRUUURR

and this could also be

RUUURRR

wait a minute ?

doesnt that mean this is all possible permutations of the this sentence. you guessed right.

we could simply use 7!. But wait, does it make a difference if two R's or two U's or in fact, any same letters are swapped ? But 7! thinks each of one them as a different entity while we do not care so it would treat two same letters swapped as different sequences

Solution ? Multinomial rule
In order to remove this bias. Our solution will be 7!/(4! * 3!) = 35


## Question 2. Given a smaller strings and a bigger string b, design an algorithm to find all permutations of the shorter string within the longer one. Print the location of each permutation.

len(s1) = n
len(s2) = m

1. Find permutations
2. search


with these two steps. Assuming that perm(s2) = O(m)
and loop of n iterations
we get complexity of O(nm)

seems okayish. we can go lower

1. store s2 in hash map O(m)
2. Loop through s1 O(n)
	
	if any letter is present in hashmap, keep going untill all letters are covered
	if you have covered the whole hash map
	you found one occurence otherwise word is incomplete
	(reset loop from next letter where the word started)
	
O(m+n) (approximate)

One can alternatively use bit vector. store s2 inside a bit vector.

## Question 3. Is Unique: Implement an algorithm to determine if a string has all unique characters. What if you cannot use additional data structures?

### solution 1 with data structure
put all characters in hash map
incremenet counter (h[letter]+=1)
if any one of them, exceeds 1, then its not unique


Alternative Solution Found: Bit Vector can be used
Advantage seems to be that whereas hashmap uses lots of space
as each increment means one integer space ( 8 bit ).
So a thousand characters would be 8000 bits needed. (more space complexity)
This approach uses only 8 bits in total memory.

int bits = 00000000000...(=0)

in order to change a bit we add 2^A where A is bit no (0,1,2,3)
so if we find 'a' 
-> convert ascii to integer (a)
-> if AND(bits,2^a) = 1, then number is not unique
-> Otherwise bits = bits + 2^a

This approach has O(1) as space complexity

complexity O(n)

### solution 2 without data structure
Best Concievable run time is O(n) as
each letter needs to be visited once

we can use O(n^2) by have one loop for iteration and one loop for comparison

sort array as letters are simply assci values (nlogn)
iterate through it and check if current and previous letter is same O(m)
complexity O(n+nlogn)=O(n)


## Question 4. Given a string, write a function to check if it is a permutation of a palindrome. A palindrome is a word or phrase that is the same forwards and backwards. A permutation is a rearrangement of letters. The palindrome does not need to be limited to just dictionary words.


For a string to be part of palindrome.
if its length is even number
then each letter must occur twice (use two bit strings to keep track instead of hasmap in order to save memory)
if its length is odd number
then each letter must occur twice and one should occur only once
use hashmap to store number of occurences.

Afterwards, simply pass through hashmap to confirm these properties.
Algorithm is O(n)


## Question 5. One Away: There are three types of edits that can be performed on strings: insert a character, remove a character, or replace a character. Given two strings, write a function to check if they are one edit (or zero edits) away. (TRY AGAIN)

Best concievable time is O(n+m) as you need to go through each string atleast once

1. insert and delete (solved. just compare length) O(1)
	-> if len is different return True
	-> But how do you know if rest of letters are same ???????
	
2. replace (go through string and store number of mismatches. if one is different. its replace)
	mismatch+=1
	-> if (mismatch >2)
		return True
		
return False

Above solution is incorrect

### Final Solution

1. Loop through array and record mismatch
2. if there is a mismatch and length is different,skip character in larger array and continue recording mismatches (while skipping the current one) 

at the end,
if lengths were different and no of mismatches == 0 return True
if lengths were same and no of mismatches = 1 return True
otherwise return False

## Question 6. (REVISE AGAIN)

Given a circular linked list, implement an algorithm that returns the node at the
beginning of the loop.
DEFINITION
Circular linked list: A (corrupt) linked list in which a node's next pointer points to an earlier node, so
as to make a loop in the linked list.
EXAMPLE
Input: A - > B - > C - > D - > E - > C [the same C as earlier]
Output: C



This question was a tough one. One solution was solving it with hasmap.
This meant that there would be O(n) space.

I also tried reversing the linkedlist while visiting each node
but there was no success.

Final Solution:

<img src='https://github.com/HamzaTatheer/competitive-coding-notes/blob/main/images/ques.png?raw=true'/>


Use two pointers p1 and p2. p1 takes 1 step and p2 takes 2 step
if there is no loop, p1 and p2 will never collide.
If, however, there is a loop, there will come a time when p1 and p2
will collide and p2/p1 will need to take p steps to reach starting of node
where p is also the number of steps needed to reach the starting of node
from head of linked list. We can then increment a new pointer from head
and another from collision. Once they meet the same point, this is the starting node.


Lets proof this distance p

distance covered by p1 to reach start of loop: p
distance covered by p2 when p1 reached start of loop: 2p
displacement of p2 from start of loop: (2p-p)mod n == p mod n  (where is n is loop size)

p1 will be going at 1 step at a time while p2 will be going 2 steps at a time.
p2 will actually be slowly catching up the distance from p1 as its faster
untill it catches it.

so if p2 is at 5m from p1
When p2 covers 5 more meters, due to double speed p1 will have caught up.
i.e 2*5 = 5+5, 2*100 = 100+100. we always catch up (where 5,100 dist betw p1,p2)

we know displacement of p2 from start. as p1 is orignally at start of loop.
What is the distance from start of loop to cover (i.e till p1) ? 
n -  displacement of p2 = n - ((p) mod n)


1) 2*(n-((p)mod(n))) is the distance covered by p2 in order to reach p1

2) And p1 will will be (n-((p)mod(n))) away from its current position (start of loop)



you can use either 1) or 2) to find the position of collision.
lets use 2 as its easier 
 
we know that p1 is (n-((p)mod(n)) away from start of loop.
So how much distance is needed to reach end of loop ?

it is 
= n - (n-((p)mod(n)) 
= (p mod(n))

One case is easy: p < n
in that case p mod(n) = p.

So we can move one pointer from head to cover p distance while pointer
from collision point also covers p distance and collision tells us the start of loop

The main takeaway is that by moving one step for both pointers,
it WILL converge at start of loop and NOT miss each other.

What if p >= n

we will utilise the equation

collision pointer location = p mod n

can two different p with same n have the same collision pointer location ?
yes.


lets say p = 13, n = 10
13 mod 10 = 3;

make p = p - n means the collision pointer remains same
i.e 3 mod 10 = 3.

as a equation like X mod 10 = 3 starts with a 3 mod 10 and goes like 3+10 mod 10, 3+10+10 mod 10 ..

so such a subtraction would bring us to such a case
where p = p mod n (as p < n because we subtracted n)

Hence, In order to execute this, we move both collision pointer and head equally.
upon completing n steps, collision pointer comes back at same place (as its a loop)
while p becomes smaller by n steps(Yet coresponding collision pointer of new p hasnt changed. 23 mod 10 == 13 mod 10 == 3 mod 10)

Subtracting n steps(one by one,multiple times) would make us converge to the base case p < n and p = p mod n which ensures
that our two pointers will meet as both are p steps away from each other.


## Question 7.

Sort Stack: Write a program to sort a stack such that the smallest items are on the top. You can use
an additional temporary stack, but you may not copy the elements into any other data structure
(such as an array). The stack supports the following operations: push, pop, peek, and is Empty.

A naive solution for this question exists. Take minimum element out of s1 by popping out of it and storing those temporarily in another stack.
Afterwards, you put those taken from s1, back in s1 besides the minimum one which you put back in s2 temporary stack and keep it there forever.

You keep going like this while not altering the ordered values in s2, Untill s1 becomes empty.

Afterwards you put s2 elements in s1 which reverses them and gives us the order we want.

Complexity is O(n^2) and space O(2n)

```
while(!s1.empty()) {

	count_s1 = 0;
	min_val = INT_MAX;
	while(!s1.empty()){
		value = s1.pop();
		min_val = min(value,INT_MAX);
		s2.push(value);
		count_s1++;
	}
	
	no_of_mins = 0;
	
	while(count_s1 > 0){
		value = s2.pop();
		if(value != min_val)
			s1.push(value);
		else
			no_of_mins++;	
		count_s1--;
	}

	while(no_of_mins != 0)
		s2.push(min_val)

}
```
Another alternative simpler solution:
we should simply put values in s2 in sorted order from s1.
When our value to be inserted is out of order, we take the other ones out (temporarily in s1) and then put our value at its correct place and then put temporary ones of s1 back in s2 on top of our value.

we keep repeating this.

Both have O(n^2) time complexity and O(n) space



## Question 8.

Route Between Nodes: Given a directed graph, design an algorithm to find out whether there is a
route between two nodes.


solution: simple bfs

put start node in queue

extract
put its neighbours in queue
if reached, then good


BUT, remember one thing, you need to mark node as visited.
otherwise, you can keep repeating a cycle or repeat a node multiple times.


Another Solution is to start BFS from both nodes and stop when both meet in any position, otherwise finish all path and return False


## Question 9.

Minimal Tree: Given a sorted (increasing order) array with unique integer elements, write an algo­
rithm to create a binary search tree with minimal height.


BuildTree(g,arr,root,s,e)

	if(s==e)
		return arr[s];

	index = (s+e)/2
	val = arr[index]

	Node n = new Node(val)
	
	if(root != NULL)		
		g.connect(root,n)


		g.connect(root,g.BuildTree(g,arr,n,s,index+s-1))
		g.connect(root,g.BuildTree(g,arr,n,index+s+1,e))

	return root


BuildTree(g,arr,NULL,0,len(arr))

## Question 10

List of Depths: Given a binary tree, design an algorithm which creates a linked list of all the nodes
at each depth (e.g., if you have a tree with depth D, you'll have D linked lists).


High Level Idea, finding depth and managing array is needed

createList(lists,node,d){

	if(node == NULL)
		return;

	lists[d].insert(node);
	createlists(lists,node.left,d+1);
	createlists(lists,node.right,d+1);
}

createList(lists,root,0);


## Question 11

Implement a function to check if a binary tree is balanced. For the purposes of
this question, a balanced tree is defined to be a tree such that the heights of the two subtrees of any
node never differ by more than one.


WRONG IMPLEMENTATION BELOW. Under this implementation. you are check parent left tree and right tree difference.
you need to check difference for each sub tree.

Algorithm should work ideally in O(n)  (TRY_AGAIN)

```	
max_depth - min_depth 
	
where end of depth is defined as (nodes having null ptrs on left and right)

This difference should be 1, not more.



getDepth(node,d,max_depth,min_depth)

	if(node.left == NULL && node.right == NULL)
		min_depth = min(min_depth,d)
		max_depth = max(max_depth,d)
	else
		getDepth(node.left,d+1,max_depth,min_depth)
		getDepth(node.right,d+1,max_depth,min_depth)
		
		
max_depth = INT_MIN;
min_depth = INT_MAX;
getDepth(root,0,max_depth,min_depth)		

if(|max_depth - min_depth| <= 1)
	print('balanced');
else
	print('not balanced')
	
```


## Question 12

Write an algorithm to find the "next" node (i.e., in-order successor) of a given node in a
binary search tree. You may assume that each node has a link to its parent.



if has right child then, right left.
else
left child ancestors





reachNode(search,node,ans)

	found = False;
	dir = ''

	if(search < node)
		found = reachNode(search,node.left,ans)
		dir = 'l'

	if(search > node)
		found = reachNode(search,node.right,ans)
		dir = 'r'
	
	if(found == False)
		if(dir == 'l')
			ans = node.val;
			return True;

		
	if(search == node.val)
	
		if(node.right != NULL)
			ans = stage2();
			return True;		
		else
			return False;
			
			
			
	return false;
		

## Question 13

<img src='https://github.com/HamzaTatheer/competitive-coding-notes/blob/main/images/47.png?raw=true'/>

Depth First Search can also be used. Keep going untill you reach the project to be completed.
It will always be the last thing to finish. So add it to the end of list. When you go one step back due to recursion.
If the previous node doesnt have any other children, then it is correct to say that it will be the project completed prior to orignal project.
If it does have other children, we can traverse it to reach the same situation as before (last project) and do the same thing as we did before.

Once we have covered all the childs of the node, we know that everything occuring after it is already part of the list. The prior task to completing them would be our current node.



# Code Forces

## <a href='https://codeforces.com/problemset/problem/1279/C'>Stack Of Presents</a>

```
#include <iostream>
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

#define FOR(i, j, k, in) for (LL int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (LL int i=j ; i>=k ; i-=in)
#define LL long long

LL int getTime(){
    
    LL int n,m;
    LL int* arr1;
    cin >> n;
    cin >> m;

    arr1 = new LL int[n+1];
    unordered_map<LL int,LL int> arr1_map;

    LL int i;
    FOR(i,1,n+1,1){
        scanf("%lld",&arr1[i]);
        arr1_map[arr1[i]]=i;
    }
    

    LL int p_i = 0;//previous index at which gift was found
    LL int t =0;//total time
    i=1;
    FOR(i,1,m+1,1){
        
        LL int item = 0;
        scanf("%lld",&item);

        //line below was previous approach and gave time exceeded
        //trying hashmap instead
        // int j=1;
        // while(arr1[j] != item){
        //     j++;
        // }
        
        LL int j=arr1_map[item];

        if(j < p_i){
            //printf("t+=1\n");
            t+=1;
        }
        else{
            LL int k = j-1; //boxes on top are one more than j
            LL int collected = i-1;
            LL int temp1 = k-collected;
            LL int temp2 = 2*temp1 ;
            LL int temp3 = temp2+1;
            t = (LL int)t + (LL int)temp3;
            //t+= 2*(k-collected) + 1;
            //printf("2*(%lld-%lld) + 1 \n",k,collected);;
            p_i = j;
        }
        

    }

    delete[] arr1;
    arr1 = nullptr;
    return t;
}


int main()
{
    int no_of_cases=1;
    cin>>no_of_cases; //uncomment on submission to use multiple
    
    LL int* arr = new LL int[no_of_cases];
    
    int i =0;
    FOR(i,0,no_of_cases,1){
        arr[i] = getTime();
    }


    FOR(i,0,no_of_cases,1){
        printf("%lld\n",arr[i]);
    }

    delete[] arr;
    arr = nullptr;
    return 0;
}
```

lessons learned
BCR is important. Always use it and utilize operations below it.
Test Cases can let you find flaws quickly
always take care of deletion of memory
keep notice of the size of number and use data type accordingly (use long long)
think of a solution and simplify it as long as it does not beat the previous solution complexity.
use printf and scanf instead of cout and cin
convert to real world scenerios in order to solve quicker



