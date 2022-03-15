.data
  one: .asciiz "byte #1: "
  two: .asciiz "| byte #2: "
  three: .asciiz "| byte #3: "
  four: .asciiz "| byte #4: "
  value: .word 0x4a889cf1
.text
  .globl main  
main: 
    sub $sp, $sp, 4
    sw $ra, 0($sp)
    lw $a0, value
    jal extractBytes
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra


extractBytes: 
    move $s0, $a0
    srl $t0, $s0, 24

    srl $t1, $s0, 16
    sll $t1, $t1, 24
    srl $t1, $t1, 24

    srl $t2, $s0, 8
    sll $t2, $t2, 24
    srl $t2, $t2, 24

    sll $t3, $s0, 24
    srl $t3, $t3, 24

    la $a0, one
    li $v0, 4
    syscall
    add $a0, $t0, 0
    li $v0, 1
    syscall

    la $a0, two
    li $v0, 4
    syscall
    li $v0, 1
    add $a0, $t1, $0
    syscall

    la $a0, three
    li $v0, 4
    syscall
    li $v0, 1
    add $a0, $t2, $0
    syscall

    la $a0, four
    li $v0, 4
    syscall
    li $v0, 1
    add $a0, $t3, $0
    syscall

    jr $ra

    