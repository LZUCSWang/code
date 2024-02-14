from django.db import models
from django.db.models.signals import pre_delete, post_init, post_save
from django.dispatch import receiver


# Create your models here.

class pic(models.Model):
    img = models.ImageField(upload_to='img')
    name = models.CharField(max_length=20)

    def __str__(self):
        return self.name



class tourism(models.Model):

    name = models.CharField(max_length=20)
    img = models.ImageField(upload_to='tourism')
    img_index = models.ImageField(upload_to='tourism')
    intro = models.CharField(max_length=250)
    longitude = models.FloatField()
    latitude = models.FloatField()

    def __str__(self):
        return self.name


class ethnic(models.Model):
    name = models.CharField(max_length=20)
    img = models.ImageField(upload_to='ethnic')
    intro = models.CharField(max_length=250)
    population = models.CharField(max_length=20)
    intro_long = models.CharField(max_length=1000)
    def __str__(self):
        return self.name


@receiver(pre_delete, sender=pic)
@receiver(pre_delete, sender=tourism)
@receiver(pre_delete, sender=ethnic)
def file_delete(instance, **kwargs):  # 函数名随意
    # print('进入文件删除方法，删的是',instance.img)   # 用于测试
    instance.img.delete(False)  # file是保存文件或图片的字段名**


@receiver(post_init, sender=pic)
@receiver(post_init, sender=tourism)
@receiver(post_init, sender=ethnic)
def file_path(sender, instance, **kwargs):
    instance._current_file = instance.img


@receiver(post_save, sender=pic)
@receiver(post_save, sender=tourism)
@receiver(post_save, sender=ethnic)
def delete_old_image(sender, instance, **kwargs):
    if hasattr(instance, '_current_file'):
        if instance._current_file != instance.img:
            instance._current_file.delete(save=False)
