begin_mwi:
        set %const, 14316  # set register to constant
        set %max, 30             # the max window size
        set %i, 0                # current number of data points available (simulated)

outer_loop_begin:	
	    set %j,   0              # init inner loops index
        set %sum, 0              # current mwi value

        cmp %i, %max             # find max of const and
        jlt i_gt_lim
        mov %lim, %i
        jmp inner_loop
        
i_gt_lim:
        mov %lim, %max
        
inner_loop:
        load %tmp, %j            # load current data point
        add %sum, %sum, %tmp     # add it to sum
        addi %j, %j, 1           # increment inner loop
        cmp %i, %lim             # re-run loop if i < lim
        jlt inner_loop

outer_loop_end:
        addi %i, %i, 1           # increment data pointer
        div %sum, %sum, %const   # divide the sum total of observed values by
        dis %sum                 # display the computed mwi
        jmp begin_mwi            # start new mwi computation
