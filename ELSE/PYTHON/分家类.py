'''
Author: 王贤义
FilePath: \code\PYTHON\分家类.py
Description: 
'''
import math 
class PlaneGraphics():
    def __init__(self,shape):
        self.shape=shape
    def area(self):
        pass
    def show(self):
        print("{}的面积是{}".format(self.shape,self.area()))
#定义长方形类Rectangle继承PlaneGraphics类
class Rectangle(PlaneGraphics):
    def __init__(self,length,width):
        super().__init__("长方形")
        self.length=length
        self.width=width
    def area(self):#重写父类的area方法
        return self.length*self.width
class Ecilipse(PlaneGraphics):
    def __init__(self,a,b):
        super().__init__("椭圆形")
        self.a=a
        self.b=b
    def area(self):
        return math.pi*self.a*self.b

r = Rectangle(10,20)
r.show()
e=Ecilipse(10,20)
print(e.area())
r= Rectangle(100,100)
r.show()
