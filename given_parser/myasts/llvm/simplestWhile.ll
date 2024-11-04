target triple = "x86_64-apple-macosx14.0.0"

;@.str = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1 ; Format string for `printf` to print an i64

;declare i32 @printf(i8*, ...) ; Declare `printf`
@.print = private unnamed_addr constant [5 x i8] c"%ld \00", align 1


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
;		%format_str_ptr = bitcast [5 x i8]* @.str to i8* ; Cast the format string to i8* (required by printf)
;		call i32 (i8*, ...) @printf(i8* %format_str_ptr, i64 %5) ; Call printf with the format string and %5

        %6 = icmp sgt i64 %5, 0
        br i1 %6, label %L0, label %L1


        L1:
        ret i64 %5
}
