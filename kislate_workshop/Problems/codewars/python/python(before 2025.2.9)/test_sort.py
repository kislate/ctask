from solution import order # 这里你只需要创建一个solution.py文件，
# 然后将你的函数放在里面即可，这样就不会报错了

import codewars_test as test #这个模块在codewars上

@test.describe("Your order, please")
def fixed_tests():
    @test.it('Basic Tests')
    def it1():
        test.assert_equals(order("is2 Thi1s T4est 3a"), "Thi1s is2 3a T4est")
        test.assert_equals(order("4of Fo1r pe6ople g3ood th5e the2"), "Fo1r the2 g3ood 4of th5e pe6ople")
        test.assert_equals(order("d4o dru7nken sh2all w5ith s8ailor wha1t 3we a6"), "wha1t sh2all 3we d4o w5ith a6 dru7nken s8ailor")
        test.assert_equals(order(""), "")
        test.assert_equals(order("3 6 4 2 8 7 5 1 9"), "1 2 3 4 5 6 7 8 9")


@test.describe("Random tests")
def random_tests():
    WORDS = "a able about after all an and as ask at bad be big but by call case child come company day different do early eye fact feel few find first for from get give go good government great group hand have he her high his I important in into it know large last leave life little long look make man my new next not number of old on one or other over own part person place point problem public right same say see seem she small take tell that the their there they thing think this time to try up use want way week will with woman work work world would year you young".split()
    
    from random import randint, sample, shuffle
    
    for _ in range(50):
        arr = sample(WORDS, randint(0, 9))
        arr2 = []
        for i, w in enumerate(arr):
            letters = list(w)# python中字符串是不可变的，所以要先转换为列表
            letters.insert(randint(0, len(w)), str(i+1))
            arr2.append("".join(letters))
        expected = " ".join(arr2)
        shuffle(arr2)# 打乱列表
        test_str = " ".join(arr2)
        
        @test.it(f'Testing: "{test_str}"')
        def single_test():
            test.assert_equals(order(test_str), expected)

'''
函数是 Python 标准库 random 模块中的一个函数。它用于从指定的序列中随机抽取指定数量的元素，
返回一个新的列表。sample 函数不会修改原始序列。

语法：

参数：

population:可以是列表、元组、字符串等任何序列。
k:要抽取的元素数量。
'''