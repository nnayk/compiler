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

	L0:
	%1 = icmp sgt i64 9, 0
	br i1 %1, label %L1, label %L4


	L1:
	br i1 1, label %L2, label %L3


	L2:
	call i32 (ptr, ...) @printf(ptr noundef @.print, i64 noundef 3)
	br i1 1, label %L2, label %L3


	L3:
	br label %L5

	L4:
	call i32 (ptr, ...) @printf(ptr noundef @.print, i64 noundef 2)
	br label %L5

	L5:
	br label %L6


	L6:
	ret i64 5

}

