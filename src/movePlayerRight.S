.globl movePlayerRight
.extern set_color
.extern set_cursor
.extern puts
.extern put_char
.extern setPlayerPosition
.extern player

.data
	playerSprite: .asciiz "\x2\x3\x4"
    emptySprite: .asciiz "\xFF"

.text
    movePlayerRight:
        addi $sp, $sp, -12
        sw $ra, 8($sp)

        la $t0, player
        sw $t0, 0($sp)
        sb $a0, 0($sp)
        sb $a1, 1($sp)

        li $a0, 10              #14 = LIGHT_GREEN
        li $a1, 0               #0  = BLACK
        jal set_color

        la $t0, player
        lb $a0, 0($sp)
        lb $a1, 1($sp)
        jal set_cursor

        la $t1, playerSprite
        sw $t1, 4($sp)
        #jal puts

        la $t0, player
        lb $a0, 0($sp)
        lb $a1, 1($sp)
        addi $a1, $a1, -1
        sb $a1, 1($sp)
        jal set_cursor

        la $a0, emptySprite
        jal puts

        la $t0, player
        lw $a0, 4($sp)
        jal puts

        la $t0, player
        lb $a0, 0($sp)
        lb $a1, 1($sp)
        addi $a1, $a1, -2
        sb $a1, 1($sp)
        jal set_cursor

        la $a0, emptySprite
        jal puts

        la $t0, player
        lb $a0, 0($sp)
        lb $a1, 1($sp)
        jal setPlayerPosition

        lw $ra, 8($sp)
        addi $sp, $sp, 12
        jr $ra