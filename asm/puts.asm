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
		ne 
		brf puts_label_1
		rload local 0
		printchar
		load  local 0
		const 1
		add
		store local 0
		br puts_label_0
	puts_label_1:	
		ret
def main 0
	 call init_data
	 const 500
	 call puts
	 const 32
	 printchar
	 const 500
	 call puts
	 const 10
	 printchar
	 halt