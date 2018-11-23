#coding: utf-8

'''
Nome: Iago Richard - R.A: 21038514
Link do desafio: https://www.logic-puzzles.org/game.php?u2=d14cfb8ac2fec5b0c681d8ad26b7145a
'''

from itertools import product

animal   = ['leopard', 'bear', 'orangutan', 'tortoise']
month    = ['March', 'April', 'May', 'June']
magazine = ['Animal Science', 'Nature Monthly', 'The Geographer', 'Wildzone']

#1ª restrição: A foto tirada em abril foi a foto do leopardo da neve ou a foto publicada pela Wildzone.
def res1(combination):

	if combination[2] == 'April' and (combination[0] != 'leopard' or combination[1] != 'Wildzone'):
		return False
	elif combination[2] != 'April':
		return True
	else:
		return True
	
#4ª restrição:A foto do urso polar foi publicado pelo The Geographer.
def res4(combination):
	if combination[0] == 'bear' and combination[1] != 'The Geographer':
		return False
	elif combination[1] == 'The Geographer' and combination[0] != 'bear':
		return False
	else:
		return True

#5º restrição: A foto da tartaruga gigante foi publicado pela Nature Monthly.
def res5(combination):
	if combination[0] == 'tortoise' and combination[1] != 'Nature Monthly':
		return False
	elif combination[1] == 'Nature Monthly' and combination[0] != 'tortoise':
		return False
	else:
		return True
		
#Restrições 2 e 3
#2. A foto publicada pelo The Geographer foi tirada 1 mês após a foto publicada pela Wildzone.
#3. O tiro publicado pela Nature Monthly foi feito 2 meses após a foto publicada pela Wildzone.
def res(combination):
	if combination[1] == 'Wildzone' and (combination[2] == 'April' or combination[2] == 'March'):
		return True
	elif combination[1] == 'The Geographer' and (combination[2] == 'April' or combination[2] == 'May'):
		return True
	elif combination[1] == 'Nature Monthly' and (combination[2] == 'May' or combination[2] == 'June'):
		return True
	elif combination[1] == 'Animal Science' and (combination[2] == 'March' or combination[2] == 'June'):
		return True
	else:
		return False
		
		
def filtrar(combinations):
	c1 = list(filter(res1, combinations))
	c2 = list(filter(res4, c1))
	c3 = list(filter(res5, c2))
	c4 = list(filter(res, c3))
	
	return c4
	
def separa_animais(x):
	l = [y for y in x if y[0] == 'leopard'] 
	b = [y for y in x if y[0] == 'bear'] 
	o = [y for y in x if y[0] =='orangutan'] 
	t = [y for y in x if y[0] == 'tortoise'] 
		
	return l, b, o, t
	
def solucao(combination):

	r = [y[1] for y in combination]
	m = [y[2] for y in combination]
	
	if len(set(m)) == len(m) and len(set(r)) == len(r):
		return True
	else:
		return False

def resposta():
	combinations = list (product (animal, magazine, month))
	x = filtrar(combinations)
	l, b, o, t = separa_animais(x)

	combinations2 = list (product (l,b,o,t))
	y = list (filter(solucao, combinations2))
	y = y[0]
	
	print ("Resposta: ")
	for i in y:
		print (i[0]," - ", i[1]," - ", i[2])

def main():
	resposta()

main()





