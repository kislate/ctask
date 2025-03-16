在 Python 中，函数和方法有一些关键区别：

1. **定义位置**：
    - **函数**：函数是通过 `def` 关键字定义的，并且通常在模块级别定义。它们可以独立存在，不依赖于任何对象。
    - **方法**：方法是定义在类中的函数。它们与类的实例相关联，并且通常操作类的实例数据。

2. **调用方式**：
    - **函数**：函数可以直接调用，不需要依赖于任何对象。例如，内置函数 `len()` 可以直接调用。
    - **方法**：方法必须通过类的实例来调用。例如，列表对象的 `append()` 方法必须通过列表实例来调用。

3. **第一个参数**：
    - **函数**：函数的参数列表不包含 `self`。
    - **方法**：方法的第一个参数通常是 `self`，它代表类的实例。通过 `self`，方法可以访问和修改实例的数据。

4. **__repr__ 方法**：
    - **定义**：`__repr__` 是一个特殊的方法，用于定义类的实例在使用 `repr()` 函数或在解释器中直接打印实例时的字符串表示。
    - **用途**：`__repr__` 方法的目的是提供一个“官方的”字符串表示，通常可以用来重新创建这个对象，或者至少提供足够的详细信息来识别这个对象。

以下是一个示例，展示了函数和方法的区别：

```python
# 定义一个函数
def my_function(x):
     return x + 1

# 定义一个类
class MyClass:
     def __init__(self, value):
          self.value = value
     
     # 定义一个方法
     def my_method(self):
          return self.value + 1
     
     # 定义 __repr__ 方法
     def __repr__(self):
          return f"MyClass(value={self.value})"

# 调用函数
result_function = my_function(10)
print(result_function)  # 输出: 11

# 创建类的实例
my_instance = MyClass(10)

'''
MyClass(10) 调用 MyClass 类的构造方法 __init__，并传递参数 10。
__init__ 方法接收参数 10，并将其赋值给实例的属性 value。
创建的实例被赋值给变量 my_instance，这样你就可以通过 my_instance 访问和操作这个实例。
'''

# 调用方法
result_method = my_instance.my_method()
print(result_method)  # 输出: 11

# 使用 __repr__ 方法
print(repr(my_instance))  # 输出: MyClass(value=10)
```

在这个示例中：
- `my_function` 是一个独立的函数，可以直接调用。
- `my_method` 是一个方法，必须通过类的实例 `my_instance` 来调用，并且它的第一个参数是 `self`，用于访问实例的数据。
- `__repr__` 方法提供了类实例的字符串表示，便于调试和日志记录。
    def my_method(self):
        return self.value1 + self.value2

# 创建类的实例，并传递两个参数 10 和 20 给构造方法
my_instance = MyClass(10, 20)

# 调用方法
result_method = my_instance.my_method()
print(result_method)  # 输出: 30
```

在这个示例中：
- `__init__(self, value1, value2)` 方法有三个参数：`self`、`value1` 和 `value2`。
- `self` 是类的实例，在创建实例时由 Python 自动传递。
- `value1` 和 `value2` 是你在创建实例时传递的参数，例如 `10` 和 `20`。
- `self.value1 = value1` 和 `self.value2 = value2` 将传入的参数赋值给实例的属性 `value1` 和 `value2`。

当你执行 `my_instance = MyClass(10, 20)` 时，实际调用的是 `MyClass.__init__(my_instance, 10, 20)`，其中 `my_instance` 是新创建的实例，`10` 和 `20` 是传递的参数。

这样，你就可以在类的实例中存储多个值，并在方法中使用这些值。