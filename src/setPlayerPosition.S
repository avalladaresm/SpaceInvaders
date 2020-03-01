.globl setPlayerPosition
.extern player

.text
    setPlayerPosition:
        addi $sp, $sp, -4
        sw $ra, 0($sp)

        la $t0, player
        sb $a0, 0($t0)
        sb $a1, 1($t0)

        lw $ra, 0($sp)
        addi $sp, $sp, 4
        jr $ra
