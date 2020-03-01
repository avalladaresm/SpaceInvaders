.globl setBulletPosition
.extern bullet

.text
    setBulletPosition:
        addi $sp, $sp, -4
        sw $ra, 0($sp)

        la $t0, bullet
        sb $a0, 0($t0)
        sb $a1, 1($t0)

        lw $ra, 0($sp)
        addi $sp, $sp, 4
        jr $ra
