- [Problem](https://leetcode.com/problems/find-the-difference/)

# What questions to ask before starting to code ?
- Is it guaranteed that a character is always introduced ?
- are the letters guaranteed to be small letters ?
- are there only [a-z] characters ?

# Idea
- keep a hashmap with the letter frequencies of the string s. Iterate through string t and increment the frequencies of it too. The introduced letter is the one with odd frequency.
