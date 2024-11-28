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
	%1 = icmp sgt i64 3, 5
	br i1 %1, label %L1, label %L2


	L1:
	%2 = add i64 2, 4
	%3 = sub i64 9, 8
	br label %L3

	L2:
	%4 = add i64 7, 8
	br label %L3

	L3:
	%5 = phi i64 [ %4, %L2 ],[ %3, %L1 ]
	%6 = add i64 3, %5
	%7 = add i64 %6, 9
	call i32 (ptr, ...) @printf(ptr noundef @.print, i64 noundef %7)
	%9 = mul i64 9, %6
	br label %L4


	L4:
	ret i64 %9

}

