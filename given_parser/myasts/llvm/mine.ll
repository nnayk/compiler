target triple = "x86_64-apple-macosx14.0.0"
%struct.A = type { i64, i64, i8, ptr }
%struct.B = type { i64, i64, i8, ptr }

@data = global ptr null, align 8
@abc = global ptr null, align 8
@f = global i8 0, align 4

define noundef i64 @foo(i64 noundef %x, i8 noundef %y, ptr noundef %obj) {
    ret i64 7
}

define noundef i64 @main() {
    %r1 = call i64 @foo()
    ret i64 %r1
}
