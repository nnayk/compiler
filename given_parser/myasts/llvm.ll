target triple = "x86_64-apple-macosx14.0.0"
declare i8* @malloc(i32)
declare void @free(i8*)
declare i32 @printf(i8*, ...)
declare i32 @scanf(i8*, ...)
@.println = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.print = private unnamed_addr constant [5 x i8] c"%ld \00", align 1
@.read = private unnamed_addr constant [4 x i8] c"%ld\00", align 1
@.read_scratch = common global i32 0, align 4
              

define noundef i8 @foo() {

	L0:
	%1 = xor i1 0, 1
	br label %L1


	L1:
	ret i8 %1

}

