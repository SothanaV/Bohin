from django.shortcuts import render
from .models import Meter
from django.http import HttpResponse, JsonResponse
from django.shortcuts import redirect
from django.core import serializers
# Create your views here.
def getdata(request,nodeid,volt):
	Volt_meter = Meter(
		nodeid = nodeid ,
		volt 	= float(volt), 
		)
	Volt_meter.save()
	print ("Save")
	return HttpResponse("OK",content_type='text/plain')
def showdata(request):
	#data = Room.objects.all().values('nodeid','temp','humi','time')
	data = Meter.objects.all().order_by("-time").values('time','volt')
	print(data)
	return JsonResponse(list(data), safe=False)
def graph(request):
	return render(request, 'first.html')