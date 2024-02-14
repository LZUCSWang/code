
# # vcc=float(input("输入直流电压:"))
# # rb=float(input("输入电阻rb:"))
# # rc1=float(input("输入电阻rc1:"))
# # rc2=float(input("输入电阻rc2:"))
# # rl=float(input("输入电阻rl:"))
# # Ibq=vcc/rb
# # Icq=B*Ibq
# # Vceq=vcc-Icq*(rc1+rc2)
# # print(Ibq,Icq,Vceq)
# # rbe=300+(1+B)*(26/1000/Icq)
# # Au=-B*(rc2*rl)/(rc2+rl)/rbe
# # Ri=rb*rbe/(rb+rbe)
# # Ro=rc2
# # print(rbe,Au,Ri,Ro)
def bl(datas,b):
    return datas*b/(datas+b)
def q3():
    B=int(input("输入放大倍数B:"))
    Re=float(input("输入电阻Re:"))
    Rl=float(input("输入电阻Rl:"))
    Rb1=float(input("输入电阻Rb1:"))
    Rb2=float(input("输入电阻Rb2:"))
    Rs=float(input("输入电阻Rs:"))
    rbe=300+(1+50)*26/2
    print(rbe)
    Au=(1+B)*bl(Re,Rl)/((1+B)*bl(Re,Rl)+rbe)
    print(Au)
    # print(-60*bl(3000,6000)/rbe)
    Ri=bl(Rb1,bl(Rb2,(rbe+(1+B)*(bl(Re,Rl)))))
    print(Ri)
    Ro=bl(Re,(bl(Rs,bl(Rb1,Rb2))+rbe)/(1+B))
    print(Ro)
def Aucount(B,Rc,Rl,rbe):
    return -B*bl(Rc,Rl)/rbe
def q1():
    rbe=300+(1+50)*26/2
    print(rbe)
    print(Aucount(50,3000,6000,rbe))
    Rb=300000
    print(bl(Rb,rbe))
def jintai():
    vc=float(input("输入集电极电压:"))
    vb=float(input("输入基极电压:"))
    ve=float(input("输入射极电压:"))
    Ib,Ic=-vb/(10000+510),(12-vc)/10000
    B=Ic/Ib
    print(Ib,Ic,B)
jintai()
jintai()