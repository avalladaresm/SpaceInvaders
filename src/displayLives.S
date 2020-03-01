.globl displayLives
.extern set_color
.extern set_cursor
.extern puts

.data
	lives: .asciiz "Lives"
    liveSprite: .asciiz "\x2\x3\x4"
    emptySprite: .asciiz "\xff\xff\xff"

.text
    displayLives:
        addi $sp, $sp, -4
        sw $ra, 0($sp)

        move $t4, $a0

        li $a0, 1
        li $a1, 60
        jal set_cursor

        li $a0, 15              #15 = BRIGHT_WHITE
        li $a1, 0               #0  = BLACK
        jal set_color
        
        la $a0, lives
        jal puts

        li $a0, 10              #10 = LIGHT_GREEN
        li $a1, 0               #0  = BLACK
        jal set_color

        li $t0, 0
        li $t1, 1
        li $t2, 2
        
        beq $t4, $t2, if
        if: 
            li $a0, 1
            li $a1, 66
            jal set_cursor
            la $a0, liveSprite
            jal puts
            li $a0, 1
            li $a1, 70
            jal set_cursor
            la $a0, liveSprite
            jal puts
            lw $ra, 0($sp)
            addi $sp, $sp, 4
            jr $ra

        beq $t4, $t1, elif1
        elif1: 
            li $a0, 1
            li $a1, 66
            jal set_cursor
            la $a0, liveSprite
            jal puts
            li $a0, 1
            li $a1, 70
            jal set_cursor
            la $a0, emptySprite
            jal puts
            lw $ra, 0($sp)
            addi $sp, $sp, 4
            jr $ra

        beq $t4, $t0, elif2
        elif2: 
            li $a0, 1
            li $a1, 66
            jal set_cursor
            la $a0, emptySprite
            jal puts
            li $a0, 1
            li $a1, 70
            jal set_cursor
            la $a0, emptySprite
            jal puts
            lw $ra, 0($sp)
            addi $sp, $sp, 4
            jr $ra

        