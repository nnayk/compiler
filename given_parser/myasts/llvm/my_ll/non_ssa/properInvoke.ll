target triple = "x86_64-apple-macosx14.0.0"

declare i8* @malloc(i32)

%struct.A = type { i64 }

define noundef i64 @foo(i64 noundef %x, i8 noundef %y, ptr noundef %obj) {
        %f = alloca i64, align 8
        %1 = getelementptr inbounds %struct.A, ptr %obj, i32 0, i32 0
        %2 = load i64, ptr %1, align 8
        %3 = add i64 %x, %2
        store i64 %3, ptr %f, align 8
		ret i64 %3
}
define noundef i64 @main() {
        %arg2 = alloca i8, align 1
        %q = alloca i64, align 8
        %data = alloca ptr, align 8
        %4 = load ptr, ptr %data, align 8
        %5 = getelementptr inbounds %struct.A, ptr %4, i32 0, i32 0
        store i64 96, ptr %5, align 8
        store i8 0, ptr %arg2, align 1
        %6 = load ptr, ptr %data, align 8
        %7 = call ptr @malloc(i64 noundef 8)
        store ptr %7, ptr %data, align 8
        %8 = load ptr, ptr %data, align 8
        %9 = getelementptr inbounds %struct.A, ptr %8, i32 0, i32 0
        store i64 99, ptr %9, align 8
        %10 = load i8, ptr %arg2, align 1
        %11 = load ptr, ptr %data, align 8
        %12 = call i64 @foo(i64 noundef 3, i8 noundef %10, ptr noundef %11)
        store i64 %12, ptr %q, align 8
		ret i64 %12
}

