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
mov x1, 9
bl printf

	L2:
adrp x0, fmt
add x0, x0, :lo12:fmt
mov x1, 8
bl printf

	L3:
adrp x0, fmt
add x0, x0, :lo12:fmt
mov x1, x3
bl printf
	br label %L4

	L4:
	ret
	ldp fp, lr, [sp], 48

