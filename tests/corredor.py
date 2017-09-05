#!/usr/bin/python

import os
import sys
import random
import subprocess



for i in range(1,100+1):
	subprocess.call(['./test-6 '+'count_words_c '+str(i)+' corpus corpus corpus corpus  >> ./resultados/juab.csv'],shell = True)