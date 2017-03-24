# Chapter 6 Solutions

## The Heavy Pill

We have **20** bottles, **19** of them with 1.0 gram pills and **one bottle** with 1.1 gram pills, and we can use the scale only once. <br>
This means we need to weigh at least **19** bottles at the same time, and do so such that we can identify each of the bottles. <br>
All but one of them contain 1.0 gram pills, so we could use this to identify them,  by putting:

- one pill from bottle one
- two pills from bottle two
...

Let's suppose the 1.1 gram pills are in bottle one. Then all the pills on the scale should weight: 1 * 1.1 + 2 * 1.0 + 3 * 1.0 + ... = 190,1
This is one case, but the 1.1 gram pills can be in any of the other bottles, and this would result in different sums, which tell us which bottle has those pills.


## Basketball

- Probability to win **Game 1**: p
- Probability to win **Game 2**: 
  - p(win first game) * p(win second game) * p(lose third game) + 
  - p(lose first game) * p(win second game) * p(win third game) + 
  - p(win first game) * p(lose second game) * p(win third game) + 
  - p(win first game) * p(win second game) * p(win third game) = 3 * p^2 * (1-p) + p^3

Game 1 is chosen if:
- p > 3 * p^2 * (1-p) + p^3
- p - 3 * p^2 * (1-p) + p^3 > 0
...

## Dominos

The invariant we will use is the following: a domino piece will cover **one black and one white** piece. The diagonally opposite corners are of same colors, so by removing them we will have 2 squares of same color deficit, which cannot be covered by the dominos.

## Ants on Triangle

From **all 2^n cases**, only **2** result in ants collision, i.e. when all ants go in the same direction, and there are two of them because the ants can go in clockwise or counter-clockwise direction.
So, the probability is: **(2^n - 2) / (2^n)**.

## Jugs of Water
Just play arround with the water.

## Blue-Eyes Island

This problem can be solved by starting from simple cases and by induction coming up with a general solution.
**TODO** write solution.

## The Apocalypse

One birth simulation in a family can be represented by a sequence: bbbbbg, where b = boy and g = girl. <br>
For each family, we need to find the expected length of such a sequence. <br>
Let's call G, the random variable that counts the number of girls. Then, by definition E[G] = 1, because every family has to have a girl. <br>
Let's call T, the length of the aforementioned sequence. Thus E[T] = 1/2 * 1 + 1/2 * (1 + E[T]). <br>
The first summand is the probability of getting a girl in the first birth, and thus the sequence has length 1. <br>
The second summand is the probability of not having a girl, and thus a boy, in the first birth, and so starting the birth count all over again, and counting 1 for the boy we have got. <br>
Finally, by algebraic manipulation, E[T] = 2, and thus E[Boys] = 2 - E[G] = 1. <br>
So, in the long term, the gender ratio is *1.0*.

## The Egg Drop Problem

**TODO:** write solution.

## 100 Lockers

- At the beginning all the lockers are open.
- Each locker number **L** can be written as: 1 * p_1^k_1 * p_2^k_2 * ...
- Thus, the locker will stay open if it has an **odd** number of factors.
- Observe that we regard 1 as a factor too, so the only numbers that have odd number of factors are **perfect squares**.
- How many perfect squares <= 100 ? well 1^2, 2^2, ..., 10^2 <= 100. There are 10 such perfect squares.

## Poison

Idea is to use the test stripes as ids for our bottles. Thus using a binary representation of the numbers. <br>
We have 1000 bottles and 10 stripes, so we could represent 2^10 bottles. <br>
- Put drops from bottles which have **i-th** bit on, on the **i-th** stripe.
- Wait for 7 days for the test results.
- The bottle id which bits are composed of the stripes that are positive, is the poisonous bottle.
