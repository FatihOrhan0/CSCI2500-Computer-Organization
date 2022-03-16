.data
  one: .asciiz "byte #1: "
  two: .asciiz "| byte #2: "
  three: .asciiz "| byte #3: "
  four: .asciiz "| byte #4: "
  value: .word 0x12345678
  first: .word 0xff000000
  second: .word 0x00ff0000
  third: .word 0x0000ff00
  fourth: .word 0x000000ff
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

extractBytes2:
    move $s0, $a0
    lw $s1, first
    and $t0, $a0, $s1
    srl $t0, $t0, 24
    lw $s1, second
    and $t1, $a0, $s1
    srl $t1, $t1, 16
    lw $s1, third
    and $t2, $a0, $s1
    srl $t2, $t2, 8
    lw $s1, fourth
    and $t3, $a0, $s1
   
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