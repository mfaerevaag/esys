begin:
        set %one, $8
	    set %sum, $5
        cmp %one, %sum
        jlt yes
        set %wat, $15
yes:
        set %wat, $7
        jmp none
no:
	    set %wat, $9
none:
        
