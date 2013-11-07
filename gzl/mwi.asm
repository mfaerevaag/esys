begin:	
	    set $cadr, 0
        set $acc, 0	
	    #set $tmp, 31
	    set $tmp, 31		
        add $eadr, $sadr, $tmp
loop:
	    load $tmp, $cadr
        add $acc, $acc, $tmp
        set $tmp, 1
        add $cadr, $cadr, $tmp
        cmp $cadr, $eadr
        jlt loop
average:
	    set $tmp, 1118482 # div const for 30
	    div $res, $acc, $tmp
        set $tmp, 1
        add $sadr, $sadr, $tmp
        set $tmp, 3
