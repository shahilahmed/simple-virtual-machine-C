def init_data 0
	sdata 500 Fizz edata
	sdata 512 Buzz edata
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
def main 0
	 call init_data
	 const 500
	 call puts
	 const 32
	 printchar
	 const 512
	 call puts
	 println
	 halt