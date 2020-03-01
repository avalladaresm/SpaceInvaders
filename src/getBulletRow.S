.globl getBulletRow
.extern bullet

.text
    getBulletRow:
        addi $sp, $sp, -4
        sw $ra, 0($sp)

        la $t0, bullet
        lb $v0, 0($t0)

        lw $ra, 0($sp)
        addi $sp, $sp, 4
        jr $ra