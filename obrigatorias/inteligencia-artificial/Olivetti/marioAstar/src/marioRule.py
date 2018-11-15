#!/usr/bin/env python
# marioRule.py
# Author: Fabrício Olivetti de França
#
# Agente baseado em regras para o SMW

import sys
import retro

import numpy as np
from numpy.random import uniform, choice, random
import pickle
import os
import time
from rominfo import *
#from utils import *

radius = 6

def dec2bin(dec):
    binN = []
    while dec != 0:
        binN.append(dec % 2)
        dec = dec / 2
    return binN

def printState(state):
    state_n = np.reshape(state.split(','), (2*radius + 1, 2*radius + 1))  
    _=os.system("clear")
    mm = {'0':'  ', '1':'$$', '-1':'@@'}
    for i,l in enumerate(state_n):
      line = list(map(lambda x: mm[x], l))
      if i == radius + 1:
        line[radius] = 'X'
      print(line) 

def getRam(env):
    ram = []
    for k, v in env.data.memory.blocks.items():
        ram += list(v)
    return np.array(ram)
    
def rule():
  env = retro.make(game='SuperMarioWorld-Snes', state='YoshiIsland1', players=1)
  env.reset()
  
  total_reward = 0
  long_jump = False

  while not env.data.is_done():
    ram = getRam(env)
    
    state, x, y = getInputs(ram)
    printState(getState(ram, radius)[0])

    state_mtx = np.reshape(state, (2*radius + 1, 2*radius + 1))
    

    
    if long_jump==True:
      ob, rew, done, info = env.step(dec2bin(131))
      total_reward += rew
      ob, rew, done, info = env.step(dec2bin(131))
      total_reward += rew
      long_jump = False
    else:
      if state_mtx[7,9]==-1 or state_mtx[7,8]==-1:
        ob, rew, done, info = env.step(dec2bin(384))
        total_reward += rew
      elif state_mtx[5,11] == -1:
        ob, rew, done, info = env.step(dec2bin(130))
        total_reward += rew
      elif state_mtx[5,9]==-1 or state_mtx[5,8]==-1:
        if state_mtx[4,9]==-1 or state_mtx[4,8]==-1:
          ob, rew, done, info = env.step(dec2bin(128))
          total_reward += rew
        else:
          ob, rew, done, info = env.step(dec2bin(131))
          total_reward += rew
          long_jump = True
      else:
        ob, rew, done, info = env.step(dec2bin(128))
        total_reward += rew
      env.render()
      print(info)
  return total_reward

def main():
  r = rule()
    
if __name__ == "__main__":
  main()  
