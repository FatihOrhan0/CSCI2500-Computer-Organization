.data
  fib:       .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  fibL:      .word 20
  newline:     .asciiz "\n"


.text
  .globl main   

main: 
  sub $sp, $sp, 4
  sw $ra, 0($sp) 

  la $s0, fib
  lw $t0, 4($s0)
  li $t0, 1
  sw $t0, 4($s0)

  li $t0, 0

  loop: 
    slt $t3, $t0, 18
    beq $t3, 0, exit1


    lw $t1, 0($s0)
    lw $t2, 4($s0)
    add $t5, $t1, $t2
    sw $t5, 8($s0)
    add $s0, $s0, 4


    add $t0, $t0, 1 
    #add $t1, $t1, 4 
    #add $t2, $t2, 4  

    j loop



    exit1:
      jal printArr
    exit2:
      lw  $ra, 0($sp)
      add $sp, $sp, 4
      jr $ra




    printArr: 
      la $s0, fib
      li $t0, 0

      printLoop: 
        slt $t3, $t0, 20
        beq $t3, 0, exit2

        li $v0, 1
        lw $a0, 0($s0)
        syscall
        li $v0, 4
        la $a0, newline
        syscall
        add $s0, $s0, 4
        add $t0, $t0, 1

        j printLoop

      jr $ra




