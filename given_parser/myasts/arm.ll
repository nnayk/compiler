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

	L1:
adrp x0, fmt
add x0, x0, :lo12:fmt
mov x1, x2
bl printf
	sub x4, %2, 1

	L2:
adrp x0, fmt
add x0, x0, :lo12:fmt
mov x1, x7
bl printf
	br label %L3

	L3:
	ret
	ldp fp, lr, [sp], 48

