# -*- mode: Python; -*-
import os, platform, subprocess, re, time, ConfigParser, shutil, sys, signal

MYAPP_VER_MAJOR = '0'
MYAPP_VER_MINOR = '03'

WEB_SRV_PREFIX = 'srvmyapp'
WEB_SRV_HOST = '127.0.0.1'
WEB_SRV_PORT = '50007'
WEB_CLIENT_HOST = '192.168.1.10'#127.0.0.1
WEB_CLIENT_PORT = '8001'


Export('MYAPP_VER_MAJOR MYAPP_VER_MINOR')
Export('WEB_SRV_PREFIX WEB_SRV_HOST WEB_SRV_PORT WEB_CLIENT_HOST WEB_CLIENT_PORT')

vars = Variables('custom.py')

env = Environment(variables=vars)

SConscript(['checkers/SConscript', 'web/SConscript'], exports=['env'] )

