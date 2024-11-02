target triple = "x86_64-apple-macosx14.0.0"
@.println = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
declare i32 @printf(ptr, ...)

define noundef i64 @main() {
	%x = alloca i64, align 8
	%y = alloca i64, align 8
	%_ret = alloca i64, align 8
	store i64 3, ptr %x, align 8
	store i64 0, ptr %y, align 8
	%1 = load i64, ptr %x, align 8
	%2 = icmp sgt i64 %1, 0
	br i1 %2, label %L0, label %L1


	L0:
	store i64 4, ptr %x, align 8
	store i64 5, ptr %x, align 8
	br label %L2


	L1:
	store i64 6, ptr %x, align 8
	store i64 7, ptr %x, align 8
	br label %L2


	L2:
	%3 = load i64, ptr %x, align 8
	%4 = icmp sgt i64 %3, 0
	br i1 %4, label %L3, label %L4


	L3:
	%5 = load i64, ptr %x, align 8
	%6 = sub i64 %5, 1
	store i64 %6, ptr %x, align 8
	%7 = load i64, ptr %y, align 8
	%8 = add i64 %7, 4
	store i64 %8, ptr %y, align 8
	%9 = load i64, ptr %x, align 8
    call i32(ptr,...) @printf(ptr noundef @.println, i64 noundef %8)
    ;call i32(ptr,...) @printf(ptr noundef @.println, i64 noundef %9)
	%11 = icmp sgt i64 %9, 0
	br i1 %11, label %L3, label %L4

 	L4:
	store i64 7, ptr %x, align 8
	store i64 12, ptr %_ret, align 8
	br label %Lreturn


	Lreturn:
	%12 = load i64, ptr %_ret, align 8
	ret i64 %12

}
