AB = 52.1
BC = 57.2
CD = 43.5
DE = 51.9
EA = 33.4
EB = 68.2
EC = 71.9
def deal(datas,b,c):
    temp=(datas+b+c)/2
    return (temp*(temp-datas)*(temp-b)*(temp-c))**0.5
print(round(deal(AB,EB,EA)+deal(CD,DE,EC)+deal(BC,EC,EB),2))