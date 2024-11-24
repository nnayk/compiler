fp .req x29
lr .req x30
.arch armv8-a
.text


.global main
main:
stp fp, lr [sp,-48] !
ldp fp, lr [sp], 48

