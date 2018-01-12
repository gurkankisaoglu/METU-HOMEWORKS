import random
def hyphenate(s):
	pivot=0
	subpivot=0
	vowels=["a","e","i","I","o","O","U","u"]
	hyphens=[]
	for pivot in range(len(s)):
		if len(s[pivot:])==1:
			hyphens.append(s[subpivot:])
			break
		if s[pivot] in vowels:
			pivot+=1
			if len(s[pivot:])==1 and s[pivot] not in vowels:
				hyphens.append(s[subpivot:])
				break
			if s[pivot] in vowels:
				hyphens.append(s[subpivot:pivot])
				subpivot=pivot	
			if s[pivot] not in vowels:
				pivot+=1
				if len(s[pivot:])==1 and s[pivot] not in vowels:
					hyphens.append(s[subpivot:pivot])
					break
				if s[pivot] in vowels:
					hyphens.append(s[subpivot:pivot-1])
					subpivot=pivot-1
				if s[pivot] not in vowels:
					pivot+=1
					if len(s[pivot:])==1 and s[pivot] not in vowels:
						hyphens.append(s[subpivot:])
						break
					if s[pivot] in vowels:
						hyphens.append(s[subpivot:pivot-1])
						subpivot=pivot-1
					pivot-=1
		else:		
			continue
	return hyphens
		
def give_me_most_freq_syllable(dic,syllable):
	value_list=dic[syllable].values()
	most_freq_number=max(value_list)
	freq_of_most_freq=value_list.count(most_freq_number)
	list_keys=[]

	if syllable==".":
		list_keys=dic[" "].keys()+dic["."].keys()
		randomkey=random.choice(list_keys)
		return randomkey

	elif len(value_list)==1:
		list_keys=dic[syllable].keys()
		return list_keys[0]

	elif len(value_list)==2:
		list_keys=dic[syllable].keys()
		randomint=random.randint(0,1)
		return list_keys[randomint]

	elif freq_of_most_freq>=2:
		for key,value in dic[syllable].iteritems():
			if value==most_freq_number:
				list_keys.append(key)
		randomint=random.randint(0,freq_of_most_freq-1)
		return list_keys[randomint]			

	elif freq_of_most_freq<2:
		for key,value in dic[syllable].iteritems():
			if value==most_freq_number:
				list_keys.append(key)
				y=value_list.index(most_freq_number)
		del value_list[y]
		most_freq_number=max(value_list)
		for key,value in dic[syllable].iteritems():
			if value==most_freq_number:
				list_keys.append(key)
		randomint=random.randint(0,len(list_keys)-1)
		return list_keys[randomint]

def execute():
	syllables=[" "]
	dic={}	
	outputlist=[]
	outputtext=""

	while True:
		line=raw_input()
		if line=="=":
			break
		else:
			words=line.split(" ")			
			for word in words:
				if word.endswith(".") and word.count(".")==1:
					syllables+=hyphenate(word[:-1])
					syllables+=["."]
				elif "." in word :
					if word.endswith("."):				
						wordlist=word.split(".")
						for m in range(len(wordlist)):
							syllables+=hyphenate(wordlist[m])
							syllables+=["."]
							syllables.pop()					
					else:
						wordlist=word.split(".")
						for m in range(len(wordlist)):
							syllables+=hyphenate(wordlist[m])
							syllables+=["."]
							syllables.pop()							
							syllables+=[" "]				

				else:
					syllables+=hyphenate(word)
					syllables+=[" "]	


	n=int(syllables[1])
	m=int(syllables[3])
	del syllables[0]
	del syllables[0]
	del syllables[0]
	del syllables[0]			

	for j in range(len(syllables)-1):
		dic.setdefault(syllables[j],{})
	for i in range(len(syllables)-1):
		if syllables[i+1] in dic[syllables[i]]:
			dic[syllables[i]][syllables[i+1]]+=1
		elif syllables[i+1] not in dic[syllables[i]]:
			dic[syllables[i]].setdefault(syllables[i+1],1)	
	del syllables[0]	

	if "." not in dic.keys():
		list_keys0=dic[" "].keys()
	else:
		list_keys0=dic[" "].keys()+dic["."].keys()
	first_syllable=random.choice(list_keys0)
	outputlist=outputlist+[first_syllable]
	outputtext="".join(outputlist)			

	while True:
		next_syllable=give_me_most_freq_syllable(dic,outputlist[-1])
		outputlist=outputlist+[next_syllable]
		outputtext+="".join(outputlist[-1])
		a=outputtext.count(" ")
		b=outputtext.count(".")
		wordnumber=a+b
		charnumber=len(outputtext)
		if charnumber>m or wordnumber>n:
			print outputtext			
			break
