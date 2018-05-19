import glob, os, io

files = []

def CreateFunc(str):
    vissza=[]
    tmp=str[:str.find('{')]
    arg=str[str.find('{'):]
    if "CIKLUS" in tmp:
        vissza.append("for"+tmp.lstrip("CIKLUS").rstrip()+" :")
    else:
        vissza.append("if"+tmp.lstrip("ELAGAZAS").rstrip()+" :")
    val = arg.split(";;")
    tmp = []
    for i in val:
        if ("CIKLUS" in i or "ELAGAZAS" in i):
            tmp+=CreateFunc(i)
        else:
            tmp.append(i.replace('}','').replace('{',''))
    tmp = [' '*4 + szo for szo in tmp]
    vissza += tmp
    return vissza

for file in glob.glob("*.prog"):
    files.append(file)

for i in files:
    inp = io.open(i,"r",encoding="utf-8")
    fname=i.rstrip(".prog")+".py"
    ki = io.open(fname,"w",encoding="utf-8")
    for line in inp:
        if line[0].isupper():
            temp = CreateFunc(line)
        else:
            temp=line.split(";;")
        ki.write("\n".join(temp))