target triple = "x86_64-apple-macosx14.0.0"
declare i8* @malloc(i32)
declare void @free(i8*)
declare i32 @printf(i8*, ...)
declare i32 @scanf(i8*, ...)
@.println = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.print = private unnamed_addr constant [5 x i8] c"%ld \00", align 1
@.read = private unnamed_addr constant [4 x i8] c"%ld\00", align 1
@.read_scratch = common global i32 0, align 4
              

define noundef i64 @foo(i64 noundef %a, i64 noundef %b, i64 noundef %c) {
	%ret = alloca i64, align 8
	%y = alloca i64, align 8

	L0:
	store i64 0, ptr %ret, align 8
	%1 = icmp sgt i64 %a, 0
	br i1 %1, label %L1, label %L6


	L1:
	store i64 1, ptr %ret, align 8
	%2 = icmp sgt i64 %b, 0
	br i1 %2, label %L2, label %L5


	L2:
	store i64 2, ptr %ret, align 8
	%3 = icmp sgt i64 %c, 0
	br i1 %3, label %L3, label %L4


	L3:
	store i64 3, ptr %ret, align 8
	br label %L4

	L4:
	call i32 (ptr, ...) @printf(ptr noundef @.print, i64 noundef 1)
	br label %L5

	L5:
	call i32 (ptr, ...) @printf(ptr noundef @.print, i64 noundef 2)
	br label %L7

	L6:
	store i64 5, ptr %y, align 8
	br label %L7

	L7:
	%6 = load i64, ptr %ret, align 8
	store i64 %6, ptr %_ret, align 8
	br label %L8


	L8:
	%7 = load i64, ptr %_ret, align 8
	ret i64 %7


