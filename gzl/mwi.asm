.begin:
        seti %const, 143165577  # set register to constant
        seti %lim, 30
        seti %idx, 0
	    seti %sum, 0
        jmp .loop         # unconditional jump
.loop:
        load %tmp, %idx   # load 
        div %const, %tmp  # divide using the funky constant
        add %sum, %tmp    # save result in 1st arg
        cmp %idx, %lim	  # sets lt/gt/eq flags
	    inc %idx          # increment by one (does not set flags)
        jlt .loop         # jump if less than flag is set
        ret
