#-*- coding: utf-8 -*-
import glob
import os

def search(dirname):
    flist = os.listdir(dirname)
    for f in flist:
        next = os.path.join(dirname, f)
        if os.path.isdir(next):
            search(next)
        else:
            doFileWork(next)
def doFileWork(filename):
    ext = os.path.splitext(filename)[-1]
    if ext == ".txt":
        fr=open(filename, 'r')
        print filename, " : "
        lines = fr.readlines()
        countaa=0
        countbb=0
        countcc=0
        words=[]
        for line in lines:
            words += line.split()
            countcc+=1
        for word in words:
            countbb+=1
            countaa+=len(word)
        print "글자수 : ", countaa
        print "단어수 : ", countbb
        print "라인수 : ", countcc
        fr.close()
        
filelist = glob.glob("*.txt")
print "지금은 현재폴더 내의(", os.getcwd(), ").txt파일 입니다.\n"
for i in filelist:
	f=open(i,'r')
	print i," : "
	lines = f.readlines()
	counta=0
	countb=0
	countc=0
	word=[]
	for line in lines:
		word+=line.split()
		countc+=1
	for j in word:
		countb+=1
		counta+=len(j)
	print "글자수 : ", counta
	print "단어수 : ", countb
	print "라인수 : ", countc
	f.close()

print "\n\n\n\n이제부터 하위폴더 내의 .txt파일을 검사합니다. 폴더 경로를 포함합니다.\n"
k = os.listdir(os.getcwd())
for l in k:
        n = os.path.join(os.getcwd(), l)
        if os.path.isdir(n):
                search(n)
