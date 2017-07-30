from django.db import models
from django.utils import timezone
# Create your models here.
class Meter(models.Model):
    time    = models.DateTimeField(auto_now_add=True)
    nodeid  = models.CharField(max_length=10, blank=False)
    volt    = models.FloatField(default=0.0)