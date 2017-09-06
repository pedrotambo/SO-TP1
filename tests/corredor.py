#!/usr/bin/python

import os
import sys
import subprocess

#cecesito la misma cantidad de archivos como la cantidad máxima de threads que vaya a usar

#ACA CREADOR DE ARCHIVOS (siguiendo además aclaraciones de abajo)

#Exp1: creo X (por ahora 100,200) corpus con todas las palabras distintas entre si
#Exp2: doy corpus (original) como tantos threads tenga
#Exp3: aleatorios como tantos threads tenga
#Exp4: todas palabras que empiezen con la mista letra (sumar la letra a cada random?)

#creo las rutas de archivos a pasarles
archivosExp1 = ''
for file in sorted(os.listdir('./exp1')):
	archivosExp1 = archivosExp1 + ' ' + str(file)

archivosExp2 = ''
for _ in range(0,16):
	archivosExp2 = archivosExp2 + ' ' + 'corpus'

archivosExp3 = ''
for file in sorted(os.listdir('./exp3')):
	archivosExp3 = archivosExp3 + ' ' + str(file)

archivosExp4 = ''
for file in sorted(os.listdir('./exp4')):
	archivosExp4 = archivosExp4 + ' ' + str(file)


#corro los tests, puse una copia del ejecutable en cada expi para que pueda ejecutar la lista de archivos facilmente

for i in range(1,100+1):
	subprocess.call(['./exp1/test-6 '+'count_words_c '+str(i)+' '+archivosExp1+' >> ../resultados/count_words_c_Exp1.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp2/test-6 '+'count_words_c '+str(i)+' '+archivosExp2+'  >> ../resultados/count_words_c_Exp2.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp3/test-6 '+'count_words_c '+str(i)+' '+archivosExp3+'  >> ../resultados/count_words_c_Exp3.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp4/test-6 '+'count_words_c '+str(i)+' '+archivosExp4+'  >> ../resultados/count_words_c_Exp4.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp1/test-6 '+'count_words_ct '+str(i)+' '+archivosExp1+' >> ../resultados/count_words_ct_Exp1.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp2/test-6 '+'count_words_ct '+str(i)+' '+archivosExp2+'  >> ../resultados/count_words_ct_Exp2.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp3/test-6 '+'count_words_ct '+str(i)+' '+archivosExp3+'  >> ../resultados/count_words_ct_Exp3.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp4/test-6 '+'count_words_ct '+str(i)+' '+archivosExp4+'  >> ../resultados/count_words_ct_Exp4.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp1/test-6 '+'maximum '+str(i)+' '+archivosExp1+' >> ../resultados/maximum_Exp1.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp2/test-6 '+'maximum '+str(i)+' '+archivosExp2+'  >> ../resultados/maximum_Exp2.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp3/test-6 '+'maximum '+str(i)+' '+archivosExp3+'  >> ../resultados/maximum_Exp3.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp4/test-6 '+'maximum '+str(i)+' '+archivosExp4+'  >> ../resultados/maximum_Exp4.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp1/test-6 '+'maximum_cw_c '+str(i)+' '+archivosExp1+' >> ../resultados/maximum_cw_c_Exp1.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp2/test-6 '+'maximum_cw_c '+str(i)+' '+archivosExp2+'  >> ../resultados/maximum_cw_c_Exp2.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp3/test-6 '+'maximum_cw_c '+str(i)+' '+archivosExp3+'  >> ../resultados/maximum_cw_c_Exp3.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp4/test-6 '+'maximum_cw_c '+str(i)+' '+archivosExp4+'  >> ../resultados/maximum_cw_c_Exp4.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp1/test-6 '+'maximum_cw_ct '+str(i)+' '+archivosExp1+' >> ../resultados/maximum_cw_ct_Exp1.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp2/test-6 '+'maximum_cw_ct '+str(i)+' '+archivosExp2+'  >> ../resultados/maximum_cw_ct_Exp2.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp3/test-6 '+'maximum_cw_ct '+str(i)+' '+archivosExp3+'  >> ../resultados/maximum_cw_ct_Exp3.csv'],shell = True)

for i in range(1,100+1):
	subprocess.call(['./exp4/test-6 '+'maximum_cw_ct '+str(i)+' '+archivosExp4+'  >> ../resultados/maximum_cw_ct_Exp4.csv'],shell = True)
