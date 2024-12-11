.data
fmt: .asciz "%d\n"
fmtn: .asciz "%d\n"
fp .req x29
lr .req x30


.arch armv8-a


.text
.global foo
foo:
	stp fp, lr, [sp,-48] !

	L0:
	str 3, [sp, 16]
	icmp sgt x5, %4, 0

	L1:
adrp x0, fmt
add x0, x0, :lo12:fmt
mov x1, x2
bl printf
	sub x4, %2, 1
	str x4, [sp, 16]
	icmp sgt x5, %4, 0

	L2:
adrp x0, fmt
add x0, x0, :lo12:fmt
mov x1, x7
bl printf
	str 2, [sp, 16]
	b L3

	L3:
	ret
	ldp fp, lr, [sp], 48

.global main
main:
	stp fp, lr, [sp,-32] !

	L4:
adrp x0, fmt
add x0, x0, :lo12:fmt
mov x1, x9
bl printf
	str 3, [sp, 16]
	b L5

	L5:
	ret
	ldp fp, lr, [sp], 32

