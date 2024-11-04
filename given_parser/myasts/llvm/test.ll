target triple = "x86_64-apple-macosx14.0.0"

;declare i32 @printf(ptr noundef, ...)
;@.str = private unnamed_addr constant [6 x i8] c"y=%d\0A\00", align 1
@.println = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
declare i32 @printf(ptr, ...)

define noundef i64 @main() {
    %x = alloca i64, align 8
    store i64 9, ptr %x, align 8
    %1 = load i64, ptr %x, align 8
    %2 = icmp sgt i64 %1, 0
    br i1 %2, label %L0, label %L1

L0:
    %3 = load i64, ptr %x, align 8
    %4 = sub i64 %3, 1
    store i64 %4, ptr %x, align 8
    %5 = load i64, ptr %x, align 8
    ; Print the value of %5
    ;call i32 (ptr, ...) @printf(ptr noundef @.str, i64 noundef %5)
    %6=call i32 (ptr, ...) @printf(ptr noundef @.println, i64 noundef %5)
    %7 = icmp sgt i64 %5, 0
    br i1 %7, label %L0, label %L1

L1:
    ret i64 %5
}

