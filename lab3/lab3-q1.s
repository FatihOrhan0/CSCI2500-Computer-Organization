.data
  string:        .asciiz "==> lucky "
  newline:       .asciiz "\n"

.text 
  .globl main

main:   
        sub $sp, $sp, 4   # allocate stack space to store $ra
        sw  $ra, 0($sp)   # store $ra on the stack


        li $s0, 13             # Load Immediate (li)  lucky = 13
        sgt $t0, $s0, -13       #check if s0 > -13, store in t0
        beq $t0, 1, assign_tag  #forward to assign_tag if t0 == 1
        beq $t0, 0, normal_order

        assign_tag: 
            sub $s0, $s0, 6     #lucky -= 6;
        
        normal_order:
        li $v0, 4
        la $a0, string
        syscall
        li $v0, 1
        add $a0, $s0, 0
        syscall
        li $v0, 4
        la $a0, newline
        syscall

        #li $v0, 1
        #syscall

        lw  $ra, 0($sp)
        add $sp, $sp, 4
        jr $ra
