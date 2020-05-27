# modified-walksat

A C++ implementation of Modified WalkSAT algorithm.

## Modified WalkSAT Algorithm

<pre>
<b>Require:</b> n, m: The number of variables and clauses.
<b>Require:</b> C: The set of clauses (in DIMACS format).
<b>Require:</b> p ∈ (0, 1): The probability of flipping.
<b>Require:</b> maxit: Maximum number of assigments to be tried in each run. 
<b>Require:</b> maxv: Maximum number of variables to be simultaneously flipped.
1. M←Random(domain=[0,1],length=n) 
2. v←0
3. while v ≤ maxv do
4. 	v←v+1
5. 	while maxit > 0 do
6. 		maxit ← maxit − 1
7. 		if Satisfies(M, C) then
8. 			return M 
9.    		end if
10.   		S ←FindVariablesInFalseClauses(C) 
11.   		if Random() ≥ p then
12.     		M ←FlipVariables(M,S,v) 
13.   		else
14.     		M ←FindMinConflictingVVars(M,C,v) 
15.   		end if
16.   	end while 
17. end while 
18. return Failure
</pre>

## Instructions to Run

Option 1 - Run the shell script WalkSAT.sh
```bash
./WalkSAT.sh
```

Option 2 - Open Terminal and issue following commands:
```bash
g++ WalkSAT.cpp -o WalkSAT
./WalkSAT
```
