target triple = "x86_64-apple-macosx14.0.0"
declare i8* @malloc(i32)
declare void @free(ptr)
declare i64 @printf(ptr, ...)
declare i64 @scanf(ptr, ...)
@.println = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.print = private unnamed_addr constant [5 x i8] c"%ld \00", align 1
@.read = private unnamed_addr constant [4 x i8] c"%ld\00", align 1
@.read_scratch = common global i32 0, align 4
              

define noundef i64 @isqrt(i64 noundef %a) {

	L0:
	%7 = icmp sle i64 %4, %6
	br i1 %7, label %L1, label %L2


	L1:
	%2 = phi i64 [ %4, %L1 ],[ 1, %L0 ]
	%3 = phi i64 [ %5, %L1 ],[ 3, %L0 ]
	%6 = phi i64 [ %6, %L1 ],[ %a, %L0 ]
	%4 = add i64 %2, %3
	%5 = add i64 %3, 2
	%7 = icmp sle i64 %4, %6
	br i1 %7, label %L1, label %L2


	L2:
	%8 = phi i64 [ 3, %L0 ],[ %5, %L1 ]
	%9 = sdiv i64 %8, 2
	%10 = sub i64 %9, 1
	br label %L3


	L3:
	ret i64 %10

}

define noundef i8 @prime(i64 noundef %a) {

	L4:
	%11 = icmp slt i64 %a, 2
	br i1 %11, label %L5, label %L6


	L5:
	br label %L12


	L6:
	%12 = call i64 @isqrt(i64 noundef %a)
	%24 = icmp sle i64 %21, %22
	br i1 %24, label %L7, label %L10


	L7:
	%14 = phi i64 [ %26, %L9 ],[ %a, %L6 ]
	%15 = phi i64 [ %21, %L9 ],[ 2, %L6 ]
	%22 = phi i64 [ %23, %L9 ],[ %12, %L6 ]
	%16 = sdiv i64 %14, %15
	%17 = mul i64 %16, %15
	%18 = sub i64 %14, %17
	%19 = icmp eq i64 %18, 0
	br i1 %19, label %L8, label %L9


	L8:
	br label %L12


	L9:
	%21 = add i64 %15, 1
	%24 = icmp sle i64 %21, %22
	br i1 %24, label %L7, label %L10


	L10:
	br label %L12


	L11:


	L12:
	%25 = phi i8 [ 1, %L10 ],[ 0, %L8 ],[ 0, %L5 ]
	ret i8 %25

}

define noundef i64 @main() {

	L13:
	%35 = icmp sle i64 %32, %33
	br i1 %35, label %L14, label %L17


	L14:
	%28 = phi i64 [ %32, %L16 ],[ 0, %L13 ]
	%33 = phi i64 [ %34, %L16 ],[ 6, %L13 ]
	%29 = call i8 @prime(i64 noundef %28)
	br i1 %29, label %L15, label %L16


	L15:
	call i32 (ptr, ...) @printf(ptr noundef @.println, i64 noundef %28)
	br label %L16

	L16:
	%32 = add i64 %28, 1
	%35 = icmp sle i64 %32, %33
	br i1 %35, label %L14, label %L17


	L17:
	br label %L18


	L18:
	ret i64 0

}

