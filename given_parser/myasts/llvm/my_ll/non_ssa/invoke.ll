target triple = "x86_64-apple-macosx14.0.0"

define noundef i64 @foo(i64 noundef %x, i8 noundef %y) {
	ret i64 86 
}
define noundef i64 @main() {
        %arg2 = alloca i8, align 1
        store i8 0, ptr %arg2, align 1
        %1 = load i8, ptr %arg2, align 1
        %2 = call i64 @foo(i64 noundef 3, i8 noundef %1)
		ret i64 %2
}
