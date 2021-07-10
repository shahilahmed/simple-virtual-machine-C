
def pattern 1
		ent 3
		const 0
		store local 0
		load argument 0
		store local 2
	pattern_label_0:
		load local 0
		load local 2
		lt
		brf pattern_label_3
		const 0
		store local 1
		pattern_label_1:
			load local 1
			load local 2
			lt
			brf pattern_label_2	
			load local 0
			load local 2
			mul
			load local 1
			add
			store global 512
			rload global 512
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
	sdata  0 #rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR edata
	const 8
	call pattern
	const 10
	printchar
	halt