import sys, io
if len(sys.argv)<4:
    print("Three parameters are needed!")
else:
    try:
        inp1 = io.open(sys.argv[1],"r", encoding="utf-8")
        inp2 = io.open(sys.argv[2],"r", encoding="utf-8")
        out = io.open(sys.argv[3],"w", encoding="utf-8")
        csere = []
        modify = []
        for line in inp1:
            temp = line.split("::")
            csere.append(temp[0].strip())
            modify.append(temp[1].strip())
        for line in inp2:
            temp = line.replace('.',' ').split(" ")
            outsor = " "
            for i in xrange(len(temp)):
                temp2 = temp[i].lower()
                if temp2 in csere:
                    outsor += modify[csere.index(temp2)]
                else:
                    outsor += temp2
                outsor += " "
            outsor = outsor.strip().capitalize()
            out.write(outsor+".\n")
        out.close()        
    except IOError, err :
        print("Wrong file name!")
