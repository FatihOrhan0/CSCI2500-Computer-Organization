
.data
  even:     .asciiz "EVEN\n"
  odd:      .asciiz "ODD\n"


.text
  .globl main  

main: 
    sub $sp, $sp, 4
    sw $ra, 0($sp)
    addi $a0, $a0, 1071
    jal parity
    add $a0, $s0, $0
    beq $v0, 0, printEven
    li $v0, 1
    syscall
    lw  $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

    printEven: 
    li $v0, 4
    la $a0, even
    syscall
    lw  $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra




parity: 
    add $t0, $a0, $0
    sll $s0, $t0, 31
    srl $s0, $s0, 31
    jr $ra


