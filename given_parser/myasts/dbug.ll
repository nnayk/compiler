target triple = "x86_64-apple-macosx14.0.0"
declare i8* @malloc(i32)
declare void @free(i8*)
declare i32 @printf(i8*, ...)
declare i32 @scanf(i8*, ...)
@.println = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.print = private unnamed_addr constant [5 x i8] c"%ld \00", align 1
@.read = private unnamed_addr constant [4 x i8] c"%ld\00", align 1
@.read_scratch = common global i32 0, align 4
              

define noundef i64 @main() {

	L0:
	%x = alloca i64, align 8
	%_ret = alloca i64, align 8
	store i64 3, ptr %x, align 8
	%1 = load i64, ptr %x, align 8
	%2 = icmp sgt i64 %1, 0
	br i1 %2, label %L1, label %L5


	L1:
	%3 = load i64, ptr %x, align 8
	%4 = sub i64 %3, 1
	store i64 %4, ptr %x, align 8
	%5 = load i64, ptr %x, align 8
	%6 = sdiv i64 %5, 2
	%7 = icmp eq i64 %6, 4
	br i1 %7, label %L2, label %L3


	L2:
	store i64 2, ptr %_ret, align 8
	br label %L4

	L3:
	%8 = load i64, ptr %x, align 8
	call i32 (ptr, ...) @printf(ptr noundef @.print, i64 noundef %8)
	br label %L4

	L4:
	%10 = load i64, ptr %x, align 8
	%11 = icmp sgt i64 %10, 0
	br i1 %11, label %L1, label %L5


	L5:
	call i32 (ptr, ...) @printf(ptr noundef @.print, i64 noundef 5)
	store i64 99, ptr %_ret, align 8
	br label %L6


	L6:
	%13 = load i64, ptr %_ret, align 8
	ret i64 %13
}
