import django.http
import json
import traceback

#all modules should be imported here

from django.shortcuts import render_to_response

from django.template import RequestContext

from django.http import HttpResponse

import checkerspy
import checkerspy.views

def index(request):
    """for working server"""
    return render_to_response('tresc.html', {}, context_instance=RequestContext(request))
    
def entry(request):
    return render_to_response('entry.html', {}, context_instance=RequestContext(request))
    
def play(request):
    return render_to_response('tresc.html', {}, context_instance=RequestContext(request))

def ajax(request, module, function):
    """dispatch ajax requests"""
    try:
		
        fun = getattr(getattr(globals()[str(module)], 'views'), str(function))
        data = json.dumps( fun(request.GET) )
        return django.http.HttpResponse(data, content_type='application/json')
    except:
        return render_to_response('tresc.html', {}, context_instance=RequestContext(request))
