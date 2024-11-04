target triple = "x86_64-apple-macosx14.0.0"


define noundef i64 @main() {
        %x = alloca i64, align 8
        store i64 6, ptr %x, align 8
        %1 = load i64, ptr %x, align 8
        %2 = icmp slt i64 %1, 2
        br i1 %2, label %L0, label %L1


        L0:
        %3 = load i64, ptr %x, align 8
        %4 = sdiv i64 %3, 2
        store i64 %4, ptr %x, align 8
        br label %L1


        L1:
        %5 = load i64, ptr %x, align 8
		ret i64 %5
}
