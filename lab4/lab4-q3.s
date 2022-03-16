.data
    list: .word 12,100,101,5,123456789,18
    hexlist: .word 0x4a889cf1, 0xff00fefd
    hexbytes: .word 0xfc, 0x01, 0xaa, 0xbb
    test1: .word 0,0,0,0,0,0,0,0 # $a1 set to 8; returns 8 in $v0
    test2: .word 0x4a889cf1, 0xff00fefd # $a1 set to 2; returns 5 in $v0
    test3: .byte 0x01, 0x0b, 0xff, 0xef # $a1 set to 1; returns 0 in $v0
    test4: .word 0x4a889cf1, 0xff00fefd # $a1 set to 1; returns 3 in $v0
    one: .asciiz "byte #1: "
    two: .asciiz "| byte #2: "
    three: .asciiz "| byte #3: "
    four: .asciiz "| byte #4: "
    newline: .asciiz "\n"
    first: .word 0xff000000
    second: .word 0x00ff0000
    third: .word 0x0000ff00
    fourth: .word 0x000000ff

.text
    .globl main
main: 
    sub $sp, $sp, 4
    sw $ra, 0($sp)
    li $s4, 0

    #la $a0, test1
    #li $a1, 8
    #jal evens

    la $a0, test2
    li $a1, 2
    jal evens

    #la $a0, test3
    #li $a1, 1
    #jal evens

    #la $a0, test4
    #li $a1, 1
    #jal evens

    lw  $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra


evens: 
    sub $sp, $sp, 4
    sw $ra, 0($sp)
    li $s2, 0   #int i = 0
    li $s4, 0   #int total = 0
    #sll $a1, $a1, 3
    li $s5, 1

    loop: 
        slt $s3, $s2, $a1
        beq $s3, 0, exit1
        move $s6, $a0 
        
        lw $a0, 0($a0)
        bne $a0, 0, skipIncrease5
        sub $s4, $s4, 3
        skipIncrease5: 
        jal extractBytes2

        move $a0, $t0
        jal parity
        beq $s0, $s5, skipIncrease1
        addi $s4, $s4, 1
        skipIncrease1:

        move $a0, $t1
        jal parity
        beq $s0, $s5, skipIncrease2
        addi $s4, $s4, 1
        skipIncrease2:

        move $a0, $t2
        jal parity
        beq $s0, $s5, skipIncrease3
        addi $s4, $s4, 1
        skipIncrease3:

        move $a0, $t3
        jal parity
        beq $s0, $s5, skipIncrease4
        addi $s4, $s4, 1
        skipIncrease4:

        move $a0, $s6
        addi $a0, $a0, 4
        addi $s2, $s2, 1
        j loop

    exit1: 
        move $v0, $s4
        lw  $ra, 0($sp)
        addi $sp, $sp, 4
        jr $ra    



parity: 
    add $t7, $a0, $0
    sll $s0, $t7, 31
    srl $s0, $s0, 31

    move $v0, $s0
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

    li $v0, 4
    la $a0, newline
    syscall

    jr $ra