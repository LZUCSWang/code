from flask import Flask,request,render_template

######################################
# http://127.0.0.1:5000/aichat
# 问：你吃饭了吗？
# 问：一起看电影把？
# ...
# 扩展 aiwork 函数，增强功能
######################################

app = Flask(__name__)

chatmsg = []

def aiwork(text):
	aitalk = text.replace('你','我').replace('吧,','！').replace('吗','').replace('？','！')
	return '小兰： ' +  aitalk

@app.route('/aichat',methods=['POST','GET'])
def ai_post():
	if request.method == 'GET':
		return render_template('chatai.html')
	text = request.form['chat']
	chatmsg.append(text)
	chatmsg.append( aiwork(text) )
	cc = chatmsg.copy()
	cc.reverse()
	return render_template('chatai.html',chatmsg = cc)


app.run(debug=True)