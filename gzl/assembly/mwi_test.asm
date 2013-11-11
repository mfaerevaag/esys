begin:
        set $a, 0
        set $b, 1
next_fib:
        add $fib, $a, $b
        mov $tmp, $a
        add $a, $a, $b
        mov $b, $tmp
        jmp next_fib
