from django.conf.urls import url

import views

urlpatterns = [
    url(r'^ajax/(?P<module>\w+)/(?P<function>\w+)/', views.ajax, name='ajax'),
    url(r'^$', views.index, name='index'),
    url(r'^entry', views.entry, name='entry'),
    url(r'^play', views.play, name='play'),
    url(r'^rules', views.rules, name='rules'),
]


