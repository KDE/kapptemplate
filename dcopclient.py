# dcopclient.py
#
# This is a python script that can demonstrate the "scripting" ability
# of even a very simple app.  If you create a framework with
# kapptemplate and compile and run it, it will automatically be a dcop
# server.  Just run this script and watch what happens :-)
#
# You need the xmlrpc library from http://www.pythonware.com
#
# Kurt Granroth <granroth@kde.org>
#!/usr/bin/python

from xmlrpclib import *
import os

rc = open(os.environ['HOME'] + '/.kxmlrpcd', 'r')
config = string.split(rc.read(), ',')
port = config[0]
auth = config[1]

server = Server("http://localhost:" + port +"/kmyapp")

server.KMyAppIface.openURL(auth, "http://www.kde.org")
