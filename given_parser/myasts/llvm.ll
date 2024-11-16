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
	%5 = icmp sgt i64 %4, 0
	br i1 %5, label %L1, label %L2


	L1:
	%2 = phi i64 [ 3, %L0 ]
	call i32 (ptr, ...) @printf(ptr noundef @.print, i64 noundef %2)
	%4 = sub i64 %2, 1
	%5 = icmp sgt i64 %4, 0
	br i1 %5, label %L1, label %L2


	L2:
	%7 = phi i64 [ 3, %L0 ],[ %4, %L1 ]
	call i32 (ptr, ...) @printf(ptr noundef @.print, i64 noundef 5)
	%8 = sdiv i64 99, %7
	br label %L3


	L3:
	ret i64 %8

}

