- [Problem]()

# What questions to ask before starting to code ?
- can the list of cookies or children be empty ?
- are the numbers in g and s already sorted ?
- how large can the two arrays be ?

# Idea
- sort both arrays in increasing order.
- start from the largest cookie, and from the greediest child.
- if the current cookie fits the child's greediness, then give him the cookie and pick the next cookie and child.
- otherwise, go to the next child, but keep the current cookie.
