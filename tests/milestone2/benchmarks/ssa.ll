target triple = "x86_64-apple-macosx14.0.0"
declare i8* @malloc(i32)
declare void @free(ptr)
declare i64 @printf(ptr, ...)
declare i64 @scanf(ptr, ...)
@.println = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.print = private unnamed_addr constant [5 x i8] c"%ld \00", align 1
@.read = private unnamed_addr constant [4 x i8] c"%ld\00", align 1
@.read_scratch = common global i32 0, align 4
              

define noundef i64 @computeFib(i64 noundef %input) {

	L0:
	%1 = icmp eq i64 %input, 0
	br i1 %1, label %L1, label %L3


	L1:
	br label %L7


	L3:
	%2 = icmp sle i64 %input, 2
	br i1 %2, label %L4, label %L5


	L4:
	br label %L7


	L5:
	%3 = sub i64 %input, 1
	%5 = sub i64 %input, 2
	%7 = add i64 	%4 = call i64 @computeFib(i64 noundef %3)
, 	%6 = call i64 @computeFib(i64 noundef %5)

	br label %L7


	L6:
	br label %L2

	L2:


	L7:
	%8 = phi i64 [ %7, %L5 ],[ 1, %L4 ],[ 0, %L1 ]
	ret i64 %8

}

define noundef i64 @main() {

	L8:
	%9 = call i64 @computeFib(i64 noundef 3)
	call i32 (ptr, ...) @printf(ptr noundef @.println, i64 noundef %9)
	br label %L9


	L9:
	ret i64 0

}

