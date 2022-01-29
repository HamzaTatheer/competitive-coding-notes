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

## Question 6. 

