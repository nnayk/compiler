target triple = "x86_64-apple-macosx14.0.0"

@.println = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
declare i32 @printf(i8*, ...)

define noundef i64 @main() {
    %x = alloca i64, align 8
    store i64 9, i64* %x, align 8  ; Store 9 in x
    %1 = load i64, i64* %x, align 8  ; Load x into %1
    %2 = icmp sgt i64 %1, 0  ; Compare %1 to 0
    br i1 %2, label %L0, label %L1  ; Branch based on comparison

L0:
    %3 = load i64, i64* %x, align 8  ; Load x again
    %4 = sub i64 %3, 1  ; Decrement
    store i64 %4, i64* %x, align 8  ; Store back to x
    %5 = load i64, i64* %x, align 8  ; Load updated x
    ; Print the value of %5
    %format_str_ptr = bitcast [5 x i8]* @.println to i8*  ; Correctly cast to i8*
    call i32 (i8*, ...) @printf(i8* %format_str_ptr, i64 %5)  ; Call printf with %5

    %6 = icmp sgt i64 %5, 0  ; Check if %5 is greater than 0
    br i1 %6, label %L0, label %L1  ; Loop back if true

L1:
    ret i64 %5  ; Return the final value of x
}

