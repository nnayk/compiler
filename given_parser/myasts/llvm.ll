target triple = "x86_64-apple-macosx14.0.0"
declare i8* @malloc(i32)
declare void @free(ptr)
declare i64 @printf(ptr, ...)
declare i64 @scanf(ptr, ...)
@.println = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.print = private unnamed_addr constant [5 x i8] c"%ld \00", align 1
@.read = private unnamed_addr constant [4 x i8] c"%ld\00", align 1
@.read_scratch = common global i32 0, align 4
              

define noundef i64 @main() {
	%x = alloca i64, align 8

	L0:
	store i64 3, ptr %x, align 8
	%1 = load i64, ptr %x, align 8
	%2 = icmp sgt i64 %1, 5
	br i1 %2, label %L1, label %L2


	L1:
	store i64 1, ptr %_ret, align 8
	br label %L4


	L2:
	call i32 (ptr, ...) @printf(ptr noundef @.print, i64 noundef 5)
	br label %L3

	L3:
	call i32 (ptr, ...) @printf(ptr noundef @.print, i64 noundef 9)


	L4:
	%5 = load i64, ptr %_ret, align 8
	ret i64 %5

}

