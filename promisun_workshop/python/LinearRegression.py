
#zby和我演都不带演的题目，嘻嘻
#能看懂都难




# 本关任务：根据本关卡所学知识，构建线性回归算法，并利用波斯顿房价数据对模型进行训练，然后对未知的房价数据进行预测。

# 相关知识
# 为了完成本关任务，你需要掌握：1.线性回归训练流程，2.线性回归的正规方程解。

# 数据集介绍
# 波斯顿房价数据集共有506条波斯顿房价的数据，每条数据包括对指定房屋的13项数值型特征和目标房价组成。用数据集的80%作为训练集，数据集的20%作为测试集，训练集和测试集中都包括特征和目标房价。

# sklearn中已经提供了波斯顿房价数据集的相关接口，想要使用该数据集可以使用如下代码：

# from sklearn import datasets
# #加载波斯顿房价数据集
# boston = datasets.load_boston()
# #X表示特征，y表示目标房价
# X = boston.data
# y = boston.target
# 数据集中部分数据与标签如下图所示：





# 线性回归训练流程
# 由数据集可以知道，每一个样本有13个特征与目标房价，而我们要做的事就是通过这13个特征来预测房价，我们可以构建一个多元线性回归模型，来对房价进行预测。模型如下：

# y=b+w 
# 1
# ​
#  x 
# 1
# ​
#  +w 
# 2
# ​
#  x 
# 2
# ​
#  +...+w 
# n
# ​
#  x 
# n
# ​
 

# 其中x 
# i
# ​
#  表示第i个特征值，w 
# i
# ​
#  表示第i个特征对应的权重，b表示偏置，y表示目标房价。

# 为了方便，我们稍微将模型进行变换：

# y=w 
# 0
# ​
#  x 
# 0
# ​
#  +w 
# 1
# ​
#  x 
# 1
# ​
#  +w 
# 2
# ​
#  x 
# 2
# ​
#  +...+w 
# n
# ​
#  x 
# n
# ​
 

# 其中x 
# 0
# ​
#  等于1。

# Y=heta.X

# heta=(w 
# 0
# ​
#  ,w 
# 1
# ​
#  ,...,w 
# n
# ​
#  )

# X=(1,x 
# 1
# ​
#  ,...,x 
# n
# ​
#  )

# 而我们的目的就是找出能够正确预测的多元线性回归模型，即找出正确的参数heta。那么如何寻找呢？通常在监督学习里面都会使用这么一个套路，构造一个损失函数，用来衡量真实值与预测值之间的差异，然后将问题转化为最优化损失函数。既然损失函数是用来衡量真实值与预测值之间的差异那么很多人自然而然的想到了用所有真实值与预测值的差的绝对值来表示损失函数。不过带绝对值的函数不容易求导，所以采用MSE(均方误差)作为损失函数，公式如下：

# loss= 
# m
# 1
# ​
#  sum 
# i=1
# m
# ​
#  (y 
# i
#  −p 
# i
#  ) 
# 2
 

# 其中p表示预测值，y表示真实值，m为样本总个数，i表示第i个样本。最后，我们再使用正规方程解来求得我们所需要的参数。

# 线性回归模型训练流程如下：



# 线性回归的正规方程解
# 对线性回归模型，假设训练集中m个训练样本，每个训练样本中有n个特征，可以使用矩阵的表示方法，预测函数可以写为：

# Y=hetaX

# 其损失函数可以表示为

# (Y−hetaX) 
# T
#  (Y−hetaX)

# 其中，标签Y为mx1的矩阵，训练特征X为mx(n+1)的矩阵，回归系数heta为(n+1)x1的矩阵，对heta求导，并令其导数等于0，可以得到X 
# T
#  (Y−hetaX)=0。所以，最优解为：

# heta=(X 
# T
#  X) 
# −1
#  X 
# T
#  Y

# 这个就是正规方程解，我们可以通过最优方程解直接求得我们所需要的参数。

# 编程要求
# 根据提示，在右侧编辑器补充 Python 代码，实现线性回归算法与MSE损失函数计算方法，并利用房价数据对模型进行训练，然后对未知的房价数据进行预测。

# 函数说明
# numpy方法：
# numpy.mean(array, axis)
# 指定轴上数组元素计算算术平均数。

# numpy.mean([ [1,2,3],
#       [4,5,6],
#       [7,8,9]],axis=0)
# [4. 5. 6.]
# numpy.ones(shape)
# 返回一个包含给定形状和数据类型的新数组。

# numpy.ones([3, 3])
# [[1. 1. 1.]
# [1. 1. 1.]
# [1. 1. 1.]]
# numpy.hstack((a, b))
# 按水平方向（列顺序）堆叠数组构成一个新的数组。

# numpy.hstack(([1,2,3],[4,5,6]))
# [1 2 3 4 5 6]
# numpy.vstack((a, b))
# 按垂直方向（行顺序）堆叠数组构成一个新的数组。

# numpy.vstack(([1,2,3],[4,5,6]))
# [[1 2 3]
# [4 5 6]]
# numpy线性代数方法：
# numpy.linalg.inv(m)
# 返回 m 的逆矩阵

# numpy.linalg.inv([[2,5],[1,3]])
# [[ 3. -5.]
# [-1.  2.]]
# numpy.dot(m1, m2)
# 矩阵 m1 与矩阵 m2 点乘。

# numpy.dot([[2,5],[1,3]], [[3,-5],[-1,2]])
# [[1 0]
# [0 1]]
# m.T
# 矩阵 m 的转置矩阵。

# m = np.array([[2,5],[1,3]])
# m.T
# [[2 1]
# [5 3]]
# 测试说明
# 只需返回预测结果即可，程序内部会检测您的代码，MSE低于30则视为过关。

# 学习参考
# 对于本项目觉得困难，实在无从着手的同学可以参考博文：https://www.yisu.com/zixun/46799.html

# 开始你的任务吧，祝你成功！

#encoding=utf8 
import numpy as np
def mse_score(y_predict,y_test):
    '''
    input:y_predict(ndarray):预测值
          y_test(ndarray):真实值
    ouput:mse(float):mse损失函数值
    '''
    #********* Begin *********#
    mse = np.mean((y_predict - y_test) ** 2)
    #********* End *********#
    return mse
class LinearRegression :
    def __init__(self):
        '''初始化线性回归模型'''
        self.theta = None
    def fit_normal(self,train_data,train_label):
        '''
        input:train_data(ndarray):训练样本
              train_label(ndarray):训练标签
        '''
        #********* Begin *********#
        X = np.c_[np.ones(train_data.shape[0]), train_data]
        self.theta = np.linalg.inv(X.T.dot(X)).dot(X.T).dot(train_label)
        #********* End *********#
        return self.theta
    def predict(self,test_data):
        '''
        input:test_data(ndarray):测试样本
        '''
        #********* Begin *********#
        X = np.c_[np.ones(test_data.shape[0]), test_data]
        predictions = X.dot(self.theta)
        return predictions
        #********* End *********#


# 本关任务：根据本关卡所学知识，用Python实现线性回归常用评估指标，并对构造的线性回归模型进行评估。

# 相关知识
# 为了完成本关任务，你需要掌握：1.均方误差(MSE)，2.均方根误差(RMSE)，3.平均绝对误差(MAE)，4.R-Squared。

# 前言
# 大家知道已经，机器学习通常都是将训练集上的数据对模型进行训练，然后再将测试集上的数据给训练好的模型进行预测，最后根据模型性能的好坏选择模型，对于分类问题，大家很容易想到，可以使用正确率来评估模型的性能，那么回归问题可以使用哪些指标用来评估呢？



# MSE
# MSE （Mean Squared Error）叫做均方误差,公式如下：

# m
# 1
# ​
#  sum 
# i=1
# m
# ​
#  (y 
# i
#  −p 
# i
#  ) 
# 2
 

# 其中y 
# i
#  表示第i个样本的真实标签，p 
# i
#  表示模型对第i个样本的预测标签。线性回归的目的就是让损失函数最小。那么模型训练出来了，我们在测试集上用损失函数来评估模型就行了。

# RMSE
# RMSE（Root Mean Squard Error）均方根误差，公式如下：

# sqrt 
# m
# 1
# ​
#  sum 
# i=1
# m
# ​
#  (y 
# i
#  −p 
# i
#  ) 
# 2
 

# RMSE其实就是MSE开个根号。有什么意义呢？其实实质是一样的。只不过用于数据更好的描述。

# 例如：要做房价预测，每平方是万元，我们预测结果也是万元。那么差值的平方单位应该是千万级别的。那我们不太好描述自己做的模型效果。怎么说呢？我们的模型误差是多少千万？于是干脆就开个根号就好了。我们误差的结果就跟我们数据是一个级别的了，在描述模型的时候就说，我们模型的误差是多少万元。

# MAE
# MAE(平均绝对误差)，公式如下：

# m
# 1
# ​
#  sum 
# i=1
# m
# ​
#  ∣y 
# i
#  −p 
# i
#  ∣

# MAE虽然不作为损失函数，确是一个非常直观的评估指标，它表示每个样本的预测标签值与真实标签值的L1距离。

# R-Squared
# 上面的几种衡量标准针对不同的模型会有不同的值。比如说预测房价 那么误差单位就是万元。数子可能是3，4，5之类的。那么预测身高就可能是0.1，0.6之类的。没有什么可读性，到底多少才算好呢？不知道，那要根据模型的应用场景来。 看看分类算法的衡量标准就是正确率，而正确率又在0～1之间，最高百分之百。最低0。如果是负数，则考虑非线性相关。很直观，而且不同模型一样的。那么线性回归有没有这样的衡量标准呢？
# R-Squared就是这么一个指标，公式如下：

# R 
# 2
#  =1− 
# sum 
# i
# ​
#  (y 
# mean
# i
# ​
#  −y 
# i
#  ) 
# 2
 
# sum 
# i
# ​
#  (p 
# i
#  −y 
# i
#  ) 
# 2
 
# ​
 

# 其中y 
# mean
# ​
#  表示所有测试样本标签值的均值。为什么这个指标会有刚刚我们提到的性能呢？我们分析下公式：



# 其实分子表示的是模型预测时产生的误差，分母表示的是对任意样本都预测为所有标签均值时产生的误差，由此可知：

# R 
# 2
#  leq1,当我们的模型不犯任何错误时，取最大值1；

# 当我们的模型性能跟基模型性能相同时，取0；

# 如果为负数，则说明我们训练出来的模型还不如基准模型，此时，很有可能我们的数据不存在任何线性关系。

# 编程要求
# 根据提示，在右侧编辑器Begin-End处补充代码，用Python实现R-Squared指标，并用实现的R-Squared指标来评估上一关的线性回归模型。

# 函数说明
# numpy方法：
# numpy.mean(array, axis)
# 指定轴上数组元素计算算术平均数。

# numpy.mean([ [1,2,3],
#       [4,5,6],
#       [7,8,9]],axis=0)
# [4. 5. 6.]
# numpy.var(array, axis)
# 指定轴上数组元素计算方差。

# numpy.var([ [1,2,3],
#       [4,5,6],
#       [7,8,9]],axis=0)
# [6. 6. 6.]
# numpy.ones(shape)
# 返回一个包含给定形状和数据类型的新数组。

# numpy.ones([3, 3])
# [[1. 1. 1.]
# [1. 1. 1.]
# [1. 1. 1.]]
# numpy.hstack((a, b))
# 按水平方向（列顺序）堆叠数组构成一个新的数组。

# numpy.hstack(([1,2,3],[4,5,6]))
# [1 2 3 4 5 6]
# numpy.vstack((a, b))
# 按垂直方向（行顺序）堆叠数组构成一个新的数组。

# numpy.vstack(([1,2,3],[4,5,6]))
# [[1 2 3]
# [4 5 6]]
# numpy线性代数方法：
# numpy.linalg.inv(m)
# 返回 m 的逆矩阵

# numpy.linalg.inv([[2,5],[1,3]])
# [[ 3. -5.]
# [-1.  2.]]
# numpy.dot(m1, m2)
# 矩阵 m1 与矩阵 m2 点乘。

# numpy.dot([[2,5],[1,3]], [[3,-5],[-1,2]])
# [[1 0]
# [0 1]]
# m.T
# 矩阵 m 的转置矩阵。

# m = np.array([[2,5],[1,3]])
# m.T
# [[2 1]
# [5 3]]
# 测试说明
# 只需返回预测结果即可，程序内部会检测您的代码，R-Squared指标高于0.6视为过关。

# 开始你的任务吧，祝你成功！
#encoding=utf8 
import numpy as np
#mse
def mse_score(y_predict,y_test):
    #********* Begin *********#
    mse = np.mean((y_predict - y_test) ** 2)
    #********* End *********#
    return mse
#r2
def r2_score(y_predict,y_test):
    '''
    input:y_predict(ndarray):预测值
          y_test(ndarray):真实值
    output:r2(float):r2值
    '''
    #********* Begin *********#
    ss_total = np.sum((y_test - np.mean(y_test)) ** 2)
    ss_res = np.sum((y_test - y_predict) ** 2)
    r2 = 1 - (ss_res / ss_total)
    #********* End *********#
    return r2
class LinearRegression :
    def __init__(self):
        '''初始化线性回归模型'''
        self.theta = None
    def fit_normal(self,train_data,train_label):
        '''
        input:train_data(ndarray):训练样本
              train_label(ndarray):训练标签
        '''
        #********* Begin *********#
        X_b = np.hstack([np.ones((len(train_data), 1)), train_data])
        self.theta = np.linalg.inv(X_b.T.dot(X_b)).dot(X_b.T).dot(train_label)
        #********* End *********#
        return self
    def predict(self,test_data):
        '''
        input:test_data(ndarray):测试样本
        '''
        #********* Begin *********#
        X_b = np.hstack([np.ones((len(test_data), 1)), test_data])
        y_predict = X_b.dot(self.theta)
        return y_predict
        #********* End *********#


# 本关任务：你需要调用 sklearn 中的线性回归模型，并通过波斯顿房价数据集中房价的13种属性与目标房价对线性回归模型进行训练。我们会调用你训练好的线性回归模型，来对房价进行预测。

# 相关知识
# 为了完成本关任务，你需要掌握：1.LinearRegression。

# 数据集介绍
# 波斯顿房价数据集共有506条波斯顿房价的数据，每条数据包括对指定房屋的13项数值型特征和目标房价组成。用数据集的80%作为训练集，数据集的20%作为测试集，训练集和测试集中都包括特征和目标房价。
# 想要使用该数据集可以使用如下代码：

# import pandas as pd
# #获取训练数据
# train_data = pd.read_csv('./step3/train_data.csv')
# #获取训练标签
# train_label = pd.read_csv('./step3/train_label.csv')
# train_label = train_label['target']
# #获取测试数据
# test_data = pd.read_csv('./step3/test_data.csv')
# 数据集中部分数据与标签如下图所示：




# LinearRegression
# LinearRegression的构造函数中有两个常用的参数可以设置：

# fit_intercept：是否有截据，如果没有则直线过原点，默认为Ture。
# normalize：是否将数据归一化,默认为False。
# LinearRegression类中的fit函数用于训练模型，fit函数有两个向量输入：

# X：大小为**[样本数量,特征数量]**的ndarray，存放训练样本
# Y：值为整型，大小为**[样本数量]**的ndarray，存放训练样本的标签值
# LinearRegression类中的predict函数用于预测，返回预测值，predict函数有一个向量输入：

# X：大小为**[样本数量,特征数量]**的ndarray，存放预测样本
# LinearRegression的使用代码如下：

# lr = LinearRegression()
# lr.fit(X_train, Y_train)
# predict = lr.predict(X_test)
# 编程要求
# 使用sklearn构建线性回归模型，利用训练集数据与训练标签对模型进行训练，然后使用训练好的模型对测试集数据进行预测，并将预测结果保存到./step3/result.csv中。保存格式如下：


# 测试说明
# 我们会获取你的预测结果与真实标签对比，R2指标高于0.6视为过关。

# 开始你的任务吧，祝你成功！

#encoding=utf8
import pandas as pd
from sklearn.linear_model import LinearRegression
#********* Begin *********#
#获取训练数据

#获取训练标签

#获取测试数据

#训练模型

#获取预测标签

#********* End *********#
#将预测标签写入csv
df = pd.DataFrame({'result':predict}) 
df.to_csv('./step3/result.csv', index=False)
