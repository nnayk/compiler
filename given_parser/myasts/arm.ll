fp .req x29
lr .req x30
.arch armv8-a
.text


.global main
main:
	stp fp, lr [sp,-48] !
	icmp sgt %2, 3, 4
	%3 = zext i1 %2 to i8
	ldp fp, lr [sp], 48

