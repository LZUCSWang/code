from django.contrib import admin
from django.urls import path, include
import views

urlpatterns = [
    path('tasks/dashboard/', views.dashboard, name='dashboard'),
]
