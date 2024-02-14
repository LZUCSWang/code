import math
qli=1/200*pow(1/4.7*1e7,0.5)
qc=5268/728.6
qli2=1/500*pow(1/4.7*1e7,0.5)
qc2=2500/859.3

# print(qc)
# print(qc2)
# print(qli)
# print(qli2)
def wucha(shi,li):
    return abs(li-shi)/li*100
print(wucha(qc2,qli2))

