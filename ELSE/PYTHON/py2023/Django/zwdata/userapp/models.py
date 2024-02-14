from django.db import models
from django.contrib.auth.models import AbstractUser


# 用户类
# 重写django的用户模型类，作为网站的用户类
class User(AbstractUser, models.Model):
    class Meta:
        verbose_name = "用户"
        verbose_name_plural = verbose_name


# 政务数据
class Affair(models.Model):
    City = models.CharField("城市", max_length=20)
    Title = models.CharField("标题", max_length=100)
    Time = models.DateTimeField("发布时间")
    Content = models.TextField("内容")
    RepDep = models.CharField("回复部门", max_length=100,blank=True,null=True)
    RepTime = models.DateTimeField("回复时间",blank=True,null=True)
    RepCon = models.TextField("回复内容",blank=True,null=True)
    URL = models.CharField("链接", max_length=300,blank=True,null=True)

    class Meta:
        verbose_name = "政务数据"
        verbose_name_plural = verbose_name
