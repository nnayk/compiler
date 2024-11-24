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
	%1 = icmp sgt i64 3, 0
	br i1 %1, label %L1, label %L2


	L1:
	br label %L3

	L2:
	br label %L3

	L3:
	%2 = phi i64 [ 7, %L2 ],[ 5, %L1 ]
	%6 = phi i64 [ 0, %L2 ],[ 0, %L1 ]
	%9 = icmp sgt i64 %5, 0
	br i1 %9, label %L4, label %L5


	L4:
	%4 = phi i64 [ %2, %L3 ]
	%7 = phi i64 [ %6, %L3 ]
	%5 = sub i64 %4, 1
	%8 = add i64 %7, 4
	%9 = icmp sgt i64 %5, 0
	br i1 %9, label %L4, label %L5


	L5:
	br label %L6


	L6:
	ret i64 %_ret

}

