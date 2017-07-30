from django.conf.urls import url
from . import views

urlpatterns = [
	url(r'^data/(?P<nodeid>\d+)/(?P<volt>\d+\.\d+)/?$', views.getdata, name='getdata'),
	url(r'^showdata/', views.showdata, name='showdata'),
	url(r'^home/', views.graph, name='home'),
]