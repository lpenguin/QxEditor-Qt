#!/usr/bin/python

import os
import glob
import json
import re

path = './quests/'
res = {"quests":[]}
of = open('quests.json', "w")
for file in glob.glob( os.path.join( path, "*.json" ) ):
    name = os.path.basename(file).replace(".json", "")
    name = name[0:1].upper()+name[1:]
    res["quests"].append({"name" : name, "url" : file})
res["quests"] = sorted(res["quests"], key=lambda quest: quest["name"])
json.dump( res , of )

