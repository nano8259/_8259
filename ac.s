.data
_Prompt: .asciiz "Enter an integer:  "
_ret: .asciiz "\n"
.globl main
.text
read:
  la $a0,_Prompt
  li $v0,4
  syscall
  li $v0,5
  syscall
  jr $ra
write:
  li $v0,1
  syscall
  li $v0,4
  la $a0,_ret
  syscall
  move $v0,$0
  jr $ra

fibo:
  li $t3, 1
  sw $t3, 8($sp)
  lw $t1, 4($sp)
  lw $t2, 8($sp)
  beq $t1,$t2,label2
  j label3
label3:
  li $t3, 2
  sw $t3, 16($sp)
  lw $t1, 4($sp)
  lw $t2, 16($sp)
  beq $t1,$t2,label2
  j label1
label2:
  li $t3, 1
  sw $t3, 24($sp)
  lw $v0,24($sp)
  jr $ra
label1:
  li $t3, 1
  sw $t3, 32($sp)
  lw $t1, 4($sp)
  lw $t2, 32($sp)
  sub $t3,$t1,$t2
  sw $t3, 36($sp)
  move $t0,$sp
  addi $sp, $sp, -56
  sw $ra,0($sp)
  lw $t1, 36($t0)
  move $t3,$t1
  sw $t3,4($sp)
  jal fibo
  lw $ra,0($sp)
  addi $sp,$sp,56
  sw $v0,28($sp)
  li $t3, 2
  sw $t3, 44($sp)
  lw $t1, 4($sp)
  lw $t2, 44($sp)
  sub $t3,$t1,$t2
  sw $t3, 48($sp)
  move $t0,$sp
  addi $sp, $sp, -56
  sw $ra,0($sp)
  lw $t1, 48($t0)
  move $t3,$t1
  sw $t3,4($sp)
  jal fibo
  lw $ra,0($sp)
  addi $sp,$sp,56
  sw $v0,40($sp)
  lw $t1, 28($sp)
  lw $t2, 40($sp)
  add $t3,$t1,$t2
  sw $t3, 52($sp)
  lw $v0,52($sp)
  jr $ra
label0:

main:
  addi $sp, $sp, -20
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal read
  lw $ra,0($sp)
  addi $sp, $sp, 4
  sw $v0, 16($sp)
  lw $t1, 16($sp)
  move $t3, $t1
  sw $t3, 4($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal read
  lw $ra,0($sp)
  addi $sp, $sp, 4
  sw $v0, 20($sp)
  lw $t1, 20($sp)
  move $t3, $t1
  sw $t3, 8($sp)
  lw $t1, 4($sp)
  lw $t2, 8($sp)
  add $t3,$t1,$t2
  sw $t3, 24($sp)
  lw $t1, 24($sp)
  move $t3, $t1
  sw $t3, 12($sp)
  lw $a0, 12($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal write
  lw $ra,0($sp)
  addi $sp, $sp, 4
  li $t3, 1
  sw $t3, 32($sp)
  lw $v0,32($sp)
  jr $ra
label4:
