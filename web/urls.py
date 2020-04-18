from django.conf.urls import url

import views

#urlpatterns = patterns('',
#                       url(r'^ajax/(?P<module>\w+)/(?P<function>\w+)/', views.ajax, name='ajax'),
#                       url(r'^$', views.index, name='index'),
#                       url(r'^', views.index, name='index')
#)

urlpatterns = [
    url(r'^ajax/(?P<module>\w+)/(?P<function>\w+)/', views.ajax, name='ajax'),
    url(r'^$', views.index, name='index'),
    url(r'^entry', views.entry, name='entry'),
    url(r'^play', views.play, name='play'),
]


