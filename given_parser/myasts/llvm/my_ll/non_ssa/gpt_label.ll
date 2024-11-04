target triple = "x86_64-apple-macosx14.0.0"
@.str = private unnamed_addr constant [21 x i8] c"x is greater than y\0A\00", align 1
@.str2 = private unnamed_addr constant [25 x i8] c"x is not greater than y\0A\00", align 1

declare i32 @printf(ptr, ...)

define i64 @main() {
entry:
  %x = alloca i64, align 8
  %y = alloca i64, align 8
  store i64 5, ptr %x, align 8
  store i64 10, ptr %y, align 8

  %x_val = load i64, ptr %x, align 8
  %y_val = load i64, ptr %y, align 8
  %cond = icmp sgt i64 %x_val, %y_val   ; compare x > y

  br i1 %cond, label %greater, label %not_greater

greater:                                   ; if x > y
  call i32 (ptr, ...) @printf(ptr @.str)   ; print "x is greater than y"
  br label %after_branch                   ; jump to after_branch

not_greater:                               ; if x <= y
  call i32 (ptr, ...) @printf(ptr @.str2)  ; print "x is not greater than y"
  br label %after_branch                   ; jump to after_branch

after_branch:                              ; after the conditional branch
  ; Additional code can go here if needed
  ret i64 0                                ; return 0 to end the program
}

