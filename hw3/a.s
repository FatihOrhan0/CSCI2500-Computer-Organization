#hw3.s
#this file is the solution for the third homework that mimics hw1 in assembly. 


#TODO: 

#From the entered data stored in v0, go through 128 bytes.
#int i = 0;
#for (; i < 128; i++) { 
# if (buffer[i] < 0) break;
# if (!isprint(buffer[i])) charNums[((int) buffer[i]) - 32]++;
#}
#printf("Read %d bytes\n", i);

#for (int j = 0; j < 95; j++) { 
# if (charNums[j] != 0) { 
#   printf("%c: ", (char) (j + 32));
#   printDashes(charNums[j]); 
#}}



.data
  buffer:     .space 128
  chars:      .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  charLen:    .word 95
  prompt:     .asciiz "Enter data: "
  result1:    .asciiz "Read "
  result2:    .asciiz "bytes\n"
  newline:    .asciiz "\n"
  openPar:    .asciiz " ("
  closePar:    .asciiz ")"
  pound:      .asciiz "#"


.text
  .globl main   

main: 
  sub $sp, $sp, 4
  sw  $ra, 0($sp) 

  la $a0, prompt
  li $v0, 4
  syscall

  li $a1, 128
  la $a0, buffer
  li $v0, 8
  syscall
  #li $v0, 4
  #syscall

#int i = 0;
#for (; i < 128; i++) { 
# if (buffer[i] < 0) break;
# if (!isprint(buffer[i])) charNums[((int) buffer[i]) - 32]++;
#}
#printf("Read %d bytes\n", i);

  li $s0, 0


  parseLoop: 
    slt $t3, $s0, 95
    beq $t3, 0, exit2

    lb $s1, 0($a0)

    slt $t6, $s1, 0
    beq $t6, 0, exit2

    sb $s1, 0($a2)
    jal isprint
    beq $v1, 0, parseLoop

    la $s2, chars
    sub $s2, $s2, 32
    add $s2, $s2, $s1
    lw $s3, 0($s2)
    add $s3, $s3, 1
    sw $s3, 0($s2)

    j parseLoop

  exit2: 

  la $s4, chars
  lw $s5, 0($s4)
  add $a0, $s5, 0
  li $v0, 1
  syscall



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

  #void printNPounds(int n):
  #for (int i = 0; i < n; i++) {printf("#");}
  #printf(" (%d)\n", n);

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

      