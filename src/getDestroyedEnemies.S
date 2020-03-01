.globl getDestroyedEnemies
.extern invader1
.extern invader2
.extern invader3

.text
    getDestroyedEnemies:
        addi $sp, $sp, -4
        sw $ra, 0($sp)

        la $t1, invader1
        la $t2, invader2
        la $t3, invader3

        move $t0, $zero         # $t0 = i
        move $t4, $zero         # $t4 = destroyedEnemies
        li $t5, 5               # max count in for
        li $t6, 1               # if isDestroyed == true

        for:
            slt $t7, $t5, $t0
            bne $t7, $zero, end_for

            sll $t8, $t0, 2

            if1:
                add $t9, $t1, $t8
                lw $t9, 2($t9)
                beq $t9, $t4, sum1
            sum1:
                addi $v0, $v0, 1

            if2:
                add $t9, $t2, $t8
                lw $t9, 2($t9)
                beq $t9, $t4, sum2
            sum2:
                addi $v0, $v0, 1

            if3:
                add $t9, $t3, $t8
                lw $t9, 2($t9)
                beq $t9, $t4, sum3
            sum3:
                addi $v0, $v0, 1
            j for

        end_for:
            move $v0, $v0
            jr $ra

        lw $ra, 0($sp)
        addi $sp, $sp, 4
        jr $ra