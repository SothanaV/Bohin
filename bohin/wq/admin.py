from django.contrib import admin
from .models import *
# Register your models here.

class NodeAdmin(admin.ModelAdmin):
	list_display = ('id', 'describe' )

class SettingAdmin(admin.ModelAdmin):
	list_display = ('name', 'value_min', 'value_max')

class ValueAdmin(admin.ModelAdmin):
	list_display = ('node', 'param', 'time', 'value')

admin.site.register(Node, NodeAdmin)
admin.site.register(ParamSetting, SettingAdmin)
admin.site.register(ParamValue, ValueAdmin)
