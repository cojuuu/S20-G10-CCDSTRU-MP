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
**Interpret:** F is the difference of M to the union of R and B<br>
**Decode:**<br>


**over <-> (|F| = 3 ∨ val >= 20 ∨ start ∧ (|R| > 0 ∧ |B| = 0 ∨ |R| = 0 ∧ |B| > 0))**<br>
**Interpret:** Over IF AND ONLY IF the cardinality of F is equal to 3 OR val is more than or equal to 20 OR NOT start AND (the cardinality of R is greater than 0 AND the cardinality of B is equal to 0 OR the cardinality of R is equal to 0 AND the cardinality of B is greater than 0)<br>
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
**Interpret:** *go* only if R is equal to the difference of R and *pos*<br>
**Decode:**<br>


**¬*go* -> (B = B - {*pos*})**<br>
**Interpret:** don't *go* only if B is equal to the difference of B and *pos*<br>
**Decode:**<br>

**S = S - {*pos*}**<br>
**Interpret:** S is equal to the difference of S and *pos*<br>
**Decode:**<br>


**T = T - {*pos*}**<br>
**Interpret:** T is equal to the difference of T and *pos*<br>
**Decode:**<br>

#### Replace(*pos* ∈ M)

**found = false**<br>
**Interpret:** Initialize found to false<br>
**Decode:** found starts as false before checking *pos*<br><br>

**(go ∧ *pos* ∈ B) -> (B = B - {*pos*} ∧ found = true)**<br>
**Interpret:** If it is Red’s turn and *pos* is in Blue, remove *pos* from B and set found true<br>
**Decode:** Red captures Blue’s piece at *pos* and found becomes true<br><br>

**(go ∧ *pos* ∈ R) -> found = true**<br>
**Interpret:** If it is Red’s turn and *pos* is already in R, set found true<br>
**Decode:** Red selected an already-Red position at *pos* and found becomes true<br><br>

**(go ∧ *pos* ∉ R) -> (R = R ∪ {*pos*})**<br>
**Interpret:** If it is Red’s turn and *pos* is not in R, add *pos* to R<br>
**Decode:** Red claims or places on *pos*<br><br>

**(¬go ∧ *pos* ∈ R) -> (R = R - {*pos*} ∧ found = true)**<br>
**Interpret:** If it is Blue’s turn and *pos* is in Red, remove *pos* from R and set found true<br>
**Decode:** Blue captures Red’s piece at *pos* and found becomes true<br><br>

**(¬go ∧ *pos* ∈ B) -> found = true**<br>
**Interpret:** If it is Blue’s turn and *pos* is already in B, set found true<br>
**Decode:** Blue selected an already-Blue position at *pos* and found becomes true<br><br>

**(¬go ∧ *pos* ∉ B) -> (B = B ∪ {*pos*})**<br>
**Interpret:** If it is Blue’s turn and *pos* is not in B, add *pos* to B<br>
**Decode:** Blue claims or places on *pos*<br><br>

**(found ∧ *pos* ∉ S) -> (S = S ∪ {*pos*} ∧ found = false)**<br>
**Interpret:** If found is true and *pos* is not in S, add *pos* to S and reset found to false<br>
**Decode:** First-time marking: *pos* becomes part of S and found is cleared<br><br>

**(found ∧ *pos* ∈ S ∧ *pos* ∉ T) -> (T = T ∪ {*pos*} ∧ Expand(*pos*))**<br>
**Interpret:** If found is true and *pos* is already in S but not in T, add *pos* to T then expand<br>
**Decode:** Second-stage trigger: *pos* becomes part of T and causes Expand(*pos*)<br>

#### Expand(*pos* ∈ M)

#### Update(*pos* ∈ M)

#### NextPlayerMove(*pos* ∈ M)

#### GameOver()

***result* ∈ {"R wins", "B wins", "draw"}**<br>

**(over ∧ |R| > |B|) -> result = "R wins"**<br>
**Interpret:** If the game is over and the cardinality of R is greater than the cardinality of B, then the result is "R wins"<br>
**Decode:** R wins if they have more elements than B<br>

**(over ∧ |R| > |B|) -> result = "R wins"**<br>
**Interpret:** If the game is over and the cardinality of R is less than the cardinality of B, then the result is "B wins"<br>
**Decode:** B wins if they have more elements than R<br>

**(over ∧ |R| = |B|) -> result = "draw"**<br>
**Interpret:** If the game is over and the cardinality of R is equal to the cardinality of B, then the result is "draw"<br>
**Decode:** If R and B have the same number of elements, then it is a draw<br>
