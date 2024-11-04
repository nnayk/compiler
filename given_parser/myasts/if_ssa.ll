target triple = "x86_64-apple-macosx14.0.0"


define noundef i64 @main() {
    ;%x = alloca i64, align 8
    ;store i64 3, ptr %x, align 8
    %2 = icmp sgt i64 3, 5
    br i1 %2, label %L0, label %L1


    L0:
    br label %L2


    L1:
    br label %L2


    L2:
    %3 = phi i64 [9, %L0], [7, %L1]
    %4 = add i64 3, %3
	
	ret i64 %4
}
