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
	str 3, [sp, 16]
	add x1, 4, 3
	str x1, [sp, 16]
adrp x0, fmt
add x0, x0, :lo12:fmt
mov x1, -8
bl printf
adrp x0, fmt
add x0, x0, :lo12:fmt
mov x1, ldr xq, [sp, 0]neg xq, xq

bl printf
	add x6, %1, 2
	str x6, [sp, 16]
	b L1

	L1:
	ret
	ldp fp, lr, [sp], 48

