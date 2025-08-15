# 一元模线性方程组

### ★ 问题描述

设 $a_1, a_2, \ldots, a_k$ 和 $m_1, m_2 \cdots, m_k$ 是给定的整数。求以下一元模线性方程组的解：

$$
\left.\left\{
\begin{aligned}
x&\equiv a_1\pmod {m_1}\\
x&\equiv a_2\pmod {m_2}\\
\cdots\\
x&\equiv a_k\pmod {m_k}
\end{aligned}
\right.\right.
$$

### ★ 算法设计

对于给定的整数 $a_1, a_2, \ldots, a_k$ 和 $m_1, m_2 \cdots, m_k$ ，设计一个算法，计算出给定模线性方程组的整数解 $x$。

### ★ 数据输入

输入文件名为ecrt.in。

有多组测试数据，每行一组测试数据。第1行是正整数 $k$。接着是  $k$  个整数对 $a_i$  和 $m_i$ 。

数据满足  $ k\leq 10, m_1, m_2, \ldots, m_k<50$。

### ★ 结果输出

输出文件名为ecrt.out。

依次输出相应模线性方程组的解 。方程组无解时无输出。

**输入示例**  

```
3 2 3 4 5 3 7
3 0 6 4 8 3 9
```

**输出示例**  

```
59
12
```
