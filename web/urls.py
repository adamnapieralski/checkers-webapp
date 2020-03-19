from django.conf.urls import patterns, include, url

import views

urlpatterns = patterns('',
                       url(r'^ajax/(?P<module>\w+)/(?P<function>\w+)/', views.ajax, name='ajax'),
                       url(r'^$', views.index, name='index'),
                       url(r'^', views.index, name='index')
)



