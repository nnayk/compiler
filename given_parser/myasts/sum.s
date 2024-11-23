fp .req x29
lr .req x30

.arch armv8-a
.text

/*

long int sum(long int x, long int y)
{
  return x + y;
}

*/

.global sum
sum:
    // x comes in w0, y in w1
    // return value in w0
    add x0, x0, x1
    ret

.global     main
main:
    // pre-increment the stack point to create space for two 8-byte registers
    // link register (x30), and frame pointer (x29), and store them.
    stp     x29, x30, [sp, -16]!
    mov     x29, sp

    // argc comes in from w0, so just copy it over to w1 
    mov w1, w0
    // values in a bunch of registers
    bl sum      
    // what values are still in the registers at this point?

    // restore the registers and post-decrement 
    // the stack pointer for consistency
    ldp     x29, x30, [sp], 16

    // return from the call
    ret
