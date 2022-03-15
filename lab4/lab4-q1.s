.data
  even: .asciiz "EVEN\n" "ODD\n"
.text
  .globl main  
main: 
    sub $sp, $sp, 4
    sw $ra, 0($sp)
    addi $a0, $a0, 1072
    jal parity
    lw  $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

parity: 
    add $t0, $a0, $0
    sll $s0, $t0, 31
    srl $s0, $s0, 31
    beq $a1, 0, exit

    addi $t3, 6
    mult $s0, $t3
    mflo $s0
    
    printEven:  
    li $v0, 4
    la $a0, even
    add $a0, $a0, $s0
    syscall

    exit: 
    move $v0, $s0
    jr $ra


