
import sys

# 请在此输入您的代码

for qin in range(1, 10):
    for cai in range(10):
        for first in range(10):
            for bian in range(10):
                for shang in range(10):
                    for deng in range(10):
                        tempset=set()
                        tempset.add(qin)
                        tempset.add(cai)
                        tempset.add(first)
                        tempset.add(bian)
                        tempset.add(shang)
                        tempset.add(deng)
                        if len(tempset)==6:
                            temp = qin*100+cai*10+first
                            if temp**2 == qin*100000+bian*10000+shang*1000+deng*100+bian*10+cai:
                                print(temp)
                                sys.exit()
