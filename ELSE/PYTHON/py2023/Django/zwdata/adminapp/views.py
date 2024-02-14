from django.shortcuts import render, redirect
from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger
from django.contrib.auth.decorators import login_required
from userapp.models import *
from adminapp.forms import AffairForm
from django.db.models import Q
import pandas as pd

# 数据查询
@login_required
def alldata(request):
    if not request.user.is_superuser: # 验证用户身份，不是管理员则跳转到登陆页面
        return redirect('/login/')

    lists = Affair.objects.all()
    # 搜索
    search = request.GET.get('search', '')
    if search:
        lists = lists.filter(Q(City__icontains=search)|Q(Title__icontains=search))

    paginator = Paginator(lists, 10)
    page = request.GET.get('page')
    try:
        contacts = paginator.page(page)
    except PageNotAnInteger:
        contacts = paginator.page(1)
    except EmptyPage:
        contacts = paginator.page(paginator.num_pages)
    return render(request, 'admin/alldata.html', {'search':search, 'contacts':contacts,'paginator':paginator,'page':page})

@login_required
def add(request):
    if not request.user.is_superuser: # 验证用户身份，不是管理员则跳转到登陆页面
        return redirect('/login/')
    if request.method == 'GET':
        form = AffairForm()
    if request.method == 'POST':
        form = AffairForm(request.POST)
        if form.is_valid():
            data = form.cleaned_data
            obj = Affair.objects.create(**data)
            return redirect('/admin/')
    return render(request, 'admin/add.html', locals())

@login_required
def edit(request, id):
    if not request.user.is_superuser: # 验证用户身份，不是管理员则跳转到登陆页面
        return redirect('/login/')
    info = Affair.objects.get(id=id)
    if request.method == 'GET':
        form = AffairForm(instance=info)
    if request.method == 'POST':
        form = AffairForm(data=request.POST, instance=info)
        if form.is_valid():
            form.save()
            search = request.GET.get('search', '')
            return redirect('/admin/')
    return render(request, 'admin/edit.html', locals())

@login_required
def delete(request, id):
    if not request.user.is_superuser: # 验证用户身份，不是管理员则跳转到登陆页面
        return redirect('/login/')
    Affair.objects.get(id=id).delete()

    search = request.GET.get('search', '')
    return redirect('/admin/?search='+search)


# 上传
@login_required
def upload(request):
    if not request.user.is_superuser: # 验证用户身份，不是管理员则跳转到登陆页面
        return redirect('/login/')
    if request.method == 'GET':
        '''显示上传页面'''
        return render(request, 'admin/upload.html')
    if request.method == 'POST':
        city = request.POST.get('city', None)
        file = request.FILES.get('file', None)
        # 判断参数是否齐全
        if file:
            # 用pandas读取数据
            data = pd.read_excel(file, header=0, dtype=str, engine='openpyxl',keep_default_na=False)
            for index, row in data.iterrows():
                if row['Title']:
                    # 存入数据库
                    try:
                        obj = Affair.objects.create(City=city,Title=row['Title'],Time=row['Time'],Content=row['Content'])
                        if row['RepDep']:
                            obj.RepDep=row['RepDep']
                        if row['RepCon']:
                            obj.RepCon=row['RepCon']
                        if row['URL']:
                            obj.URL=row['URL']
                        if row['RepTime']:
                            obj.RepTime=row['RepTime']
                        obj.save()
                        print('已录入数据', index)
                    except:
                        continue
        return redirect('/admin/')
