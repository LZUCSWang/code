#!/bin/bash

cd /home/stu_wxy/content/code
# 将执行结果追加到日志文件
git pull >> /home/stu_wxy/system/git.log
git add . >> /home/stu_wxy/system/git.log
git commit -m "update" >> /home/stu_wxy/system/git.log
git push >> /home/stu_wxy/system/git.log
# 为方便查看，追加一行日期
date >> /home/stu_wxy/system/git.log
# 同样，追加分割线
echo "==========" >> /home/stu_wxy/system/git.log