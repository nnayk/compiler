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
	br label %L3

	L2:
	br label %L3

	L3:
	%2 = phi i64 [ 7, %L2 ],[ 9, %L1 ]
	%3 = add i64 3, %2
	%4 = add i64 %3, 9
	call i32 (ptr, ...) @printf(ptr noundef @.print, i64 noundef %4)
	br label %L4


	L4:
	ret i64 9

}

