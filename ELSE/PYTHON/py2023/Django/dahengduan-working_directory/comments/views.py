from django.shortcuts import render, redirect
from django.views.generic.list import ListView
from .models import comment
from mainapp.models import tourism
from .forms import CommentForm


# Create your views here.
def post_comment(request):
    # HTTP 请求有 get 和 post 两种，一般用户通过表单提交数据都是通过 post 请求，
    # 因此只有当用户的请求为 post 时才需要处理表单数据。
    if request.method == 'POST':
        form = CommentForm(request.POST)
        #if form.is_valid():
            # 检查到数据是合法的，调用表单的 save 方法保存数据到数据库，
            # commit=False 的作用是仅仅利用表单的数据生成 Comment 模型类的实例，但还不保存评论数据到数据库。

        user = request.user
        place = tourism.objects.all()[0]
        content = request.POST.get('content')

        comment_temp = comment(user=user, place=place, content=content)
        # 最终将评论数据保存进数据库，调用模型实例的 save 方法
        comment_temp.save()


    return redirect("mainapp:tourism_page")
