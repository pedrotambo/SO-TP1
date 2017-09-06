#!/usr/bin/python

import os
import sys
import subprocess

#cecesito la misma cantidad de archivos como la cantidad máxima de threads que vaya a usar

#ACA CREADOR DE ARCHIVOS (siguiendo además aclaraciones de abajo)

#Exp1: creo X (por ahora 8,16) corpus con todas las palabras distintas entre si
#Exp2: doy corpus (original) como tantos threads tenga
#Exp3: aleatorios como tantos threads tenga
#Exp4: todas palabras que empiezen con la mista letra (sumar la letra a cada random?)

#creo las rutas de archivos a pasarles

archivosExp2 = ''
for _ in range(0,16):
	archivosExp2 = archivosExp2 + ' ' + 'corpus'

for i in range(1,16+1):
	subprocess.call(['./test-6 '+'count_words_c '+str(i)+archivosExp2+'  >> ./resultados/count_words_c_Exp2.csv'],shell = True)

for i in range(1,16+1):
	subprocess.call(['./test-6 '+'count_words_ct '+str(i)+archivosExp2+'  >> ./resultados/count_words_ct_Exp2.csv'],shell = True)

for i in range(1,16+1):
	subprocess.call(['./test-6 '+'maximum '+str(i)+' '+str(i)+archivosExp2+'  >> ./resultados/maximum_Exp2.csv'],shell = True)

for i in range(1,16+1):
	subprocess.call(['./test-6 '+'maximum_cw_c '+str(i)+' '+str(i)+archivosExp2+'  >> ./resultados/maximum_cw_c_Exp2.csv'],shell = True)

for i in range(1,16+1):
	subprocess.call(['./test-6 '+'maximum_cw_ct '+str(i)+' '+str(i)+archivosExp2+'  >> ./resultados/maximum_cw_ct_Exp2.csv'],shell = True)
