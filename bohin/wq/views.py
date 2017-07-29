import json

from django.shortcuts import render
from django.http import HttpResponse
from django.http import JsonResponse
from .models import *
# Create your views here.

def passdata(request, nodeid, sensor_name, value):
	if request.method == 'GET':
		current_node = Node.objects.get(id=nodeid)
		current_param = ParamSetting.objects.get(name=sensor_name)

		ParamValue.objects.create(node=current_node, 
			param=current_param, value=value)
	
	return HttpResponse( '%s %s %s'%(nodeid, sensor_name, value) )

def getdata(request):
	data = ParamValue.objects.filter(node__id=3, param__name='ph').order_by('-time').values('time', 'value')
	return JsonResponse( list(data) , safe= False)

def graph(request):
	return render(request, 'first.html')