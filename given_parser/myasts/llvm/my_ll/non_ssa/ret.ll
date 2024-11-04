; ModuleID = 'ret.cpp'
source_filename = "ret.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx14.0.0"

; Function Attrs: mustprogress noinline norecurse nounwind ssp uwtable
define noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 2, ptr %2, align 4
  %4 = load i32, ptr %2, align 4
  %5 = icmp sgt i32 %4, 0
  br i1 %5, label %6, label %8

6:                                                ; preds = %0
  %7 = load i32, ptr %2, align 4
  store i32 %7, ptr %1, align 4
  br label %14

8:                                                ; preds = %0
  store i32 4, ptr %3, align 4
  %9 = load i32, ptr %3, align 4
  %10 = icmp sgt i32 %9, 7
  br i1 %10, label %11, label %12

11:                                               ; preds = %8
  store i32 3, ptr %3, align 4
  br label %13

12:                                               ; preds = %8
  store i32 99, ptr %3, align 4
  br label %13

13:                                               ; preds = %12, %11
  store i32 5, ptr %1, align 4
  br label %14

14:                                               ; preds = %13, %6
  %15 = load i32, ptr %1, align 4
  ret i32 %15
}

attributes #0 = { mustprogress noinline norecurse nounwind ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"uwtable", i32 2}
!3 = !{i32 7, !"frame-pointer", i32 2}
!4 = !{!"Homebrew clang version 19.1.1"}
