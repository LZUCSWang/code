import xlsxwriter
def outPut(model):
    work = xlsxwriter.Workbook('result_1000(nolocal_search).xlsx')
    # result_600(nolocal_search).xlsx
    worksheet = work.add_worksheet()
    worksheet.write(0, 0, 'obj')
    worksheet.write(0, 1, model.best_sol.obj)
    for row,item in enumerate(model.best_sol.nodes_seq):
        worksheet.write(row + 1, 0,'v'+str(item) )
        worksheet.write(row + 1, 1, model.node_list[item].restored_area)
    work.close()