import psutil
def suspend_process(pid):
    process = psutil.Process(pid)
    process.suspend()
def terminate_process(pid):
    process = psutil.Process(pid)
    process.terminate()
def get_process_pid(process_name):
    for process in psutil.process_iter():
        # if process.name() == process_name:
        #     return process.pid
        # print(process.name())
        if process.name() == "msedge.exe":
            try:
                terminate_process(process.pid)
                print("Process {} has been terminated.".format(process.pid))
            except:
                pass
    return None
for proc in psutil.process_iter(['pid', 'name']):
    if 'msedge' in proc.info['name']:
        # 隐藏进程
        print(proc.info['pid'])
        psutil.Process(proc.info['pid']).nice(20)
# pid = get_process_pid("your_process_name")
# if pid:
#     print("PID: {}".format(pid))
# else:
#     print("Process not found.")