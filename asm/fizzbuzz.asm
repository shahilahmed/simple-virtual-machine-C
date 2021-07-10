def init_data 0
	sdata 500 #Fizz edata
	sdata 512 #Buzz edata
	ret
def puts 1
		ent 1
		load argument 0
		store local 0
	puts_label_0:	
		rload local 0
	    const 0
		if ne puts_label_1
		rload local 0
		printchar
		inc local 0
		br puts_label_0
	puts_label_1:	
		ret
def fizzbuzz 1
		ent 3
		const 1
		store local 0
		load argument 0
		store local 1
		const 0
		store local 2
	fizzbuzz_label_0:	
		load local 0
		load local 1
		if le fizzbuzz_label_4
		const 0
		store local 2		
		load local  0
		const 3
		mod
		not
		brf fizzbuzz_label_1
		const 1
		store local 2
		const 500
		call puts
		printspace
	fizzbuzz_label_1:
		load local 0
		const 5
		mod
		not
		brf fizzbuzz_label_2
		const 1
		store local 2
		const 512
		call puts
		printspace
	fizzbuzz_label_2:
		load local 2
		const 1
		eq
		brt fizzbuzz_label_3
		load local 0
		print
	fizzbuzz_label_3:	
		println
		inc local 0
		br fizzbuzz_label_0
	fizzbuzz_label_4:	
		println	
		ret	
def main 0
	 call init_data
	 const 100
	 call fizzbuzz
	 println
	 halt