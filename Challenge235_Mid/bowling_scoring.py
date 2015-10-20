#!/usr/bin/python

def isStrike(c):
  return len(c) == 1

def isSpare(c):
  return not isStrike(c) and c[1]=="/"

def getScore(n, i, tokens):
  if n == 0:
    return 0
  if isStrike(tokens[i]):
    return getScore(n-1, i+1, tokens) + 10
  elif isSpare(tokens[i]):
    if n == 2:
      return 10
    else:
      return int(tokens[i][0])
  else:
    if n == 2:
      return int(tokens[i][0]) + int (tokens[i][1])
    else:
      return int(tokens[i][0])
  
  
input1 = "X -/ X 5- 8/ 9- X 81 1- 4/X"
input2 = "62 71 X 9- 8/ X X 35 72 5/8"
line = input1
tokens = line.replace("-","0").split(" ")

score = 0
for i in range(0, len(tokens)-1):
  if isStrike(tokens[i]):
    score += getScore(2, i+1, tokens) + 10
  elif isSpare(tokens[i]):
    score += getScore(1, i+1, tokens) + 10
  else:
    score += int(tokens[i][0]) + int (tokens[i][1])

t = tokens[len(tokens)-1]
if(len(t) == 3):
  if isSpare(t):
    if(t[2] == "X"):
      score += 20
    else:
      score += 10 + int(t[2])
  else:
    if(t[2] == "X"):
      score += 20
    else: 
      score += 10 + int(t[2])
else: 
  score += int(tokens[i][0]) + int (tokens[i][1])

print score
