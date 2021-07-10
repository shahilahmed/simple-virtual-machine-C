def fact 1
		load argument 0
		const 1
		le 
		brf fact_label_0
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
def pow 2
		load argument 0
		const 0
		le 
		brf pow_label_0
		const 1
		ret
	pow_label_0:	
		load argument 1
		load argument 1
		load argument 0
		const 1
		sub
		call pow
		mul
		ret
def main 0
		ent 14
		const  0
		store local 0
		const 10
		store local 1
		const 3
		store local 2
	main_label_0:
		load local 0
		load local 1
		le 
		brf main_label_1
		load   local 0
		const 5
		call pow
		rstore local 2
		load   local 2
		const 1
		add
		store local 2
		load  local 0
		const 1
		add
		store local 0
		br main_label_0
	main_label_1:		
		const  0
		store local 0
		const 10
		store local 1
		const 3
		store local 2
	main_label_2:		
		load local 0
		load local 1
		le 
		brf main_label_3
		rload local 2
		print
		const 10
		printchar
		load   local 2
		const 1
		add
		store local 2
		load  local 0
		const 1
		add
		store local 0
		br main_label_2
	main_label_3:		
		const 10
		printchar
		halt