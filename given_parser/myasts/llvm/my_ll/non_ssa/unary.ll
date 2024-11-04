target triple = "x86_64-apple-macosx14.0.0"

define noundef i64  @main() {
        %x = alloca i64, align 8
        %y = alloca i8, align 1
        store i64 -5, ptr %x, align 8
        store i8 1, ptr %y, align 1
        ret i64 6
}
