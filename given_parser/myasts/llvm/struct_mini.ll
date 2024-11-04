; ModuleID = 'struct_mini.cpp'
source_filename = "struct_mini.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx14.0.0"

%struct.A = type { i32, i32, i8, ptr }

@f = global i8 0, align 1
@abc = global i32 0, align 4

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define void @_Z3manv() #0 {
  %1 = alloca ptr, align 8
  %2 = alloca i32, align 4
  store i32 7, ptr %2, align 4
  store i8 1, ptr @f, align 1
  %3 = load ptr, ptr %1, align 8
  %4 = getelementptr inbounds %struct.A, ptr %3, i32 0, i32 0
  store i32 5, ptr %4, align 8
  %5 = load ptr, ptr %1, align 8
  %6 = getelementptr inbounds %struct.A, ptr %5, i32 0, i32 3
  %7 = load ptr, ptr %6, align 8
  %8 = getelementptr inbounds %struct.A, ptr %7, i32 0, i32 3
  %9 = load ptr, ptr %8, align 8
  %10 = getelementptr inbounds %struct.A, ptr %9, i32 0, i32 3
  %11 = load ptr, ptr %10, align 8
  %12 = getelementptr inbounds %struct.A, ptr %11, i32 0, i32 1
  store i32 5, ptr %12, align 4
  ret void
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define void @_Z3fooib1A(i32 noundef %0, i1 noundef zeroext %1, ptr noundef byval(%struct.A) align 8 %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i8, align 1
  %6 = alloca ptr, align 8
  store i32 %0, ptr %4, align 4
  %7 = zext i1 %1 to i8
  store i8 %7, ptr %5, align 1
  %8 = load ptr, ptr %6, align 8
  %9 = getelementptr inbounds %struct.A, ptr %8, i32 0, i32 0
  store i32 5, ptr %9, align 8
  ret void
}

attributes #0 = { mustprogress noinline nounwind optnone ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"uwtable", i32 2}
!3 = !{i32 7, !"frame-pointer", i32 2}
!4 = !{!"Homebrew clang version 19.1.1"}
