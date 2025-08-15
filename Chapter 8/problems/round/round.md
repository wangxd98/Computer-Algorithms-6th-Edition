# 表格数据取整

### ★ 问题描述

给定一个 $p$ 行 $q$ 列的实数表格 $A=\left\{a_{i j}\right\}$ ，其第 $i$ 行和第 $j$ 列的和分别为 $r_i$ 和 $c_j $。 

表格数据取整问题要求将所给的实数表格 $A$ 变换为一个相应的整数表格 $B=\left\{b_{i j}\right\}$, 使得
(1)  $b_{i j}=\operatorname{round}\left(a_{i j}\right)$.
(2)  $\displaystyle\sum_{j=1}^q b_{i j}=\operatorname{round}\left(r_i\right), \sum_{i=1}^p b_{i j}=\operatorname{round}\left(c_j\right)$.

式中, $\operatorname{round}(x)$ 是对实数 $x$ 的取整运算, 可以是下取整 $\lfloor x \rfloor$的值，也可以是上取整 $\lceil x\rceil$的值 。

例如，对于下面的 3 行3 列的实数表格 $A$ ，可以有多种数据取整方案。
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
\hline 3 & 7  & 7  & 17 \\
\hline 9  & 2  & 1 &  12 \\
\hline 4  & 1  & 6  & 11\\
\hline 16  & 10  & 14 & \\
\hline 
\end{array}
$$
数据取整方案2：
$$
\begin{array}{|c|c|c|c|c|}
\hline 3 & 7  &8  & 18 \\
\hline 10  & 2  & 0 &  12 \\
\hline 4  & 1  & 6  & 11\\
\hline 17  & 10  & 14 & \\
\hline 
\end{array}
$$
数据取整方案3：
$$
\begin{array}{|c|c|c|c|c|}
\hline 3 & 7  &8  & 18 \\
\hline 10  & 2  & 1 &  13 \\
\hline 4  & 2  & 6  & 12\\
\hline 17  & 11  & 15 & \\
\hline 
\end{array}
$$
设取整后表格中数据之和为 $S=\displaystyle\sum_{i=1}^p\sum_{j=1}^q b_{i j}$，则对于方案1，2和3，其 $S$ 值分别为，$40,41 $和 $43$。

表格数据取整问题要求对于给定的实数表格，找出其数据取整方案，使得其 $S$ 值达到最大。

### ★ 算法设计

对于给定的实数表格 $A=\left\{a_{i j}\right\}$ ，其第 $i$ 行和第 $j$ 列的和分别为 $r_i$ 和 $c_j $。 

定义对实数 $x$ 的取整运算为 $\operatorname{round}(x)$ , 可取 $\lfloor x \rfloor$的值，也可取 $\lceil x\rceil$的值 。
将 $A$ 变换为一个相应的整数表格 $B=\left\{b_{i j}\right\}$, 使得
(1)  $b_{i j}=\operatorname{round}\left(a_{i j}\right)$.
(2)  $\displaystyle\sum_{j=1}^q b_{i j}=\operatorname{round}\left(r_i\right), \sum_{i=1}^p b_{i j}=\operatorname{round}\left(c_j\right)$.
(3) $S=\displaystyle\sum_{i=1}^p\sum_{j=1}^q b_{i j}$ 的值达到最大。

### ★ 数据输入

输入文件名为roun.in。
每个文件有多组测试数据。每组测试数据的第一行有2个正整数 $p,q$，表示给定的的实数表格 $A=\left\{a_{i j}\right\}$有 $p$ 行 $q$ 列。从第2行起，共 $p$ 行，每行有 $q$ 个实数，表示实数表格中一行的实数。
其中数据满足：$1\leq p,q\leq 505$，$1\leq a_{i j}\leq 125$。

### ★ 结果输出

输出文件名为roun.out。

每行依次输出每组测试数据所对应满足取整要求的整数表格的最大 $S$ 值。

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
22
43
```
