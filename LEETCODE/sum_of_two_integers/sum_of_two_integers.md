- [Problem](https://leetcode.com/problems/sum-of-two-integers/)

# What questions to ask before starting to code ?
- how large are the numbers, i.e. in how many bits do they fit ?
- can there be negative numbers too ?


# Idea
- convert number either to a bitset or access their bits directly with (AND operation and 2^i for a position i).
- the sum of the bits at position:
```cpp
n[i] = a[i] ^ b[i] ^ carry;
```
and the carry:
```cpp
carry = 1, if either (a[i] AND b[i]) OR ((a[i] OR b[i]) && carry).
```
