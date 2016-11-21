- [Problem](https://leetcode.com/problems/island-perimeter/)

# What questions to ask before starting to code ?
- is the grid rectangular ?
- is it guaranteed to have only one island ?
- how large is the grid ?

# Idea
- start with perimeter = 0.
- iterate with two for loops over the grid.
- if you encounter a '1' cell, check:
  - is the neighbour a '0' cell OR is the neighbour outside the grid?
  - if YES then perimeter++
- output perimeter.
