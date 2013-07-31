import fileinput

def dfs(v, dist):
	global furthest, furthest_, visited, A
	# base case
	if len(A[v]) == 1:
		if dist > furthest:
			furthest = dist
			furthest_ = [v]
		elif dist == furthest:
			furthest_ += [v]

	visited[v] = True
	for u in A[v]:
		if not visited[u]:
			dfs(u, dist+1)
	visited[v] = False

inp = [l.split() for l in fileinput.input()]
i = 0

while(i<len(inp)):
	N = int(inp[i][0])

	A = dict( (a,[]) for a in range(1,N+1))  # adjacencies

	visited = [False for a in range(N+1)]
	furthest_ = []
	for j in range(1,N):
		a = int(inp[i+j][0])
		b = int(inp[i+j][1])
		A[a] += [b]
		A[b] += [a]

	# Maximum height
	furthest = -float('inf')

	heads = []
	dfs(1,1)


	heads += furthest_
	
	furthest = -float('inf')
	dfs(furthest_[0],1)

	heads += [a for a in furthest_ if a not in heads]
	
	heads.sort()


	# Minimum height
	total = N
	while(total > 2):
		leafs = []
		for v in A:
			if len(A[v]) == 1:
				total -= 1
				leafs += [v]
		for l in leafs:
			A[A[l][0]].remove(l)  		# removes leaf from neighbours
			del A[l]				  	# removes leaf

	print 'Shortest:',
	for v in A:
		print v,
	print

	print 'Tallest:',
	for h in heads:
		print h,
	print

	i+=N
