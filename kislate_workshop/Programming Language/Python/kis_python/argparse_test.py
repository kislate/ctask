import argparse

# 创建 ArgumentParser 对象
parser = argparse.ArgumentParser(description="这是一个示例脚本，用于演示 argparse 的用法。")

# 添加参数
parser.add_argument("--input", type=str, required=True, help="输入文件的路径")
parser.add_argument("--output", type=str, default="output.txt", help="输出文件的路径（默认：output.txt）")
parser.add_argument("--verbose", action="store_true", help="是否启用详细输出模式")

# 解析命令行参数
args = parser.parse_args()

# 使用解析后的参数
print(f"输入文件: {args.input}")
print(f"输出文件: {args.output}")
if args.verbose:
    print("详细模式已启用！")