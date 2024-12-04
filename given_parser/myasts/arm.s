.data
fmt: .asciz "%d\n"
fmtn: .asciz "%d\n"
fp .req x29
lr .req x30


.arch armv8-a


.text
.global main
main:
	stp fp, lr, [sp,-48] !

	L0:
    adrp x0, fmt
    add x0, x0, :lo12:fmt
    mov x1, 3
    bl printf
	br label L1

	L1:
	ret
	ldp fp, lr, [sp], 48

