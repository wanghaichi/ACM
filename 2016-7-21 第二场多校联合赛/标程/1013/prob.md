# Memento Mori {2 seconds}{64 megabytes}

Professor Zhang has an $n \times m$ zero matrix(i.e. an matrix consisting of all 0s). Professor Zhang changes $k$ elements in the matrix into 1.

Given a permutation $p$ of $\{1,2,3,4\}$,  Professor Zhang wants to find the number of such submatrices that:

+ the number of 1s in the submatrix is exactly 4.
+ let the positions of the 1s in the submatrix be $(r_1,c_1),(r_2,c_2),(r_3,c_3),(r_4,c_4)$, then $r_1 < r_2 < r_3 < r_4$ and $(p_i - p_j) \cdot (c_i - c_j) > 0$ for all $1 \le i < j \le 4$.
+ no other submatrices inside the submatrix meets the above two conditions.

## Input

There are multiple test cases. The first line of input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains three integers $n$, $m$ and $k$ $(1 \le n,m,k \le 2000)$-- the size of the matrix and the number of 1s. The second line contains four integers $p_1,p_2,p_3,p_4$ denoting the permutation.

Each of the next $k$ lines contains two integers $r_i$ and $c_i$ $(1 \le r_i \le n, 1 \le c_i \le m)$ -- the position of the $i$-th 1. No two 1s will be in the same position.

## Output

For each test case, output an integer denoting answer.

## Sample Input

1
5 5 4
1 2 3 4
1 1
2 2
3 3
4 4

## Sample Output

1
