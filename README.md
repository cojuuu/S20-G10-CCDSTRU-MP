# CCDSTRU-MP

## Decoding of Specifications


### Applicable Sets

**C: {x ∈ Z+ | x < 4}**<br>
**Interpret:** Set C is a set of positive integers less than 4<br>
**Decode:** C: {1, 2, 3}<br>


**N: {x ∈ Z+ ∪ {0} | x <= 16}**<br>
**Interpret:** Set N is a set of positive integers less than or equal to 16, including 0<br>
**Decode:** N: {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}<br>


**M: C x C**<br>
**Interpret:** M is the Cartesian product of set C and set C<br>
**Decode:**<br>

| | M | |
| :---: | :---: | :---: |
| (1, 1) | (1, 2) | (1, 3) |
| (2, 1) | (2, 2) | (2, 3) |
| (3, 1) | (3, 2) | (3, 3) |


**V: {true, false}**<br>
**Interpret:** Set V is the set of truth values<br>

### System Variables

***good* ∈ V**<br>
**Interpret:** good is an element of B<br>
**Decode:** good = true, false<br>


***go* ∈ V**<br>
**Interpret:** go is an element of B<br>
**Decode:** go = true, false<br>


***start* ∈ V**<br>
**Interpret:** start is an element of B<br>
**Decode:** start = true, false<br>


***over* ∈ V**<br>
**Interpret:** start is an element of B<br>
**Decode:** start = true, false<br>


***found* ∈ V**<br>
**Interpret:** found is an element of B<br>
**Decode:** found = true, false<br>


***val* ∈ N**<br>
**Interpret:** val is an element of N<br>
**Decode:** val = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16<br>


**R,B,S,T,F ⊆ M**<br>
**Interpret:** R, B, S, T, F are subsets of M<br>
**Decode:**<br>
* R can be any value in set M<br>
* B can be any value in set M<br>
* S can be any value in set M<br>
* T can be any value in set M<br>
* F can be any value in set M<br>

### System Facts

**F = M − (R ∪ B)**<br>
**Interpret:**<br>
**Decode:**<br>


**over <-> (|F| = 3 ∨ val >= 20 ∨ start ∧ (|R| > 0 ∧ |B| = 0 ∨ |R| = 0 ∧ |B| > 0))**<br>
**Interpret:**<br>
**Decode:**<br>

### System Initialization

***good* = false**<br>
***go* = true**<br>
***start* = true**<br>
***found* = false**<br>
***val* = 0**<br>
**R = ∅**<br>
**B = ∅**<br>
**S = ∅**<br>
**T = ∅**<br>

### System States and Behavior

#### Remove(*pos* ∈ M)

***go* -> (R = R - {*pos*})**<br>
**Interpret:**<br>
**Decode:**<br>


**¬*go* -> (B = B - {*pos*})**<br>
**Interpret:**<br>
**Decode:**<br>

**S = S - {*pos*}**<br>
**Interpret:**<br>
**Decode:**<br>


**T = T - {*pos*}**<br>
**Interpret:**<br>
**Decode:**<br>
