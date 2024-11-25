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

	L2:
adrp x0, fmt
add x0, x0, :lo12:fmt
mov x1, 3
bl printf

	L3:

	L4:
adrp x0, fmt
add x0, x0, :lo12:fmt
mov x1, 2
bl printf

	L5:
	br label %L6

	L6:
	ret
	ldp fp, lr, [sp], 48

