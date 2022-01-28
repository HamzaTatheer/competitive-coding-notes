# competitive coding notes
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
