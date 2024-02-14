from django.contrib import admin

# Register your models here.
from mainapp.models import pic, tourism, ethnic
from comments.models import comment

admin.site.register(pic)
admin.site.register(tourism)
admin.site.register(ethnic)
admin.site.register(comment)

