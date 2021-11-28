.data
    inputStr: .asciiz "Give two numbers: "
    outputStr: .asciiz "The GCD of two numbers: "
    endline: .asciiz "\n"
.text
main:
    # Give Input message and store input numbers to $a0 and $a1
    li $v0, 4           # $v0=4
    la $a0, inputStr    # $a0=inputstr+0
    syscall             # 4->???
    li $v0, 5           # $v0=5
    syscall             # 4->???
    add $a0, $v0, $zero # $a0 = inputNum1
    li $v0, 5
    syscall
    add $a1, $v0, $zero # $a1 = inputNum2
    # TODO: (fin) The condition of the process terminated

    beq $a1, $zero, exit      ## case(0, 0)

    # call GCD function recursively
    jal GCD
    add $t0, $v0, $zero

    # print the answer
    li $v0, 4
    la $a0, outputStr
    syscall
    add $a0, $t0, $zero
    li $v0, 1
    syscall
    li $v0, 4
    la $a0, endline
    syscall
    j main
# END Main

GCD:
    # save in the stack
    addi $sp, $sp, -12
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)

    add $s0, $a0, $zero     # $s0=a0
    add $s1, $a1, $zero     # $s1=a1

    beq $s0, $zero, retGCD  ## case(0, 2)

    # TODO: (fin) Do Euclidean Algorithm

    # ble $s0, $s1, Euc     # $s0>=$s1

Euc:
    div $s0, $s1            # $s0 %= $s1
    mfhi $s0

    beq $s0, $zero, retGCD  # $s0 == 0 break;
    add $s2, $s0, $zero     ## swap($s0, $s1)
    add $s0, $s1, $zero
    add $s1, $s2, $zero
    j Euc

return:
    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    addi $sp, $sp, 12
    jr $ra

retGCD:
    # TODO: (fin) What do you need to return?

    add $v0, $s1, $zero

    j return
# END GCD

exit:
    # The program is finished running
    li $v0, 10
    syscall
