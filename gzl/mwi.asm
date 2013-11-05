begin:
	    set %one, $1
	    set %sum, $5
go:
        sub %sum, %sum, %one
        jgt go
	    mov %three, %sum
