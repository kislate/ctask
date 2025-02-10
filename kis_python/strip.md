在 Python 中，`strip()` 是一个字符串方法，用于移除字符串开头和结尾的空白字符（包括空格、制表符、换行符等）。它不改变字符串中间的空白字符。

### 示例
```python
# 示例字符串
s = "   Hello, World!   \n"

# 使用 strip() 移除开头和结尾的空白字符
stripped_s = s.strip()

print(f"原始字符串: '{s}'")
print(f"移除空白后的字符串: '{stripped_s}'")
```

### 输出
```
原始字符串: '   Hello, World!   
'
移除空白后的字符串: 'Hello, World!'
```

### 其他相关方法
- `lstrip()`: 只移除开头的空白字符。
- `rstrip()`: 只移除结尾的空白字符。
s
### 示例
```python
s = "   Hello, World!   \n"

# 只移除开头的空白字符
lstripped_s = s.lstrip()

# 只移除结尾的空白字符
rstripped_s = s.rstrip()

print(f"只移除开头的空白字符: '{lstripped_s}'")
print(f"只移除结尾的空白字符: '{rstripped_s}'")
```

### 输出
```
只移除开头的空白字符: 'Hello, World!   
'
只移除结尾的空白字符: '   Hello, World!'
```

希望这些信息对你有所帮助！