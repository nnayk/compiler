; ModuleID = 'foo.ll'
source_filename = "foo.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx14.0.0"

%struct.Shape = type { i32, ptr, i32, ptr, i8 }

@x = global i32 0, align 4
@y = global i32 0, align 4

; Function Attrs: mustprogress noinline norecurse ssp uwtable
define noundef i32 @main() #0 {
  %1 = call ptr @malloc(i64 noundef 40) #3
  %2 = getelementptr inbounds %struct.Shape, ptr %1, i32 0, i32 2
  store i32 5, ptr %2, align 8
  ret i32 98
}

; Function Attrs: allocsize(0)
declare ptr @malloc(i64 noundef) #1

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define void @_Z4tempv() #2 {
  ret void
}

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define noundef i32 @_Z3fooiii(i32 noundef %0, i32 noundef %1, i32 noundef %2) #2 {
  %4 = icmp ne i32 %0, 0
  br i1 %4, label %5, label %12

5:                                                ; preds = %3
  %6 = icmp ne i32 %1, 0
  br i1 %6, label %7, label %11

7:                                                ; preds = %5
  %8 = icmp ne i32 %2, 0
  br i1 %8, label %9, label %10

9:                                                ; preds = %7
  br label %10

10:                                               ; preds = %9, %7
  %.0 = phi i32 [ 3, %9 ], [ 2, %7 ]
  br label %11

11:                                               ; preds = %10, %5
  %.1 = phi i32 [ %.0, %10 ], [ 1, %5 ]
  br label %12

12:                                               ; preds = %11, %3
  %.2 = phi i32 [ %.1, %11 ], [ 0, %3 ]
  ret i32 %.2
}

; Function Attrs: mustprogress noinline nounwind ssp uwtable
define void @_Z4bluev() #2 {
  ret void
}

attributes #0 = { mustprogress noinline norecurse ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #1 = { allocsize(0) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress noinline nounwind ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #3 = { allocsize(0) }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"uwtable", i32 2}
!3 = !{i32 7, !"frame-pointer", i32 2}
!4 = !{!"Homebrew clang version 19.1.1"}
