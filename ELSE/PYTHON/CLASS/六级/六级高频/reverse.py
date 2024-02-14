from turtle import end_fill
import xlrd
data=xlrd.open_workbook('D:\code\python\六级高频\六级高频词汇.xls')
table=data.sheets()[0]
data_row = []
for row in range(table.nrows):
    item=(table.row_values(row)[1],table.row_values(row)[3])
    data_row.append(item)
f=open('D:\code\python\六级高频\data.txt','w',encoding='utf-8')
for i in data_row:
    f.write(i[0]+' '+i[1]+'\n')
f.close()

print(data_row)