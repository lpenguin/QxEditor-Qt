#!/usr/bin/python

import os
import glob
import sys
import ConfigParser
import MySQLdb


#Reading config
directory = os.path.dirname(__file__)

config = ConfigParser.ConfigParser()
config.read(directory+'/settings.cfg')

editor = config.get("main", "editor")

host = config.get('dbase', 'host')
user = config.get('dbase', 'user')
password = config.get('dbase', 'password')
dbname = config.get('dbase', 'db')

#connecting to db
db = MySQLdb.connect(host=host, user=user, passwd=password, db=dbname)
cursor = db.cursor()

def execSql( sql ):
    cursor.execute( sql )
    db.commit()
    
def addQuest(name, path):
    sql = "insert into quests (name, path) values ('%s', '%s')" % (name, path)
    execSql( sql )


def deleteQuest(name):
    sql = "delete from quests where name = '%s'" % name
    execSql( sql )

def convertQuests(qmdir, jsondir):
    for qmfile in glob.glob( os.path.join( qmdir, "*.qm" ) ):
        print qmfile
        jsonfile = os.path.join( jsondir, os.path.basename(qmfile) )
        jsonfile = jsonfile.replace(".qm", ".json").lower()
        print "Converting %s to %s..." % (qmfile, jsonfile)
        os.system("%s --convert %s %s" % (editor, qmfile, jsonfile) )
        
        
#Reading commaind line arguments

if len(sys.argv) == 1:
    print "No arguments. Exiting..."
    sys.exit(0)
    
arg1 = sys.argv[1]
if arg1 == "add":
    path = ""
    name = sys.argv[2]
    if len( sys.argv ) == 3:
        path = name
        name = os.path.basename( name )
        name = name.replace(".json", "")
    else:
        path = sys.argv[3]
    addQuest(name, path)
    print "Quest %s added" % name
    sys.exit(0)
    
if arg1 == "delete":
    name = sys.argv[2]
    deleteQuest( name )
    print "Quest %s deleted" % name
    sys.exit(0)

if arg1 == "convert":
    qmdir = sys.argv[2]
    jsondir = sys.argv[3]
    convertQuests( qmdir, jsondir )
    sys.exit(0)

    

