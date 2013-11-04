begin:
        set %one, 1	
	    set %a, 0
	    set %b, 0
addit:  
        add %c, %a, %b
        dis %c
        jlt addit
        set %a, 5
	    
        
