target triple = "x86_64-apple-macosx14.0.0"

define noundef i8 @main() {
        %x = alloca i64, align 8
        %y = alloca i64, align 8
        %z = alloca i64, align 8
        %le = alloca i8, align 1
        store i64 3, ptr %x, align 8
        store i64 4, ptr %y, align 8
        %1 = load i64, ptr %x, align 8
        %2 = load i64, ptr %y, align 8
        %3 = add i64 %1, %2
        store i64 %3, ptr %z, align 8
        %4 = load i64, ptr %z, align 8
        %5 = load i64, ptr %y, align 8
        %6 = icmp sle i64 %4, %5
        %7 = zext i1 %6 to i8
        store i8 %7, ptr %le, align 1
		ret i8 %7
}
