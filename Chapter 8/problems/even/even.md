# 表格偶数取整

### ★ 问题描述

给定一个 $p$ 行 $q$ 列的实数表格 $A=\left\{a_{i j}\right\}$ ，其第 $i$ 行和第 $j$ 列的和分别为 $r_i$ 和 $c_j $。 

表格偶数取整问题要求将所给的实数表格 $A$ 变换为一个相应的偶数表格 $B=\left\{b_{i j}\right\}$, 使得
(1)  $b_{i j}=\operatorname{round}\left(a_{i j}\right)$.
(2)  $\displaystyle\sum_{j=1}^q b_{i j}=\operatorname{round}\left(r_i\right), \sum_{i=1}^p b_{i j}=\operatorname{round}\left(c_j\right)$.

式中, $\operatorname{round}(x)$ 是对实数 $x$ 的偶数取整运算, 定义如下：

设对于任意整数 $z$，奇偶性函数 $\operatorname{odd}(z)$ 定义为，当整数 $z$ 为奇数时取值 1，当整数 $z$ 为偶数时取值 0。
设对于任意正实数数 $x$，偶数取整运算 $\operatorname{round}(x)$ 定义为不超过 $x$ 的最大偶数，或不小于 $x$ 的最小偶数。
也就是说， $\operatorname{round}(x)$ 可以取值 $\lfloor x \rfloor-\operatorname{odd}(\lfloor x \rfloor)$，或 $\lceil x\rceil+\operatorname{odd}(\lceil x\rceil)$。

例如，对于下面的 3 行3 列的实数表格 $A$ ，可以有多种偶数取整方案。
$$
\begin{array}{|c|c|c|c|c|}
\hline 3.1 & 6.8 & 7.3 & 17.2 \\
\hline 9.6 & 2.4 & 0.7 & 12.7 \\
\hline 3.6 & 1.2 & 6.5 & 11.3 \\
\hline 16.3 & 10.4 & 14.5 & \\
\hline
\end{array}
$$
数据取整方案1：
$$
\begin{array}{|c|c|c|c|c|}
\hline 4  & 6 & 8  &18 \\
\hline 10 & 4 & 0  &14 \\
\hline 4  &0  &8  &12\\
\hline 18 & 10  &16 & \\
\hline 
\end{array}
$$
数据取整方案2：
$$
\begin{array}{|c|c|c|c|c|}
\hline 4  & 6 & 8  &18 \\
\hline 10 & 4 & 0  &14 \\
\hline 4  &0  &6  &10\\
\hline 18 & 10  &14 & \\
\hline 
\end{array}
$$
数据取整方案3：
$$
\begin{array}{|c|c|c|c|c|}
\hline 4  & 6 & 6  &16 \\
\hline 8 & 4 & 0  &12 \\
\hline 4  &0  &8  &12\\
\hline 16 & 10  &14 & \\
\hline 
\end{array}
$$
设取整后表格中数据之和为 $S=\displaystyle\sum_{i=1}^p\sum_{j=1}^q b_{i j}$，则对于方案1，2 和 3，其 $S$ 值分别为，$44,42 $和 $40$。

表格偶数取整问题要求对于给定的实数表格，找出其偶数取整方案，使得其 $S$ 值达到最小。

### ★ 算法设计

对于给定的实数表格 $A=\left\{a_{i j}\right\}$ ，其第 $i$ 行和第 $j$ 列的和分别为 $r_i$ 和 $c_j $。 

对于任意正实数数 $x$，偶数取整运算 $\operatorname{round}(x)$ 定义为不超过 $x$ 的最大偶数，或不小于 $x$ 的最小偶数。

将 $A$ 变换为一个相应的偶数表格 $B=\left\{b_{i j}\right\}$, 使得
(1)  $b_{i j}=\operatorname{round}\left(a_{i j}\right)$.
(2)  $\displaystyle\sum_{j=1}^q b_{i j}=\operatorname{round}\left(r_i\right), \sum_{i=1}^p b_{i j}=\operatorname{round}\left(c_j\right)$.
(3) $S=\displaystyle\sum_{i=1}^p\sum_{j=1}^q b_{i j}$ 的值达到最小。

### ★ 数据输入

输入文件名为even.in。
每个文件有多组测试数据。每组测试数据的第一行有2个正整数 $p,q$，表示给定的的实数表格 $A=\left\{a_{i j}\right\}$有 $p$ 行 $q$ 列。从第2行起，共 $p$ 行，每行有 $q$ 个实数，表示实数表格中一行的实数。
其中数据满足：$1\leq p,q\leq 505$，$1\leq a_{i j}\leq 125$。

### ★ 结果输出

输出文件名为even.out。

每行依次输出每组测试数据所对应满足取整要求的偶数表格的最小 $S$ 值。

**输入示例**  

```
2 2
3.1 6.8
9.6 2.4
3 3
3.1 6.8 7.3
9.6 2.4 0.7
3.6 1.2 6.5
```

**输出示例**  

```
20
40
```
