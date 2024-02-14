from django.shortcuts import render

# Create your views here.
from django.contrib.auth.models import User
from django.shortcuts import render
from mainapp.models import tourism, ethnic, pic


def dashboard(request):
    user_count = User.objects.count()
    attractions_count = tourism.objects.count()
    ethnics_count = ethnic.objects.count()
    img_count = pic.objects.count()

    context = {'user_count': user_count, 'attactions_count': attractions_count, 'ethnics_count': ethnics_count, 'img_count': img_count}
    return render(request, 'backend/dashboard.html', context)
