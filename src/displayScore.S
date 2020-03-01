.globl displayScore
.extern set_color
.extern set_cursor
.extern puts
.extern put_char
.extern TO_STR

.data
	score: .asciiz "Score"

.text
    displayScore:
        addi $sp, $sp, -4
        sw $ra, 0($sp)

        move $t6, $a0

        li $a0, 1
        li $a1, 1
        jal set_cursor
        
        li $a0, 15              #15 = BRIGHT_WHITE
        li $a1, 0               #0  = BLACK
        jal set_color
        
        la $a0, score
        jal puts
        
        li $a0, 10              #10 = LIGHT_GREEN
        li $a1, 0               #0  = BLACK
        jal set_color

        li $a0, 1
        li $a1, 7
        jal set_cursor

        li $t0, 0xf 
        and $t0, $t6, $t0
        move $a0, $t0
        jal TO_STR
        
        move $a0, $v0
        jal put_char

        lw $ra, 0($sp)
        addi $sp, $sp, 4
        jr $ra