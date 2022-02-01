# Competitive Coding Practice notes
coding/maths questions with intuitive understanding and lessons learned

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

Another alternative simpler solution:
we should simply put values in s2 in sorted order from s1.
When our value to be inserted is out of order, we take the other ones out (temporarily in s1) and then put our value at its correct place and then put temporary ones of s1 back in s2 on top of our value.

we keep repeating this.

Both have O(n^2) time complexity and O(n) space



## Question 8.





