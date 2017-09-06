#!/usr/bin/python

import random
from random_words import RandomWords


#crea un array con palabras random (en inglés).
#n es la cantidad de palabras a considerar, m es la cantidad de palabras a tomar.
#ejemplo: si n=5 y m=10, tendremos que elegir 10 palabras de las 5 encontradas, osea, repitiendo palabras
def armador(n,m):
	palabras = []
	for _ in range(1,n+1):
		rw = RandomWords()
		word = rw.random_word()
		palabras.append(word)

	res = []
	for _ in range(1,m+1):
		secure_random = random.SystemRandom()
		res.append(secure_random.choice(palabras))

	return res

#toma un array de palabras, y les agrega la letra l adelante
def normalizador(l, res):
	for i in range(0,len(res)):
		res[i] = l+res[i]


#imprime un array de palabras como necesita el input del programa
def impresor(res):
	for i in range(0,len(res)):
		print(res[i])


if __name__ == '__main__':
	armador()
	normalizador()
	impresor()