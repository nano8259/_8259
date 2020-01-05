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
  sw $t3, 28($sp)
  lw $t1, 20($sp)
  lw $t2, 28($sp)
  beq $t1,$t2,label2
  j label3
label3:
  li $t3, 2
  sw $t3, 36($sp)
  lw $t1, 20($sp)
  lw $t2, 36($sp)
  beq $t1,$t2,label2
  j label0
label2:
  li $t3, 1
  sw $t3, 44($sp)
  lw $v0,44($sp)
  jr $ra
label1:
  li $t3, 1
  sw $t3, 52($sp)
  lw $t1, 20($sp)
  lw $t2, 52($sp)
  sub $t3,$t1,$t2
  sw $t3, 56($sp)
  move $t0,$sp
  addi $sp, $sp, -20
  sw $ra,0($sp)
  lw $t1, 20($t0)
  move $t3,$t1
  sw $t3,20($sp)
  jal fibo
  lw $ra,0($sp)
  addi $sp,$sp,20
  sw $v0,48($sp)
  li $t3, 2
  sw $t3, 64($sp)
  lw $t1, 20($sp)
  lw $t2, 64($sp)
  sub $t3,$t1,$t2
  sw $t3, 68($sp)
  move $t0,$sp
  addi $sp, $sp, -20
  sw $ra,0($sp)
  lw $t1, 20($t0)
  move $t3,$t1
  sw $t3,20($sp)
  jal fibo
  lw $ra,0($sp)
  addi $sp,$sp,20
  sw $v0,60($sp)
  lw $t1, 48($sp)
  lw $t2, 60($sp)
  add $t3,$t1,$t2
  sw $t3, 72($sp)
  lw $v0,72($sp)
  jr $ra
label0:

main:
  addi $sp, $sp, -76
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal read
  lw $ra,0($sp)
  addi $sp, $sp, 4
  sw $v0, 84($sp)
  lw $t1, 84($sp)
  move $t3, $t1
  sw $t3, 76($sp)
  move $t0,$sp
  addi $sp, $sp, -20
  sw $ra,0($sp)
  lw $t1, 20($t0)
  move $t3,$t1
  sw $t3,20($sp)
  jal fibo
  lw $ra,0($sp)
  addi $sp,$sp,20
  sw $v0,88($sp)
  lw $t1, 88($sp)
  move $t3, $t1
  sw $t3, 80($sp)
  lw $a0, 80($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal write
  lw $ra,0($sp)
  addi $sp, $sp, 4
  li $t3, 1
  sw $t3, 96($sp)
  lw $v0,96($sp)
  jr $ra
label4:
