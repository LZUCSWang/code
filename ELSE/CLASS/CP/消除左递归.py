import os
import tkinter as tk
import tkinter.messagebox
import tkinter.font as tf

zhuizhong = ""
wenfa = {"非左递归文法"}
xi_ = ""
huo = ""

window = tk.Tk()
window.title('消除左递归')
window.minsize(500,500)
#转换坐标显示形式为元组
def getIndex(text, pos):
    return tuple(map(int, str.split(text.index(pos), ".")))

def zhijie(x,y):
    if not len(y):
        pass
    else:
        if x == y[0]:
            wenfa.discard("非左递归文法")
            #处理直接左递归
            zuobian = y.split('|')
            feizhongjie = []
            zhongjie = []
            for item in zuobian:
                if x in item:
                    item = item[1:]
                    textt = str(item) + str(x) + "'"
                    feizhongjie.append(textt)
                else:
                    text = str(item) + str(x) + "'"
                    zhongjie.append(text)
            if not zhongjie:#处理A -> Ax的情况
                zhongjie.append(str(x + "'"))
            cheng = str(x) + " -> " + "|".join(zhongjie)
            zi = str(x) + "'" + " -> " + "|".join(feizhongjie) + "|є"
            text_output.insert('insert','直接左递归文法','tag1')
            text_output.insert('insert','\n')
            text_output.insert('insert',cheng,'tag2')
            text_output.insert('insert','\n')
            text_output.insert('insert',zi,'tag2')
        '''
        加上会判断输出非递归产生式，但会导致间接左递归不能删除多余产生式
        else:
            h ="不变： " + x + " -> " + y
            text_output.insert('insert','非左递归文法','tag1')
            text_output.insert('insert','\n')
            text_output.insert('insert',h,'tag2')
        '''
        text_output.insert('insert','\n')

def zhijie2(x,y):
    if not len(y):
        pass
    else:
        if x == y[0]:
            wenfa.discard("非左递归文法")
            #处理直接左递归
            zuobian = y.split('|')
            feizhongjie = []
            zhongjie = []
            for item in zuobian:
                if x in item:
                    item = item[1:]
                    textt = str(item) + str(x) + "'"
                    feizhongjie.append(textt)
                else:
                    text = str(item) + str(x) + "'"  
                    zhongjie.append(text)
            cheng = str(x) + " -> " + "|".join(zhongjie)
            zi = str(x) + "'" + " -> " + "|".join(feizhongjie) + "|є"
            text_output.insert('insert',"间接左递归文法",'tag1')
            text_output.insert('insert','\n')
            text_output.insert('insert',cheng,'tag2')
            text_output.insert('insert','\n')
            text_output.insert('insert',zi,'tag2')

        text_output.insert('insert','\n')

def tihuan(xk,yi,yk):
    yi_you = []
    yi_wu =[]
    yi_he = ""
    yi_wuhe = ""
    yi_zhong = ""
    yi_feizhong = []
    if xk in yi:
        yk_replace = yk.split('|')
        yi_fenjie = yi.split('|')#将含非终结与不含分开
        for ba in yi_fenjie:
            if xk in ba:
                yi_you.append(ba)
            else:
                yi_wu.append(ba)

        yi_he = "|".join(yi_you)

        for item in yk_replace:
            yi_zhong = yi_he.replace(xk,item)#替换
            yi_feizhong.append(yi_zhong)
        yi_wuhe = "|".join(yi_wu)#再合并
        global zhuizhong
        zhuizhong = "|".join(yi_feizhong) + "|" + yi_wuhe

#点击按钮后执行的函数
def changeString():
    text_output.delete('1.0','end')
    text = text_input.get('1.0','end')
    text_list = list(text.split('\n'))#一行一行的拿文法
    text_list.pop()
    if not text_list[0]:
        print(tkinter.messagebox.showerror(title = '出错了！',message='输入不能为空'))
    else:
        for cfg in text_list:
            x,y = cfg.split('->')#将文法左右分开
            x = ''.join(x.split())#消除空格
            y = ''.join(y.split())
            if not (len(x) == 1 and x >= 'A' and x <= 'Z'):
                pos = text_input.search(x, '1.0', stopindex="end")
                result = tkinter.messagebox.showerror(title = '出错了！',
                message='非上下文无关文法!坐标%s'%(getIndex(text_input, pos),))
                # 返回值为：ok
                print(result)
                return 0
            else:
                zhijie(x,y)
            
        for i in range(len(text_list)):
            for k in range(i):
                xi,yi = text_list[i].split('->')
                xi = ''.join(xi.split())#消除空格
                yi = ''.join(yi.split())
                
                xk,yk = text_list[k].split('->')
                xk = ''.join(xk.split())#消除空格
                yk = ''.join(yk.split())

                tihuan(xk,yi,yk)
                tihuan(xk,zhuizhong,yk)
                global xi_
                xi_ = xi
        zhijie2(xi_,zhuizhong)

        for item in wenfa:
            text_output.insert('insert',item,'tag1')    

        
#创建文本输入框和按钮
text_input  = tk.Text(window, width=80, height=16)
text_output = tk.Text(window, width=80, height=20)
#简单样式
ft = tf.Font(family='微软雅黑',size=12)
text_output.tag_config("tag1",background="yellow",foreground="red",font=ft)
text_output.tag_config('tag2',font = ft)
#按钮
button = tk.Button(window,text="消除左递归",command=changeString,padx=32,pady=4,bd=4)
 
text_input.pack()
text_output.pack()
button.pack()
window.mainloop()
