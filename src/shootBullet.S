.globl shootBullet
.extern set_color
.extern set_cursor
.extern puts
.extern put_char
.extern setBulletPosition
.extern bullet

.data
	bulletSprite: .asciiz "\x1"
    emptySprite: .asciiz "\xFF"

.text
    shootBullet:
        addi $sp, $sp, -12
        sw $ra, 8($sp)

        la $t0, bullet
        sw $t0, 0($sp)
        sb $a0, 0($sp)
        sb $a1, 1($sp)
        
        la $t1, bulletSprite
        sw $t1, 4($sp)       

        li $a0, 14              #14 = YELLOW
        li $a1, 0               #0  = BLACK
        jal set_color

        la $t0, bullet
        lb $a0, 0($sp)
        addi $a0, $a0, -1
        sb $a0, 0($sp)
        lb $a1, 1($sp)
        jal set_cursor

        la $t0, bullet
        lw $a0, 4($sp)
        jal puts

        la $t0, bullet
        lb $a0, 0($sp)
        addi $a0, $a0, 1
        sb $a0, 0($sp)
        lb $a1, 1($sp)
        jal set_cursor

        la $a0, emptySprite
        jal puts
        
        lb $t1, 0($sp)
        beq $t1, $zero, deleteSprite
        deleteSprite:
            move $a0, $zero
            lb $a1, 1($sp)
            jal set_cursor
            la $a0, emptySprite
            jal puts

        la $t0, bullet
        lb $a0, 0($sp)
        lb $a1, 1($sp)
        jal setBulletPosition

        lw $ra, 8($sp)
        addi $sp, $sp, 12
        jr $ra