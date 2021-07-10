def fact 1
		load argument 0
		const 1
		if le fact_label_0
		const 1
		ret
	fact_label_0:	
		load argument 0
		load argument 0
		const 1
		sub
		call fact
		mul
		ret		
def main 0
	ent 3
	const 4
	call fact
	store local 0
	const 6
	call fact
	store local 1
	load  local 0
	load  local 1
	add
	store global  2
	load  global  2
	print
	println
	halt