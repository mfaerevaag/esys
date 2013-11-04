begin:
        set %one, 1
	    set %a, 5
addit:  
        sub %a, %one, %a
        jgt addit
        set %a, 5
	    
        
