# -*- coding: utf-8 -*-
# Generated by Django 1.11.3 on 2017-07-30 07:16
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Meter',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('time', models.DateTimeField(auto_now_add=True)),
                ('nodeid', models.CharField(max_length=10)),
                ('volt', models.FloatField(default=0.0)),
            ],
        ),
    ]
