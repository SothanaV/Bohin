from __future__ import unicode_literals

from django.contrib import admin
from .models import Meter
# Register your models here.
class MeterAdmin(admin.ModelAdmin):
	list_display=[f.name for f in Meter._meta.fields]
admin.site.register(Meter,MeterAdmin)