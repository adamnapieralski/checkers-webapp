# -*- mode: Python; -*-
import os, platform, subprocess, re, time, shutil, sys, signal, pickle

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
AddOption('--test', dest='test', type=None, nargs=0)

env = Environment()
test_opt = GetOption('test')
python_version = ARGUMENTS.get('python')

if python_version is None:
    with open('.sconsvars.pickle', 'rb') as f:
        python_version = pickle.load(f)
else:
    with open('.sconsvars.pickle', 'wb') as f:
        pickle.dump(python_version, f)

supported_python_versions = ['2.6', '2.7', '3.6', '3.7', '3.8']

if python_version not in supported_python_versions:
    raise AttributeError("Selected python version not supported. Build terminated.")
print("scons: Using python{}...".format(python_version))
SConscript(['checkers/SConscript', 'web/SConscript'], exports=['env', 'python_version', 'test_opt'] )

if GetOption('runserver') is not None:
    os.system('python{} build_web/manage.py runserver {}:{}'.format(str(python_version)[0], WEB_CLIENT_HOST, WEB_CLIENT_PORT))
