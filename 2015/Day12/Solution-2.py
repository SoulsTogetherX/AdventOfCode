import re
import json

f = open("2015/Day12/input.txt","r")
string = f.read()
f.close()

def hook(obj):
  if "red" in obj.values():
    return {}
  else:
    return obj

stuff = str(json.loads(string, object_hook=hook))
print("The sum of all appearing non-red numbers is ", sum(map(int, re.findall("-?[0-9]+", stuff))))