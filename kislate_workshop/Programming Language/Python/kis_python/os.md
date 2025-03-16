在 Python 中，`os` 是一个标准库模块，提供了一些与操作系统交互的功能。它允许你执行操作系统相关的任务，如文件和目录操作、环境变量访问、进程管理等。

以下是一些常用的 `os` 模块功能：

1. **文件和目录操作**：
   - `os.listdir(path)`：列出指定目录中的文件和子目录。
   - `os.mkdir(path)`：创建一个新目录。
   - `os.makedirs(path)`：递归地创建目录。
   - `os.remove(path)`：删除指定文件。
   - `os.rmdir(path)`：删除指定目录。
   - `os.rename(src, dst)`：重命名文件或目录。

2. **路径操作**：
   - `os.path.join(path, *paths)`：将多个路径组合成一个路径。
   - `os.path.exists(path)`：检查路径是否存在。
   - `os.path.isfile(path)`：检查路径是否是文件。
   - `os.path.isdir(path)`：检查路径是否是目录。
   - `os.path.abspath(path)`：返回路径的绝对路径。

3. **环境变量**：
   - `os.getenv(key, default=None)`：获取环境变量的值。
   - `os.environ`：一个包含所有环境变量的字典。

4. **进程管理**：
   - `os.system(command)`：在子终端中执行系统命令。
   - `os.getpid()`：获取当前进程的进程ID。
   - `os.getppid()`：获取父进程的进程ID。

以下是一个示例，展示了如何使用 `os` 模块的一些功能：

```python
import os

# 获取当前工作目录
current_directory = os.getcwd()
print("当前工作目录:", current_directory)

# 列出当前目录中的文件和子目录
files_and_dirs = os.listdir(current_directory)
print("当前目录中的文件和子目录:", files_and_dirs)

# 创建一个新目录
new_directory = os.path.join(current_directory, "new_folder")
os.mkdir(new_directory)
print("创建了新目录:", new_directory)

# 检查路径是否存在
if os.path.exists(new_directory):
    print("路径存在:", new_directory)

# 删除新创建的目录
os.rmdir(new_directory)
print("删除了目录:", new_directory)
```

在你的代码中，如果需要使用 `os` 模块，可以通过 `import os` 导入它。然后，你可以使用 `os` 模块提供的各种功能来执行操作系统相关的任务。