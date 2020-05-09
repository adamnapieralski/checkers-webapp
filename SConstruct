# -*- mode: Python; -*-
import os, platform, subprocess, re, time, shutil, sys, signal

MYAPP_VER_MAJOR = '0'
MYAPP_VER_MINOR = '03'

WEB_SRV_PREFIX = 'srvmyapp'
WEB_SRV_HOST = '127.0.0.1'
WEB_SRV_PORT = '50007'
WEB_CLIENT_HOST = '127.0.0.1'
WEB_CLIENT_PORT = '8000'

server_url = 'http://{}:{}/'.format(WEB_CLIENT_HOST, WEB_CLIENT_PORT)


Export('MYAPP_VER_MAJOR MYAPP_VER_MINOR')
Export('WEB_SRV_PREFIX WEB_SRV_HOST WEB_SRV_PORT WEB_CLIENT_HOST WEB_CLIENT_PORT')

AddOption('--run', dest='runserver', type=None, nargs=0)

vars = Variables('custom.py')

env = Environment(variables=vars)
test_val = ARGUMENTS.get('test', 0)
python_version = ARGUMENTS.get('python', '3.6')
supported_python_versions = ['2.6', '2.7', '3.6', '3.7']

if python_version not in supported_python_versions:
    raise AttributeError("Selected python version not supported. Build terminated.")
SConscript(['checkers/SConscript', 'web/SConscript'], exports=['env', 'python_version', 'test_val'] )

if GetOption('runserver') is not None:
    os.system('python{} build_web/manage.py runserver {}:{}'.format(str(python_version)[0], WEB_CLIENT_HOST, WEB_CLIENT_PORT))
