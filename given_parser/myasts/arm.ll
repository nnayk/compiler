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
	add x2, 2, 4
	sub x3, 9, 8

	L2:
	add x4, 7, 8

	L3:
	add x6, 3, %5
adrp x0, fmt
add x0, x0, :lo12:fmt
mov x1, x7
bl printf
	mul x9, 9, %6
	br label %L4

	L4:
	ret
	ldp fp, lr, [sp], 48

