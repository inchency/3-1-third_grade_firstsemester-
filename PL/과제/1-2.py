#-*- coding: utf-8 -*-
import glob
filelist = glob.glob("*.txt")
totala=0
totalb=0
totalc=0
for i in filelist:
	f=open(i,'r')
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
	totala += counta
	totalb += countb
	totalc += countc
	

	
print "total글자수 : ", totala, " total단어수 : ", totalb, " total라인수 : ", totalc
