##################################
# python app.py 运行
# 用 flask 做了 web 开发的入门演示
##################################

from flask import Flask,request,render_template

app = Flask(__name__)

# 目录
@app.route('/')
def index(): 
    return """
      <h1><a href="/h1/"> simple hello </a></h1>
      <h1><a href="/h2/"> file hello </a></h1>
      <h1><a href="/h3/"> text hello </a></h1>
      <h1><a href="/h4/"> comboxlist hello </a></h1>
      <h1><a href="/h5/"> radio hello </a></h1>
    """


# 最简单的形式
@app.route('/h1/')
def f1(): return 'hello world !'


# 使用了网页模板
@app.route('/h2/')
def f2(): return render_template('h2.html')


# 参数传递
@app.route('/h3/',methods = ['POST','GET'] )
def f3(): 
    if request.method == 'POST':
        return '<h1> hello {} </h1>'.format(request.form['user'])
    return render_template('h3.html')

import pandas as pd
data = pd.read_excel('py2023\hello\py_big.xls',header=1)['姓  名'].to_list()


# 读取数据组合框选择打招呼对象
@app.route('/h4/',methods = ['POST','GET'] )
def f4(): 
    if request.method == 'POST':
        return '<h1> hello {} </h1>'.format(request.form['user'])
    return render_template('h4.html',data = data)


# 读取数据无线按钮选择打招呼对象
@app.route('/h5/',methods = ['POST','GET'] )
def f5(): 
    if request.method == 'POST':
        return '<h1> hello {} </h1>'.format(request.form['user'])
    return render_template('h5.html',data = data)


# 指定了端口为 5005，也就是 http://127.0.0.1:5005/ 访问
app.run( port=5005 )