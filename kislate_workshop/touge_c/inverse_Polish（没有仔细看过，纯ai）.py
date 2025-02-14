def evaluate_rpn(expression):
    stack = []
    operators = {
        '+': lambda a, b: a + b,
        '-': lambda a, b: b - a,
        '*': lambda a, b: a * b,
        '/': lambda a, b: int(b / a)  # 使用 int() 来确保结果是整数
    }

    tokens = expression.split()
    for token in tokens:
        if token in operators:
            num1 = stack.pop()
            num2 = stack.pop()
            result = operators[token](num1, num2)
            stack.append(result)
        else:
            stack.append(int(token))

    return stack[0]

if __name__ == "__main__":
    expression = input().strip()
    result = evaluate_rpn(expression)
    print(result)