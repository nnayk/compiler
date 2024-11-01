target triple = "x86_64-apple-macosx14.0.0"
;declare i8* @malloc(i32)
;declare void @free(i8*)
declare i32 @printf(ptr, ...)
;declare i32 @scanf(i8*, ...)
@.println = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.print = private unnamed_addr constant [5 x i8] c"%ld \00", align 1
@.read = private unnamed_addr constant [4 x i8] c"%ld\00", align 1
@.read_scratch = common global i32 0, align 4

define noundef i64 @main() {
        %x = alloca i64, align 8
        store i64 3, ptr %x, align 8
        %1 = load i64, ptr %x, align 8
        call i32 (ptr, ...) @printf(ptr noundef @.print, i64 noundef %1)
        %3 = load i64, ptr %x, align 8
        %4 = add i64 %3, 3
        %5 = sub i64 %4, 2
        call i32 (ptr, ...) @printf(ptr noundef @.println, i64 noundef %5)
		ret i64 %5
}
