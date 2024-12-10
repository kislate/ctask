/*
任务描述
本关任务：编程实现
（1）用一个单向链表接收一个长字符串，且每个节点接收一个字符，遍历输出链表中的所有字符，并将字符串无冗余地存放到一个动态存储分配的的字符数组中，并且输出该字符串。（本题暂不考虑空字符串情况）(结尾以回车结束)
（2）再输入一个字符，如果该字符已在链表中，则删除该结点，否则在输入字符和结点的数据域字符差值最小的结点后面插入包含该字符的结点，输出最后的字符串。

要求：采用模块化设计方法，将创建链表、遍历链表、删除结点、插入结点等功能用函数实现。

测试说明
平台会对你编写的代码进行测试，若是与预期输出相同，则算通关。

测试输入：
qwertyuiopasdfghjkl
i
预期输出：
q w e r t y u i o p a s d f g h j k l
qwertyuiopasdfghjkl
qwertyuopasdfghjkl

测试输入：
qwertyuiopasdfghjkl
q
预期输出：
q w e r t y u i o p a s d f g h j k l
qwertyuiopasdfghjkl
wertyuiopasdfghjkl

测试输入：
qwer1234?@%
5
预期输出：
q w e r 1 2 3 4 ? @ %
qwer1234?@%
qwer12345?@%

开始你的任务吧，祝你成功！*/
