from __future__ import unicode_literals

from django.db import models

# Create your models here.
class Node(models.Model):
	describe = models.CharField(max_length=100)

	def __unicode__(self):
		return "%s %s"%(self.id, self.describe)

class ParamSetting(models.Model):
	name = models.CharField(max_length=100)
	value_min = models.FloatField()
	value_max = models.FloatField()

	def __unicode__(self):
		return "{} {} {}".format(self.name, self.value_min, self.value_max)

class ParamValue(models.Model):
	node = models.ForeignKey(Node)
	param = models.ForeignKey(ParamSetting)
	time = models.DateTimeField(auto_now_add=True)
	value = models.FloatField()
