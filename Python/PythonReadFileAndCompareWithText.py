textVec=[]
textVec.append("VINOTH,KIRUBA")
textVec.append("PAVAN KARTHI,NEWMEMBER")
textVec.append("GANESAN,BANU")

textVec2=[]


fd=open("Input.txt","r")
for x in fd.read().splitlines():
  textVec2.append(x)

if textVec2 == textVec:
    print("Same")
else:
    print("Different")
