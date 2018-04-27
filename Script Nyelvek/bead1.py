import io
inputfile = io.open("data","r", encoding="utf-8")
updatefile = io.open("update","r", encoding="utf-8")
outfile = io.open("newdata","w", encoding="utf-8")
adatok = {}
for line in inputfile:
    tmp = line.split(";")
    tmp2 = tmp[0].split(".")
    OrdNum = int(tmp2[0])
    Name = tmp2[1].lstrip()
    Desc = tmp[1].lstrip()
    Price = int(tmp[2])
    adatok[OrdNum] = [Name, Desc, Price]

for line in updatefile:
    tmp = line.split(";")
    tmp2 = tmp[0].split(".")
    OrdNum = int(tmp2[0])
    if OrdNum in adatok:
                 if tmp2[1].strip() == 'visszavon':
                     del adatok[OrdNum]
                 else:
                     adatok[OrdNum][2] = int(tmp2[1])
    else:
                 Name = tmp2[1].lstrip()
                 Desc = tmp[1].lstrip()
                 Price = int(tmp[2])
                 adatok[OrdNum] = [Name, Desc, Price]

for i in adatok:
    tmp1 = str(i) + ". " + adatok[i][0] + "; " + adatok[i][1] + "; " + str(adatok[i][2])
    outfile.write(tmp1 + "\n")
outfile.close()
