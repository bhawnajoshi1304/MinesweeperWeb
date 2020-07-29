from flask import Flask, redirect, url_for, render_template
from random import random
app = Flask(__name__,static_url_path='/static')


def count(b,i,j):
    count=0
    if i>0:
        if b[i-1][j]=="mine":
            count+=1
        if j>0:
            if b[i-1][j-1]=="mine":
                count+=1
        if j<8:
            if b[i-1][j+1]=="mine":
                count+=1
    if i<8:
        if b[i+1][j]=="mine":
            count+=1
        if j>0:
            if b[i+1][j-1]=="mine":
                count+=1
        if j<8:
            if b[i+1][j+1]=="mine":
                count+=1    
    if j>0:
        if b[i][j-1]=="mine":
            count+=1
    if j<8:
        if b[i][j+1]=="mine":
            count+=1
    return str(count)

def designBoard():
    c=10
    rboard = [["0" for i in range(9)] for i in range(9)]
    while(c!=0):    
        i=int(random()*9)
        j=int(random()*9)
        if rboard[i][j]=="0":
            c-=1
            rboard[i][j]="mine"
    for i in range(9):
        for j in range(9):
            if rboard[i][j]=="0":
                rboard[i][j]=count(rboard,i,j)
    return rboard

@app.route("/")
def home():
    return render_template("index.html",title="Welcome to Minesweeper")

@app.route("/login")
def admin():
    return render_template("index.html",title="true")

@app.route("/play")
def play():
    rboard=[]
    rboard=designBoard()
    return render_template("play.html",rboard=rboard)

@app.route("/<name>")
def menu(name):
    return render_template("index.html",title=name)
        
if __name__ == "__main__":
    app.run()