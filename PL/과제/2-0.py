#-*- coding: utf-8 -*-
import os
import glob
import subprocess

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
        lines = fr.readlines()
        words=[]
        for line in lines:
            words += line.split()
        for word in words:
            fw.write(word+"\n")
        
NOTEPAD_PATH = "c:/windows/system32/notepad.exe" #여기가 메모장프로그램 위치입니다
fileList = glob.glob("*")
fw=open("all.txt", 'w')
search(os.getcwd())
fw.close()

try:
    subprocess.call([NOTEPAD_PATH, 'all.txt'])  #만약 메모장이 실행시켜지지 않으면 위에 notepad.exe가 있는 경로를 수정해 주세요.
except:
    fo = open("all.txt", 'r')
    reads = fo.readlines()
    for read in reads:
        print(read)
    fo.close()
    
    print "\n\n\n현재 폴더에 모든 txt파일을 합친 all.txt파일이 생성되었습니다. all.txt파일을 열어 확인해 보세요."
