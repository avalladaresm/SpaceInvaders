.globl getPlayerCol
.extern player

.text
    getPlayerCol:
        addi $sp, $sp, -4
        sw $ra, 0($sp)

        la $t0, player
        lb $v0, 1($t0)

        lw $ra, 0($sp)
        addi $sp, $sp, 4
        jr $ra
