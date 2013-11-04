begin:
        set %sum, 0
	    set %one, 1
addit:  
        add %sum, %sum, %one
        #jlt begin
        jmp addit
	    
        
