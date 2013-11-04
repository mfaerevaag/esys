begin:
        set %one, $1
	    set %sum, $0
wallah: 
        add %sum, %sum, %one
        jmp wallah

