#-*- coding: utf-8 -*-
import glob
import os
filelist = glob.glob("*.txt")
totala=0
totalb=0
totalc=0
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
	totala += counta
	totalb += countb
	totalc += countc
print "현재 폴더 : ", os.getcwd()
print "total글자수 : ", totala, " total단어수 : ", totalb, " total라인수 : ", totalc

