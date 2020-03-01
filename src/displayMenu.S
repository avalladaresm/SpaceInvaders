.globl displayMenu
.extern set_color
.extern set_cursor
.extern puts

.data
	title: .asciiz "SPACE INVADERS"
    play: .asciiz "Press p to play"
    by: .asciiz "By: Alejandro Valladares"

.text
    displayMenu:
        addi $sp, $sp, -4
        sw $ra, 0($sp)
        li $a0, 15              #15 = BRIGHT_WHITE
        li $a1, 0               #0  = BLACK
        jal set_color
        
        li $a0, 10
        li $a1, 32
        jal set_cursor
        
        la $a0, title
        jal puts

        li $a0, 13
        li $a1, 31
        jal set_cursor
        
        la $a0, play
        jal puts

        li $a0, 29
        li $a1, 55
        jal set_cursor

        la $a0, by
        jal puts

        lw $ra, 0($sp)
        addi $sp, $sp, 4
        jr $ra