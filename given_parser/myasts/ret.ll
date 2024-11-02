target triple = "x86_64-apple-macosx14.0.0"


define noundef i64 @main() {
        %x = alloca i64, align 8
        %_ret = alloca i64, align 8
        store i64 3, ptr %x, align 8
        %3 = load i64, ptr %x, align 8
        ret i64 %3
        store i64 %3, ptr %_ret, align 8
        br label %Lreturn


        Lreturn:
        %5 = load i64, ptr %_ret, align 8
        ret i64 %5

}

