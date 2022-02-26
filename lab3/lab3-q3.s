.data
  prompt:           .asciiz "What's the capital of New York?\n"
  corAnswer:        .asciiz "What's y ou got it!\n"
  wroAnswer:        .asciiz "Sorry, incorrect!\n"
  answer:           .asciiz "Albany\n"
  entered:          .asciiz "You entered \""
  newline:          .asciiz "\n"
  quote:            .asciiz "\""
  buffer:           .space 32

.text
  .globl main

main: 
  sub $sp, $sp, 4
  sw  $ra, 0($sp)

  la $a0, prompt
  li $v0, 4
  syscall

  li $v0, 8
  la $a0, buffer
  li $a1, 32
  syscall

  jal strlen
  add $a0, $v1, 0
  li $v0, 1
  syscall
  la $a0, newline
  li $v0, 4
  syscall
  
  #la $a1, prompt
  la $a2, answer
  li $a3, 8
  jal strncmp
  
  add $a0, $v1, 0
  li $v0, 1
  syscall

  lw  $ra, 0($sp)
  add $sp, $sp, 4
  jr $ra



  #store the length of the string in t0. Requires the string to be stored in a1
  strlen: 
    li $t0, 0
    li $v1, 0

    loop: 
      lbu $t1, 0($a1)
      beq $t1, 0, returnLen
      add $t1, $t1, 1
      add $a1, $a1, 1
      addi $v1, $v1, 1

      j loop
    
    returnLen: 
      jr $ra


  strncmp: 
    #a1 will have the first string a2 second and a3 will have int. Returns in v0
    #for (int i = 0; i < n; i++) { 
    #     if (s1[i] < s2[i]) return -1;
    #     if (s1[i] > s2[i]) return 1;
    #     if (s1[i] == 0) return 0;
    #}
    #return 0;

    li $t0, 0
    move $s0, $a0
    move $s1, $a2

    strnLoop: 
      slt $t6, $t0, $a3
      beq $t6, 0, exitNcmp
      
      lb $t2, 0($s0)
      lb $t3, 0($s1)

      bne $t2, $t3, lessThan

      #increase the variables here
      addi $s0, $s0, 1
      addi $s1, $s1, 1
      addi $t0, $t0, 1

      j strnLoop

  
    
    lessThan: 
      sub $v1, $t2, $t3
      jr $ra


    exitNcmp: 
      li $v1, 0
      jr $ra


