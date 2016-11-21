- [Problem](https://leetcode.com/problems/fizz-buzz/)

# What questions to ask before starting to code ?
- how large are the numbers ?
- will you get negative numbers ?

# Idea
- loop through i=1,n:
  - is i >= 15 and i % 15 == 0, then FizzBuzz
  - is i >= 3  and i % 3  == 0, then Fizz
  - is i >= 5  and i % 5  == 0, then Buzz
  - else i

- __Important__ to check in this order, otherwise e.g. a multiple of 15 might be labeled as Fizz, if mod 3 before mod 15.
