# Something about point

- `int x,*const p;`是错的，因为const类型的指针要在声明的时候同时初始化
- `const int x=3,*p;`是对的，因为这里的const只对x管用，对*p不管用。
- `typedef char * string;`可以使得`string c,d`中的两个变量都声明为char类型的指针
- 但是如果你这样--`#define STRING char *`会有`STRING a,b`这里会解释为`char *a,b`这样的话就只有a会是指针变量
- 