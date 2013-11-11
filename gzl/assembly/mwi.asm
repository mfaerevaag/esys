init:
        set $cadr, 0  ; keep a pointer to where we are in the data set
	    set $acc, 0   ; the accumulator

get_next_point:
        load $tmp, $cadr        ; load the next data point
        add $acc, $acc, $tmp    ; add the value to the accumulator
        addi $cadr, $cadr, 1    ; inc the address cursor
	    set $tmp, 1118482       ; div const for 30
        
	    div $res, $acc, $tmp    ; divide the accumulator by 30, this is the MWI

        set $tmp, 251           ; store result to address 251
        store $res, $tmp

        set $tmp, 30            ; check if we have 30 points accumulated
        cmp $cadr, $tmp
        jgt align_acc           ; if we do, then align the accumulator
	    jmp get_next_point      ; if not, load the next data point

align_acc:
	    set $tmp, 30              ; get the address 30 samples before the current
        sub $odp_adr, $cadr, $tmp
        load $odp, $odp_adr       ; load the data point at that address
        sub $acc, $acc, $odp      ; subtract it's value from the accumulator
	    jmp get_next_point        ; load the next data point
