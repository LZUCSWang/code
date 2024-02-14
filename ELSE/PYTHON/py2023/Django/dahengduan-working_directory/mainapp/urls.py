from django.urls import path
from . import views

app_name = 'mainapp'

urlpatterns = [
    path('index/', views.index, name='index'),
    path('ethnic_page/', views.ethnic_page, name='ethnic_page'),
    path('contacts/', views.contacts, name='contacts'),
    path('tourism_page/', views.tourism_page, name='tourism_page'),
]
