-good looking images for each eval sheet point
-separate bonus from mandatory (also specular)
-test all possible wrong inputs (make a collection of everything that can go wrong)
-check leaks again to be 10000000% sure
- ✅if any other than  C L sp etc then ERROR
- ✅if BONUS 0 only 1 L
- ✅when parsing colors, atoi, value must be >=0 and <=255
- ✅positive reads diameter etc.
- ✅check in parsing which ones have to be normalized and which not
- ✅check get length function as to be normalized and have 1
- there should be at least 1 camera check sheet !

- free_split_arr(d); why no leaks without it??
- check leaks in linux too!

- ✅SEE
	wrong problem intentified in last commit ->  the initial parse should work but the with the translation and transformation changes! check it

	the problem is i use the same function to do the parsing change it myself.