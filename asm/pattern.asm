
def pattern 1
		ent 3
		const 1
		store local 0
		load argument 0
		store local 2
	pattern_label_0:
		load local 0
		load local 2
		le
		brf pattern_label_3
		const 1
		store local 1
		pattern_label_1:
			load local 1
			load local 0 
			le
			brf pattern_label_2	
			load global 0
			printchar
			const 32
			printchar
			load local 1
			const 1
			add
			store local 1
			br pattern_label_1
		pattern_label_2:
			const 10
			printchar
			load local 0
			const 1
			add
			store local 0
			br pattern_label_0
	pattern_label_3:
		const 10
		printchar
		ret		
def main 0
	sdata 0 #* edata
	const 8
	call pattern
	const 10
	printchar
	halt