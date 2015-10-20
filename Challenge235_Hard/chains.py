#!/usr/bin/python

f = open("input")
f.readline()

pic = []
for line in f:
  pic.append(list(line[:-1]))
f.close()

start_pt = ()
for i in range(len(pic)):
  for j in range(len(pic[i])):
    if pic[i][j] == 'x':
      start_pt = (i,j) 
      break
  if start_pt:
    break

num_chain = 1
pic[i][j] = num_chain
stack = list()
stack.append(start_pt)

def inRangei(i, pic):
  return i>=0 and i<len(pic)

def inRangej(j, pic):
  return j>=0 and j<len(pic[0])

def containsX(i, j, pic):
  return pic[i][j] == 'x'

def checkAndAdd(i, j, pic, x_list):
  if inRangei(i, pic) and inRangej(j, pic):
    if containsX(i, j, pic):
      x_list.append((i,j))

while stack:
  pt  = stack.pop(0)
  i = pt[0]
  j = pt[1]

  x_list = []
  checkAndAdd(i-1, j, pic, x_list)
  checkAndAdd(i+1, j, pic, x_list)
  checkAndAdd(i, j-1, pic, x_list)
  checkAndAdd(i, j+1, pic, x_list)

  for index in range(len(x_list)):
    if index == 0:
      pic[ x_list[index][0] ] [ x_list[index][1] ] = pic[i][j]
    else:
      num_chain += 1
      pic[ x_list[index][0] ] [ x_list[index][1] ] = num_chain
    stack.append(x_list[index])
 
print "number of chains:", num_chain
