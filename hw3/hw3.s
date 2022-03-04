#hw3.s
#this file is the solution for the third homework that mimics hw1 in assembly. 





.data
  buffer:     .space 132
  chars:      .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  charLen:    .word 95
  prompt:     .asciiz "Enter data: "
  result1:    .asciiz "Read "
  result2:    .asciiz " bytes\n"
  newline:    .asciiz "\n"
  openPar:    .asciiz " ("
  closePar:   .asciiz ")\n"
  colspace:   .asciiz ": "
  pound:      .asciiz "#"


.text
  .globl main   

main: 
  sub $sp, $sp, 4
  sw  $ra, 0($sp) 

  la $a0, prompt
  li $v0, 4
  syscall

  li $a1, 129
  la $a0, buffer
  li $v0, 8
  syscall

  li $s0, 0

  parseLoop: 
    slt $t3, $s0, 128  #s0 < 128
    beq $t3, 0, exit2

    lb $s1, 0($a0)

    beq $s1, 0, exit2

    add $a2, $0, $s1
    jal isprint
    add $s0, $s0, 1
    add $a0, $a0, 1
    beq $v1, 0, parseLoop

    la $s2, chars #s2 = &chars[0]
    sub $s1, $s1, 32
    sll $s1, $s1, 2
    add $s2, $s2, $s1
    lw $s3, 0($s2)
    add $s3, $s3, 1
    sw $s3, 0($s2)

    j parseLoop

  exit2: 
  la $a0, result1
  li $v0, 4
  syscall
  add $a0, $0, $s0
  #sub $a0, $a0, 1
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, result2
  syscall
  la $s4, chars
  lw $s5, 0($s4)
  add $a0, $s5, 0
  li $v0, 1
  #syscall





  li $s0, 0
  la $s3, chars
  printArr: 
    slt $t3, $s0, 95  #s0 < 95
    beq $t3, 0, exit3

    lw $s4, 0($s3)
    beq $s4, 0, noPrint

    li $v0, 11
    add $a0, $0, $s0
    add $a0, $a0, 32
    syscall
    li $v0, 4
    la $a0, colspace
    syscall

    add $a1, $0, $s4
    jal printNPounds

   


    noPrint:
    add $s3, $s3, 4
    add $s0, $s0, 1

    j printArr


  exit3:
  lw  $ra, 0($sp)
  add $sp, $sp, 4
  jr $ra



  #isprint(int n);

  isprint: 
    #a0 -> n
    add $v1, $0, $0
    slt $t0, $a2, 127
    sgt $t1, $a2, 31
    and $v1, $t0, $t1
    j $ra


  printNPounds:
    #a1->n 
    li $t0, 0 

    printLoop: 
      slt $t1, $t0, $a1
      beq $t1, 0, exit1
      li $v0, 4
      la $a0, pound
      syscall
      addi $t0, $t0, 1
      j printLoop

    exit1: 
      la $a0, openPar
      syscall
      li $v0, 1
      add $a0, $a1, $0
      syscall
      li $v0, 4
      la $a0, closePar
      syscall
      j $ra
    
    #a0 -> n
    add $v1, $0, $0
    slt $t0, $a0, 127
    sgt $t1, $a0, 31
    and $v1, $t0, $t1
    j $ra

      