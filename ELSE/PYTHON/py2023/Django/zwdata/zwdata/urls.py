"""zwdata URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
# from django.contrib import admin
from django.urls import path
from userapp import views as user
from adminapp import views as admin

urlpatterns = [
    path('', user.index),  # 首页
    path('register/', user.register),  # 注册
    path('login/', user.login_),  # 登陆
    path('logout/', user.logout_),  # 登出

    path('data/', user.showdata),  # 数据查询
    path('detail/<int:id>/', user.detail),
    path('download/', user.download),  # 数据下载
    path('getdata/', user.getdata),
    path('charts/', user.charts),  # echarts数据分析可视化


    path('admin/', admin.alldata),
    path('admin/upload/', admin.upload),  # 数据上传
    path('admin/add/', admin.add),  # 数据添加
    path('admin/edit/<int:id>/', admin.edit),  # 修改
    path('admin/delete/<int:id>/', admin.delete),  # 删除
]
