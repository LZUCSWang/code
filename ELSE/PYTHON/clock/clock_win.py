# 导入tkinter模块
import threading
import tkinter as tk
import tkinter.filedialog as tk_file_dlg
import tkinter.ttk as ttk
import time

# 空字典，存放任务，key：优先级，value：任务列表
task_dict = {}
# 排序后的优先级
level_sorted = []


class Task:
    work_time = 3
    rest_time = 2

    def __init__(self, name, level, state):
        self.name = name
        self.level = level
        self.state = state

    @classmethod
    def reset(cls):
        cls.work_time = 3
        cls.rest_time = 2


def sort_task(lines):
    global task_dict
    global level_sorted

    for l in lines:
        cols = l.strip('\n').split('\t')

        # cols[0]：任务名，cols[1]，优先级，cols[2]：任务状态
        level = cols[1]
        task_list = task_dict.get(level)
        if task_list is None:
            task_dict[level] = list()
        task_dict[level].append(Task(cols[0], cols[1], cols[2]))

    # 对key进行排序，返回排序后的优先级，并未影响task_dict中的值
    level_sorted = sorted(task_dict)


def work(task):
    while task.work_time > 0:
        time.sleep(1)
        task.work_time -= 1
        time_label['text'] = '{0.name} 00:{0.work_time:02d}:00'.format(task)

    task.state = 'Finish'


def rest(task):
    while task.rest_time > 0:
        time.sleep(1)
        task.rest_time -= 1
        time_label['text'] = '休息时间 00:{0.rest_time:02d}:00'.format(task)


def open_file_btn_click():
    lines = []
    file_name = tk_file_dlg.askopenfilename()
    try:
        f = open(file_name, 'r+', encoding='utf-8')  # 以读写方式打开任务文件works.txt
        lines = f.readlines()  # 读取所有的行，保存在lines列表中
    except FileNotFoundError:
        print('No such file!')
    except IOError:
        print('IO error!')
    else:
        sort_task(lines)
        for level in level_sorted:  # 遍历所有的优先级
            for task in task_dict[level]:  # 遍历每一个优先级下的任务列表
                data = (task.name, task.level, task.state)
                datagrid.insert('',  # 对于表格类型的Treeview，parent一般为空
                                'end',  # 在最末插入新数据
                                values=data)


def tomato():
    for level in level_sorted:  # 遍历所有的优先级
        for task in task_dict[level]:  # 遍历每一个优先级下的任务列表
            time_label['text'] = '{0.name} 00:{0.work_time:02d}:00'.format(task)
            work(task)
            time_label['text'] = '休息时间 00:{0.rest_time:02d}:00'.format(task)
            rest(task)

            Task.reset()


def start_task():
    t = threading.Thread(target=tomato)
    t.daemon = True
    t.start()


# 创建GUI主窗体
root = tk.Tk()

root.title('番茄钟')  # 窗口标题
root.geometry('300x500+200+50')  # 宽 高 左上角顶点(x,y)

# 添加控件，编写事件对应的响应函数，将控件的事件与相应函数关联
# 创建“打开任务文件”按钮
open_btn = tk.Button(root,
                     text='从文件读入任务',
                     command=open_file_btn_click)
open_btn.pack()

# 创建树控件显示任务
col_id = ('task', 'level', 'state')  # 列的别名，唯一标识一列
col_head = ('任务', '优先级', '状态')  # 列头
datagrid = ttk.Treeview(root,
                        columns=col_id,
                        show='headings',
                        padding=(10, 5, 20, 30))
for i in range(len(col_id)):
    datagrid.column(col_id[i], width=70, anchor='center')
    datagrid.heading(col_id[i], text=col_head[i])
datagrid.pack()

# 创建按钮“开启番茄钟”
start_btn = tk.Button(root,
                      text='开启番茄钟',
                      command=start_task)
start_btn.pack()

# 创建标签显示倒计时
time_label = tk.Label(root, text='None 00:00:00')
time_label.pack()

# 启动消息主循环，在主循环中等待用户触发事件响应
root.mainloop()
