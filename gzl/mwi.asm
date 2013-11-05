begin:
	    set %one, $3
	    set %two, $5
        jmp go
go:
	    mov %three, %one	
	    mov %three, %two
        add %three, %three, %two
