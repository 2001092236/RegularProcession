# RegularProcession
Problem: find the longest suffix of the word w which belongs to the language given by the regular expression r.
The solution is as follows:
1) At each moment of time we have a stack of regulars. Initially it is empty.
2) Handle inverse Polish notation one character at a time from the end to the beginning, maintaining the stack.
3) If the current symbol is an operation, we take the right number of arguments from the stack, 
    execute it and put the result back on the stack.
   If it is a symbol, we just put it on the stack.
4) Regular expression correctness: there were always correct symbols in the input, there were always enough arguments for operations, 
    at the end, stack size = 1.

## Now the algorithm:
1) Each "regular" from the previous description is essentially a dynamic. It uses a pair of indices in a word (left and right)
    says: whether word[left ... right] lies in the language given by the current regular expression.

2) **Base**: For a 1-character regular (1, a, b, c) - such a dynamic is trivially constructed.
3) **Transition**: Let the current operation be * (cline star), the current regular is r.
    Then we need to check for each pair of indexes whether word[left ... right] is perceived by regular r*.
   This can be easily done through dynamics: word[left ... right] - is perceived if 
   1) it was taken by the old regular r
   2) it is empty
   3) word[left ... right] = word[left ... mid] word[mid + 1 ... right], where word[left ... mid] is perceived r* and word[mid + 1 ... right] is perceived r*.
   4) here left - 1 <= mid <= right. If L = R + 1 then we assume that the word is empty.
4) **Transition for oration +:**
      1) Obviously, word[left ... right] is taken as a sum, <=> at least one of the summands. I.e. you just have to make or to each cell of the dynamics.
5) **Transition for operation . :**
    1) Similar with * but only when word[left ... right] is split into word[left ... mid] word[mid + 1 ... right], where word[left ... mid], then you need the left part to be taken by the left regular and the right part by the right regular.


Then the answer to the problem can be found by simply looping over the word suffix and checking that it is perceived by the whole regular.
