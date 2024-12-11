; ModuleID = 'primes.c'
source_filename = "primes.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx14.0.0"

@.str = private unnamed_addr constant [4 x i8] c"%ld\00", align 1
@.str.1 = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1

; Function Attrs: nofree norecurse nosync nounwind ssp memory(none) uwtable
define range(i64 -4611686018427387905, 4611686018427387903) i64 @_mini_isqrt(i64 noundef %0) local_unnamed_addr #0 {
  %2 = icmp slt i64 %0, 1
  br i1 %2, label %12, label %3

3:                                                ; preds = %1, %3
  %4 = phi i64 [ %7, %3 ], [ 3, %1 ]
  %5 = phi i64 [ %6, %3 ], [ 1, %1 ]
  %6 = add nuw nsw i64 %4, %5
  %7 = add nuw nsw i64 %4, 2
  %8 = icmp sgt i64 %6, %0
  br i1 %8, label %9, label %3, !llvm.loop !5

9:                                                ; preds = %3
  %10 = lshr i64 %7, 1
  %11 = add nsw i64 %10, -1
  br label %12

12:                                               ; preds = %9, %1
  %13 = phi i64 [ 0, %1 ], [ %11, %9 ]
  ret i64 %13
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: nofree norecurse nosync nounwind ssp memory(none) uwtable
define range(i64 0, 2) i64 @_mini_prime(i64 noundef %0) local_unnamed_addr #0 {
  %2 = icmp slt i64 %0, 2
  br i1 %2, label %22, label %3

3:                                                ; preds = %1, %3
  %4 = phi i64 [ %10, %3 ], [ 2, %1 ]
  %5 = phi i64 [ %8, %3 ], [ 3, %1 ]
  %6 = phi i64 [ %7, %3 ], [ 1, %1 ]
  %7 = add nuw nsw i64 %6, %5
  %8 = add nuw nsw i64 %5, 2
  %9 = icmp sgt i64 %7, %0
  %10 = add i64 %4, 1
  br i1 %9, label %11, label %3, !llvm.loop !5

11:                                               ; preds = %3
  %12 = icmp ugt i64 %5, 3
  br i1 %12, label %13, label %22

13:                                               ; preds = %11
  %14 = tail call i64 @llvm.umax.i64(i64 %4, i64 3)
  br label %18

15:                                               ; preds = %18
  %16 = add nuw i64 %19, 1
  %17 = icmp eq i64 %16, %14
  br i1 %17, label %22, label %18, !llvm.loop !7

18:                                               ; preds = %13, %15
  %19 = phi i64 [ %16, %15 ], [ 2, %13 ]
  %20 = urem i64 %0, %19
  %21 = icmp eq i64 %20, 0
  br i1 %21, label %22, label %15

22:                                               ; preds = %18, %15, %11, %1
  %23 = phi i64 [ 0, %1 ], [ 1, %11 ], [ 0, %18 ], [ 1, %15 ]
  ret i64 %23
}

; Function Attrs: nofree nounwind ssp uwtable
define noundef i64 @_mini_main() local_unnamed_addr #2 {
  %1 = alloca i64, align 8
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %1) #5
  %2 = call i32 (ptr, ...) @scanf(ptr noundef nonnull @.str, ptr noundef nonnull %1)
  %3 = load i64, ptr %1, align 8, !tbaa !8
  %4 = icmp slt i64 %3, 0
  br i1 %4, label %35, label %5

5:                                                ; preds = %0, %31
  %6 = phi i64 [ %32, %31 ], [ %3, %0 ]
  %7 = phi i64 [ %33, %31 ], [ 0, %0 ]
  %8 = icmp ult i64 %7, 2
  br i1 %8, label %31, label %9

9:                                                ; preds = %5, %9
  %10 = phi i64 [ %16, %9 ], [ 2, %5 ]
  %11 = phi i64 [ %14, %9 ], [ 3, %5 ]
  %12 = phi i64 [ %13, %9 ], [ 1, %5 ]
  %13 = add nuw nsw i64 %12, %11
  %14 = add nuw nsw i64 %11, 2
  %15 = icmp ugt i64 %13, %7
  %16 = add i64 %10, 1
  br i1 %15, label %17, label %9, !llvm.loop !5

17:                                               ; preds = %9
  %18 = icmp ugt i64 %11, 3
  br i1 %18, label %19, label %28

19:                                               ; preds = %17
  %20 = call i64 @llvm.umax.i64(i64 %10, i64 3)
  br label %24

21:                                               ; preds = %24
  %22 = add nuw i64 %25, 1
  %23 = icmp eq i64 %22, %20
  br i1 %23, label %28, label %24, !llvm.loop !7

24:                                               ; preds = %21, %19
  %25 = phi i64 [ %22, %21 ], [ 2, %19 ]
  %26 = urem i64 %7, %25
  %27 = icmp eq i64 %26, 0
  br i1 %27, label %31, label %21

28:                                               ; preds = %21, %17
  %29 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.1, i64 noundef %7)
  %30 = load i64, ptr %1, align 8, !tbaa !8
  br label %31

31:                                               ; preds = %24, %5, %28
  %32 = phi i64 [ %6, %5 ], [ %30, %28 ], [ %6, %24 ]
  %33 = add nuw nsw i64 %7, 1
  %34 = icmp slt i64 %7, %32
  br i1 %34, label %5, label %35, !llvm.loop !12

35:                                               ; preds = %31, %0
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %1) #5
  ret i64 0
}

; Function Attrs: nofree nounwind
declare noundef i32 @scanf(ptr nocapture noundef readonly, ...) local_unnamed_addr #3

; Function Attrs: nofree nounwind
declare noundef i32 @printf(ptr nocapture noundef readonly, ...) local_unnamed_addr #3

; Function Attrs: nofree nounwind ssp uwtable
define noundef i32 @main() local_unnamed_addr #2 {
  %1 = alloca i64, align 8
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %1) #5
  %2 = call i32 (ptr, ...) @scanf(ptr noundef nonnull @.str, ptr noundef nonnull %1)
  %3 = load i64, ptr %1, align 8, !tbaa !8
  %4 = icmp slt i64 %3, 0
  br i1 %4, label %35, label %5

5:                                                ; preds = %0, %31
  %6 = phi i64 [ %32, %31 ], [ %3, %0 ]
  %7 = phi i64 [ %33, %31 ], [ 0, %0 ]
  %8 = icmp ult i64 %7, 2
  br i1 %8, label %31, label %9

9:                                                ; preds = %5, %9
  %10 = phi i64 [ %16, %9 ], [ 2, %5 ]
  %11 = phi i64 [ %14, %9 ], [ 3, %5 ]
  %12 = phi i64 [ %13, %9 ], [ 1, %5 ]
  %13 = add nuw nsw i64 %12, %11
  %14 = add nuw nsw i64 %11, 2
  %15 = icmp ugt i64 %13, %7
  %16 = add i64 %10, 1
  br i1 %15, label %17, label %9, !llvm.loop !5

17:                                               ; preds = %9
  %18 = icmp ugt i64 %11, 3
  br i1 %18, label %19, label %28

19:                                               ; preds = %17
  %20 = call i64 @llvm.umax.i64(i64 %10, i64 3)
  br label %24

21:                                               ; preds = %24
  %22 = add nuw i64 %25, 1
  %23 = icmp eq i64 %22, %20
  br i1 %23, label %28, label %24, !llvm.loop !7

24:                                               ; preds = %21, %19
  %25 = phi i64 [ %22, %21 ], [ 2, %19 ]
  %26 = urem i64 %7, %25
  %27 = icmp eq i64 %26, 0
  br i1 %27, label %31, label %21

28:                                               ; preds = %21, %17
  %29 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.1, i64 noundef %7)
  %30 = load i64, ptr %1, align 8, !tbaa !8
  br label %31

31:                                               ; preds = %24, %28, %5
  %32 = phi i64 [ %6, %5 ], [ %30, %28 ], [ %6, %24 ]
  %33 = add nuw nsw i64 %7, 1
  %34 = icmp slt i64 %7, %32
  br i1 %34, label %5, label %35, !llvm.loop !12

35:                                               ; preds = %31, %0
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %1) #5
  ret i32 0
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i64 @llvm.umax.i64(i64, i64) #4

attributes #0 = { nofree norecurse nosync nounwind ssp memory(none) uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { nofree nounwind ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #3 = { nofree nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cmov,+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #4 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #5 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"uwtable", i32 2}
!3 = !{i32 7, !"frame-pointer", i32 2}
!4 = !{!"Homebrew clang version 19.1.1"}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.mustprogress"}
!7 = distinct !{!7, !6}
!8 = !{!9, !9, i64 0}
!9 = !{!"long", !10, i64 0}
!10 = !{!"omnipotent char", !11, i64 0}
!11 = !{!"Simple C/C++ TBAA"}
!12 = distinct !{!12, !6}
