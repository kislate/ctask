# 一、union 简介

- `union` 是C语言中一种声明共用体的数据类型。
- `union`(共用体)在某种程度上类似`struct`(结构体)的一种数据结构，可以包含很多数据结构和变量。
- `union(共用体)`的特点：其内部的数据 共用一个内存首地址，共享同一段内存，以达到节省空间的目的。
`或许这里可以用来生成密码`

# 二、union的定义
### 1. 声明共用体类型
一般形式具体如下：
```C
union 共用体名
{
   //成员列表
   数据类型 成员名;
   数据类型 成员名;
   ....
}

```
##### 举例说明如下：
```C
union _MQ
{
	char data8[4];
	int  data32;
}; 

```

### 2. 定义共用体变量
一般形式具体如下：
```C
union _MQ
{
	char data8[4];
	int  data32;
}; 
//定义共用体变量
union _MQ mq;

```
合并简化形式具体如下：
```C
union _MQ
{
	char data8[4];
	int  data32;
}mq;

```

匿名结构体形式具体如下：
```C
union 
{
	char data8[4];
	int  data32;
}mq;

```

### 3. 使用 typedef 声明共用体类型，再定义共用体变量
一般形式如下
```C
typedef union MQ
{
	char data8[4];
	int  data32;
} _MQ;
//定义共用体变量，以下两种效果一样
union MQ mq;
_MQ mq;

```
匿名共用体形式具体如下：
```C
typedef union 
{
	char data8[4];
	int  data32;
} _MQ;
//定义共用体变量
_MQ mq;

```
### 三、union 使用方法

共用体变量成员----赋值(.)
初始化定义时----赋值
```C
typedef union 
{
	char data8[4];
	int  data32;
}_MQ; 

_MQ mq =
{
	.data32=0x12345678 
};

```
##### union(共用体)----*共用内存*
```C
#include <stdio.h>

typedef union 
{
  char data8[4];
  int  data32;
}_MQ; 

_MQ mq =
{
  .data32=0x12345678 //每个16进制可以直接看出来这个常量的2进制
};

int main(int argc, char *argv[])
{
	printf("data[0]=0x%x\n",mq.data8[0]);//0x78
	printf("data[1]=0x%x\n",mq.data8[1]);//0x56
	printf("data[2]=0x%x\n",mq.data8[2]);//0x34
	printf("data[3]=0x%x\n",mq.data8[3]);//0x12
	
	return 0;
}//我们可以知道16进制的两位数就刚好是一个char

```
### 大端模式和小端模式

| 模式       | data32     | data[0] | data[1] | data[2] | data[3] |
|------------|------------|---------|---------|---------|---------|
| 大端模式   | 0x12345678 | 0x12    | 0x34    | 0x56    | 0x78    |
| 小端模式   | 0x12345678 | 0x78    | 0x56    | 0x34    | 0x12    |


# 剩下的不想写了，自己去csdn查
