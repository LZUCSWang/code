import os
import sys
count = "****     180.90       88折\
****      10.25       65折\
****      56.14        9折\
****     104.65        9折\
****     100.30       88折\
****     297.15        半价\
****      26.75       65折\
****     130.62        半价\
****     240.28       58折\
****     270.62        8折\
****     115.87       88折\
****     247.34       95折\
****      73.21        9折\
****     101.00        半价\
****      79.54        半价\
****     278.44        7折\
****     199.26        半价\
****      12.97        9折\
****     166.30       78折\
****     125.50       58折\
****      84.98        9折\
****     113.35       68折\
****     166.57        半价\
****      42.56        9折\
****      81.90       95折\
****     131.78        8折\
****     255.89       78折\
****     109.17        9折\
****     146.69       68折\
****     139.33       65折\
****     141.16       78折\
****     154.74        8折\
****      59.42        8折\
****      85.44       68折\
****     293.70       88折\
****     261.79       65折\
****      11.30       88折\
****     268.27       58折\
****     128.29       88折\
****     251.03        8折\
****     208.39       75折\
****     128.88       75折\
****      62.06        9折\
****     225.87       75折\
****      12.89       75折\
****      34.28       75折\
****      62.16       58折\
****     129.12        半价\
****     218.37        半价\
****     289.69        8折"
count = count.split()
cnt = []
realcnt = []
cntwer=0
for i in count:
    cnt.append(i.split('折'))
for i in range(len(cnt)-1):
    if cnt[i+1][0] == '半价****':
        realcnt.append(50)
    elif len(cnt[i+1][0])==1:
        realcnt.append(float(cnt[i+1][0])*10)
    else :
        realcnt.append(float(cnt[i+1][0]))
i=0
while i<len(realcnt)-1:
    cntwer+=realcnt[i]*realcnt[i+1]/100
    i+=2
print(realcnt)
if cntwer%100==0:
    print(cntwer)
else :
    cntwer=(int(cntwer/100)+1)
    print(cntwer*100)
# 请在此输入您的代码