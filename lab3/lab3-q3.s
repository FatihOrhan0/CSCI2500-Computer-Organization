.data
  prompt:           .asciiz "What's the capital of New York\n"
  corAnswer:        .asciiz "Wow, you got it!\n"
  wroAnswer:        .asciiz "Sorry, incorrect!\n"
  answer:           .asciiz "Albany"
  newline:          .asciiz "\n"
  buffer:           .space 32

.text
  .globl main

main: 
  sub $sp, $sp, 4
  sw  $ra, 0($sp)

  la $a0, prompt
  li $v0, 4
  syscall
  la $a1, prompt

  jal strlen
  add $a0, $v1, 0
  li $v0, 1
  syscall
  la $a1, prompt
  la $a2, corAnswer
  lw $a3, 5
  jal strncmp
  add $a0, $v1, 0
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
      #     if (s1[i > s2[i]) return 1;
      #}
      #return 0;

      li $t0, 0

      strnLoop: 
        slt $t6, $t0, $a3
        beq $t6, 0, exitNcmp
        
        lbu $t2, 0($a1)
        lbu $t3, 0($a2)

        slt $t5, $t2, $t3
        beq $t5, 1, lessThan

        slt $t5, $t3, $t2
        beq $t5, 1, greaterThan

        #increase the variables here
        add $a1, $a1, 1
        add $a2, $a2, 1
        add $t1, $t1, 1

    
      
      lessThan: 
        lw $v1, -1
        jr $ra

      greaterThan:
        lw $v1, 1
        jr $ra

      exitNcmp: 
        lw $v1, 0
        jr $ra


