target triple = "x86_64-apple-macosx14.0.0"

@var = global i64 97, align 4

define noundef i64 @_Z3foov() { 
  %1 = alloca i64, align 4
  store i64 3, ptr %1, align 4
  %2 = load i64, ptr %1, align 4
  ret i64 %2
}

define noundef i64 @main() {
    %ret = call noundef i64 @_Z3foov()
    ret i64 %ret
}
