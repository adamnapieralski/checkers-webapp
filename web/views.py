import django.http
import json
import traceback

#all modules should be imported here

from django.shortcuts import render
from django.template import RequestContext
from django.http import HttpResponse
from django.shortcuts import redirect

import checkerspy.views

def index(request):
    return redirect('/entry')
    
def entry(request):
    return render(request, 'entry.html')
    
def play(request):
    return render(request, 'game.html')

def rules(request):
    return render(request, 'rules.html')

def ajax(request, module, function):
    """dispatch ajax requests"""
    try:
		
        fun = getattr(getattr(globals()[str(module)], 'views'), str(function))
        data = json.dumps( fun(request.GET) )
        return django.http.HttpResponse(data, content_type='application/json')
    except:
        return render(request, 'game.html')
