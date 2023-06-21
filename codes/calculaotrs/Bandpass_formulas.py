#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed May 31 11:29:24 2023

@author: IsmailYehia
"""

import numpy as np

def fre(r1, r2, c1, c2):
    return 1 / (2*np.pi * ((r1*r2*c1*c2)**0.5))

def Qbp(r1,r2):
    return 0.5* ((r2/r1)**0.5)

def gain(q):
    return -2*(q**2)

r1 = 19
r2 = 330
c1 = 1*10**-6
c2 = 1*10**-6

f = fre(r1, r2, c1, c2)
q = Qbp(r1,r2)
g = gain(q)
print('frequecy:')
print(f)
print('Q:')
print(q)
print('gain:')
print(g)