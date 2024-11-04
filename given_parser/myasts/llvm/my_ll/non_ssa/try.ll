target triple = "x86_64-apple-macosx14.0.0"


define noundef i64 @main() {
    %x = alloca i64, align 8
    store i64 3, ptr %x, align 8
    %1 = load i64, ptr %x, align 8
    %2 = icmp sgt i64 %1, 5
    br i1 %2, label %L0, label %L1


    L0:
    store i64 2, ptr %x, align 8
    store i64 5, ptr %x, align 8
    store i64 9, ptr %x, align 8
    %3 = add i64 %1, 2
    br label %L2


    L1:
    store i64 4, ptr %x, align 8
    store i64 8, ptr %x, align 8
    store i64 7, ptr %x, align 8
    %3 = add i64 %1, 4 
    br label %L2


    L2:
    %4 = load i64, ptr %x, align 8
    %5 = add i64 3, %4
    store i64 %5, ptr %x, align 8
	
	ret i64 %4
}
