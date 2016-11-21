- [Problem](https://leetcode.com/problems/reverse-string/)

# What questions to ask before starting to code ?
- None, on my side.

# Idea
- loop with i=0, size(string)/2
  - swap s[i] with s[size - 1 - i]
- Don't need to worry about size being even or odd, in the odd case the middle caracter is ignored, because size/2 truncates to an even number always.
