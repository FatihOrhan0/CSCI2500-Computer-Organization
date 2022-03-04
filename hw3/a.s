#hw3.s
#this file is the solution for the third homework that mimics hw1 in assembly. 


#TODO: create isprint function
#create a function to print n #s
#for (int i = 0; i < n; i++) {printf("#");}
#printf(" (%d)\n", n);


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
#



.data
  buffer:     .space 128
  chars:      .space 380
  charLen:    .word 95
  prompt:     .asciiz "Enter data: "
  result1:    .asciiz "Read "
  result2:    .asciiz "bytes\n"
  newline:    .asciiz "\n"
  pound:      .asciiz "#"


.text
  .globl main   

main: 
  sub $sp, $sp, 4
  sw  $ra, 0($sp) 

  la $a1, prompt
  lb $a0, 0($a1)
  jal isprint
  li $v0, 1
  add $a0, $v1, $0
  syscall

  addi $a1, $0, 5
  jal printNPounds


  lw  $ra, 0($sp)
  add $sp, $sp, 4
  jr $ra



  #isprint(int n);

  isprint: 
    #a0 -> n
    add $v1, $0, $0
    slt $t0, $a0, 127
    sgt $t1, $a0, 31
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

      