import time
ts = time.sleep
get_time = time.perf_counter
def pp(x): print('运行时间', int(1000*get_time()-x))
def f1(): print('f1 run'); ts(0.2)
def f2(): print('f2 run'); ts(0.8)
def f3(): print('f3 run'); ts(0.5)


def timeit2(f):
    def wrapper():
        print("do timeit2")
        f()
    return wrapper


def timeit(f):  # 这个装饰器只能装饰无参数函数，f，因为wrapper没有参数
    def wrapper():
        t = get_time()
        f()
        pp(t)
    return wrapper


# 装饰器的执行顺序，从下往上
print("start")
@timeit2
@timeit
def f5(): print("f5 run"); ts(0.2)


f5()
