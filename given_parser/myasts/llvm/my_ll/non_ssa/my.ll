target triple = "x86_64-apple-macosx14.0.0"
define noundef i64 @main() {
entry:
    %x = alloca i64, align 8
    %y = alloca i64, align 8
L0:
    store i64 3, ptr %y, align 8
    %1 = load i64, ptr %y, align 8
L1:
    store i64 %1, ptr %x, align 8
    %2 = load i64, ptr %x, align 8
ret i64 %2
}
