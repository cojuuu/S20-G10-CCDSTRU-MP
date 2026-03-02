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
**Decode:** found starts as false before checking *pos*<br>

**(go ∧ *pos* ∈ B) -> (B = B - {*pos*} ∧ found = true)**<br>
**Interpret:** If it is Red’s turn and *pos* is in Blue, remove *pos* from B and set found true<br>
**Decode:** Red captures Blue’s piece at *pos* and found becomes true<br>

**(go ∧ *pos* ∈ R) -> found = true**<br>
**Interpret:** If it is Red’s turn and *pos* is already in R, set found true<br>
**Decode:** Red selected an already-Red position at *pos* and found becomes true<br>

**(go ∧ *pos* ∉ R) -> (R = R ∪ {*pos*})**<br>
**Interpret:** If it is Red’s turn and *pos* is not in R, add *pos* to R<br>
**Decode:** Red claims or places on *pos*<br>

**(¬go ∧ *pos* ∈ R) -> (R = R - {*pos*} ∧ found = true)**<br>
**Interpret:** If it is Blue’s turn and *pos* is in Red, remove *pos* from R and set found true<br>
**Decode:** Blue captures Red’s piece at *pos* and found becomes true<br>

**(¬go ∧ *pos* ∈ B) -> found = true**<br>
**Interpret:** If it is Blue’s turn and *pos* is already in B, set found true<br>
**Decode:** Blue selected an already-Blue position at *pos* and found becomes true<br>

**(¬go ∧ *pos* ∉ B) -> (B = B ∪ {*pos*})**<br>
**Interpret:** If it is Blue’s turn and *pos* is not in B, add *pos* to B<br>
**Decode:** Blue claims or places on *pos*<br>

**(found ∧ *pos* ∉ S) -> (S = S ∪ {*pos*} ∧ found = false)**<br>
**Interpret:** If found is true and *pos* is not in S, add *pos* to S and reset found to false<br>
**Decode:** First-time marking: *pos* becomes part of S and found is cleared<br>

**(found ∧ *pos* ∈ S ∧ *pos* ∉ T) -> (T = T ∪ {*pos*} ∧ Expand(*pos*))**<br>
**Interpret:** If found is true and *pos* is already in S but not in T, add *pos* to T then expand<br>
**Decode:** Second-stage trigger: *pos* becomes part of T and causes Expand(*pos*)<br>

#### Expand(*pos* ∈ M)

**(a, b) = *pos***<br>
**Interpret:** Let a and b be the coordinates of *pos*<br>
**Decode:** If *pos*=(2,3) then a=2 and b=3<br>

**u, d, k, r ∈ M**<br>
**Interpret:** u, d, k, r are positions in M and are neighbors of *pos*<br>
**Decode:** These are the up, down, left, right positions if they stay inside the board<br>

**u = (a - 1, b)**<br>
**Interpret:** u is the position above *pos*<br>
**Decode:** If *pos*=(2,3) then u=(1,3)<br>

**d = (a + 1, b)**<br>
**Interpret:** d is the position below *pos*<br>
**Decode:** If *pos*=(2,3) then d=(3,3)<br>

**k = (a, b - 1)**<br>
**Interpret:** k is the position to the left of *pos*<br>
**Decode:** If *pos*=(2,3) then k=(2,2)<br>

**r = (a, b + 1)**<br>
**Interpret:** r is the position to the right of *pos*<br>
**Decode:** If *pos*=(2,3) then r=(2,4)<br>

**Remove(*pos*)**<br>
**Interpret:** Remove the piece at *pos* and also remove it from S and T<br>
**Decode:** *pos* is deleted from the current player’s set and from S and T<br>

**(go) -> Replace(u)**<br>
**Interpret:** If it is Red’s turn, replace the up neighbor<br>
**Decode:** Red expands upward<br>

**(¬go) -> Replace(d)**<br>
**Interpret:** If it is Blue’s turn, replace the down neighbor<br>
**Decode:** Blue expands downward<br>

**Replace(k)**<br>
**Interpret:** Always replace the left neighbor<br>
**Decode:** Expansion always affects the left side<br>

**Replace(r)**<br>
**Interpret:** Always replace the right neighbor<br>
**Decode:** Expansion always affects the right side<br>

#### Update(*pos* ∈ M)

**good = false**<br>
**Interpret:** Set good to false at the start of Update<br>
**Decode:** Assume the move is not yet good or valid<br>

**(*pos* ∉ S) -> (S = S ∪ {*pos*} ∧ good = ¬good)**<br>
**Interpret:** If *pos* is not in S, add it to S and flip good<br>
**Decode:** If *pos* is new to S, it becomes marked and good becomes true<br>

**(¬good ∧ *pos* ∈ S ∧ *pos* ∉ T) -> (T = T ∪ {*pos*} ∧ Expand(*pos*))**<br>
**Interpret:** If good is still false and *pos* is in S but not in T, add it to T and expand<br>
**Decode:** If *pos* was already in S, trigger expansion and mark it in T<br>

#### NextPlayerMove(*pos* ∈ M)

**(¬over ∧ start ∧ go) -> (R = R ∪ {*pos*} ∧ S = S ∪ {*pos*} ∧ good = true)**<br>
**Interpret:** If not over, in start phase, and it is Red’s turn, add *pos* to R and S and set good true<br>
**Decode:** Red places the first piece at *pos* and it is immediately marked in S<br>

**(¬over ∧ start ∧ ¬go) -> (B = B ∪ {*pos*} ∧ S = S ∪ {*pos*} ∧ good = true)**<br>
**Interpret:** If not over, in start phase, and it is Blue’s turn, add *pos* to B and S and set good true<br>
**Decode:** Blue places the first piece at *pos* and it is immediately marked in S<br>

**(¬over ∧ ¬start ∧ (go ∧ *pos* ∈ R ∨ ¬go ∧ *pos* ∈ B)) -> (Update(*pos*) ∧ good = true)**<br>
**Interpret:** After start phase, if the current player chooses their own piece at *pos*, run Update(*pos*) and set good true<br>
**Decode:** You can only select your own cell at *pos* and doing so triggers Update<br>

**(start ∧ |R| = 1 ∧ |B| = 1) -> start = false**<br>
**Interpret:** If both players have exactly one piece, end the start phase<br>
**Decode:** After both initial placements, start becomes false<br>

**(¬over ∧ good) -> (good = ¬good ∧ go = ¬go ∧ val = val + 1)**<br>
**Interpret:** If the move is good and game is not over, flip good back, switch turns, and increment val<br>
**Decode:** Successful move ends the turn and increases the move counter by 1<br>

#### GameOver()

***result* ∈ {"R wins", "B wins", "draw"}**<br>
**Interpret:** result must be one of the three possible outputs<br>
**Decode:** Only these 3 strings are allowed<br>

**(over ∧ |R| > |B|) -> result = "R wins"**<br>
**Interpret:** If the game is over and the cardinality of R is greater than the cardinality of B, then the result is "R wins"<br>
**Decode:** R wins if they have more elements than B<br>

**(over ∧ |R| > |B|) -> result = "R wins"**<br>
**Interpret:** If the game is over and the cardinality of R is less than the cardinality of B, then the result is "B wins"<br>
**Decode:** B wins if they have more elements than R<br>

**(over ∧ |R| = |B|) -> result = "draw"**<br>
**Interpret:** If the game is over and the cardinality of R is equal to the cardinality of B, then the result is "draw"<br>
**Decode:** If R and B have the same number of elements, then it is a draw<br>
