begin:
        set %one, $1
	    set %sum, $5
wallah: 
        sub %sum, %sum, %one
        jlt end
        jmp wallah
end:
        set %wat, $10

