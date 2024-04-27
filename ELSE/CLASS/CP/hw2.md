### 考虑下面的CFG G[S]：S → SS+ | SS* | number 

#### （1）给出串34+2*的一个最左推导和一个最右推导； 

- 最左推导：$S\Rightarrow SS^* \Rightarrow SS+S^*\Rightarrow 3S+S^*\Rightarrow 34+S^*\Rightarrow 34+2^*$

- 最右推导：$S\Rightarrow SS^*\Rightarrow S2^* \Rightarrow SS+2^*\Rightarrow 3S+2^*\Rightarrow 34+2^*$

#### （2）画出与上述推导过程相对应的语法树； 

![Screenshot_20231026_085057_com.newskyer.draw](C:\Users\wxy43\Downloads/Screenshot_20231026_085057_com.newskyer.draw.jpg)

#### （3）该文法表示什么语言；

#### 		  **后缀算术表达式**

#### （4）**分析**该文法有无二义性。 

无二义性：

对于一个后缀式来说，所有的运算符都固定在算数后，所以在每一步的推导过程中只能推导算符和数字中的一个，是唯一的，因此每一个式子的产生的固定的，故该文法无二义性。

---

### 写一个CFG，产生语言：{ 能被5整除的十进制整数}，要求：不考虑正负号，数字不以0开头。

$$
G[S]:S \rightarrow first \; nums \; 0 \; | \; first \; nums \;5 \; |\; 5 \\ first\rightarrow 1|2|3|4|5|6|7|8|9\\
nums\rightarrow nums \; num\; | \epsilon \\
num\rightarrow 0|1|2|3|4|5|6|7|8|9
$$

---

### 把下面文法改写为无二义的：G[S]  S-> SS | aSb | ab   要求：分析该文法的二义性来源，并论述如何消除二义性。

对于串**ababab**可生成下面两个语法树

![Screenshot_20231026_091225_com.newskyer.draw](C:\Users\wxy43\Downloads/Screenshot_20231026_091225_com.newskyer.draw.jpg)

对于同一个串，存在两个不同的语法树即可证明该文法有二义性。

二义性来源于$S\rightarrow SS$，在这步推导中在从左右两边均可以生成子树。

消除二义性：
$$
G[S]: S \rightarrow ST | T \\
T \rightarrow aSb | ab
$$
