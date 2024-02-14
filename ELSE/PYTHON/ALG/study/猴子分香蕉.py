cnt=6
while cnt>0:
    tempcnt=cnt
    if tempcnt%5==1 and tempcnt//5!=0:
        tempcnt=tempcnt-tempcnt//5-1
        if tempcnt%5==2 and tempcnt//5!=0:
            tempcnt=tempcnt-tempcnt//5-2
            if tempcnt%5==3 and tempcnt//5!=0:
                tempcnt=tempcnt-tempcnt//5-3
                if tempcnt%5==4 and tempcnt//5!=0:
                    tempcnt=tempcnt-tempcnt//5-4
                    if tempcnt%5==0 and tempcnt//5!=0:
                        print(cnt)
                        break
    cnt+=1