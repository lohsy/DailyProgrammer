#!/usr/bin/python

def is_prime(number):
  if(number == 1):
    return False
  for i in range(2, number):
    if(number%i == 0):
      return False
  return True

def find_prime_factors (number):
  prime_factors = []
  for i in range(1, number+1):
    if number%i==0 and is_prime(i):
      prime_factors.append(i)
  return prime_factors

fp=open("input2")
fp.readline()

for line in fp:
  numbers = map(int, line.replace("(", "").replace(")","").split(","))
  primes1 = find_prime_factors(numbers[0])
  primes2 = find_prime_factors(numbers[1])
  if(sum(primes1) == sum(primes2)):
    print line.rstrip() , "VALID"
  else:
    print line.rstrip() , "NOT VALID"
 
