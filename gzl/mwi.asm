init:
        set $sadr, 0            ; set a pointer to where we are in the data set
begin:	
	    set $cadr, 0            ; set the address cursor
        set $acc, 0	            ; reset the accumulator
        addi $eadr, $sadr, 31   ; calc the end address
loop:
	    load $tmp, $cadr        ; load the next data point
        add $acc, $acc, $tmp    ; add the value to the accumulator
        addi $cadr, $cadr, 1    ; inc the address cursor
        cmp $cadr, $eadr        ; loop if we haven't reached the end address
        jlt loop
average:
	    set $tmp, 1118482       ; div const for 30
	    div $res, $acc, $tmp    ; divide the accumulator by 30
        addi $sadr, $sadr, 1    ; inc the start address
        jmp begin               ; start next mwi calculation
        
