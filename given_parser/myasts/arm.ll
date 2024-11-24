.data
fmt: .asciz "%d\n"
fmtn: .asciz "%d\n"
fp .req x29
lr .req x30


.arch armv8-a


.text
.global main
main:
	stp fp, lr, [sp,-64] !

	L0:
	add x1, 3, 4
	add x2, 0, 9
	add x3, %1, %2
	br label %L1

	L1:
	ret
	ldp fp, lr, [sp], 64

