init:
        set $cadr, 0  ; her gemmes seneste adresse som er blevet processeret
	    set $acc, 0   ; her gemmes summen af de 30 samples i MWI'et

get_next_point:
        load $tmp, $cadr        ; load det næste sample fra data memory
        add $acc, $acc, $tmp    ; læg værdien til akkumulator registeret
        addi $cadr, $cadr, 1    ; øg den nuværende adresse med 1
        
	    set $tmp, 1118482       ; divisionskonstanten for at dividere med 30
	    div $res, $acc, $tmp    ; divider akkumulatoren for at få et MWI

        set $tmp, 251           ; store mwi til adresse 251
        store $res, $tmp        ;

        set $tmp, 30            ; tjek om der er akkumuleret 30 eller flere samples
        cmp $cadr, $tmp
        jgt align_acc           ; hvis der er, så tilpas akkumulator
	    jmp get_next_point      ; hvis ikke, så gå til næste sample load

align_acc:
	    set $tmp, 30              ; find adressen 30 samples tilbage i datasættet
        sub $odp_adr, $cadr, $tmp
        load $odp, $odp_adr       ; load samplet på denne adresse
        sub $acc, $acc, $odp      ; træk dets værdi fra akkumulatoren
	    jmp get_next_point        ; gå til næste sample load
