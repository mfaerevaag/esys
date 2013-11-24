init:
        set $adr, 10           ; her gemmes seneste adresse som er blevet behandlet
        set $store_adr, 251    ; addressen på hvilken vi løbende gemmer (og overskriver) mwi resultatet

get_next_point:
        load $tmp, $adr        ; load det næste sample fra data memory
        mwi $res, $tmp         ; send sample værdi til mwi co-processoren
        store $res, $store_adr ; gem mwi resultatet i data memory

        addi $adr, $adr, 1     ; inc adressen
	    jmp get_next_point     ; loop
