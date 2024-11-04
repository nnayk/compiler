target triple = "x86_64-apple-macosx14.0.0"

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define noundef i32 @_Z6simpleii(i32 noundef %a, i32 noundef %b) {
  %tmp0 = add nsw i32 %a, %b
  ret i32 %tmp0
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define noundef i32 @_Z7compare() {
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  %ret = alloca i32, align 4
  store i32 3, ptr %x, align 4
  store i32 76, ptr %y, align 4
  %tmp0 = load i32, ptr %x, align 4
  %tmp1 = load i32, ptr %y, align 4
  %tmp2 = icmp sgt i32 %tmp0, %tmp1
  br i1 %tmp2, label %then, label %el

then:                                                ; preds = %0
  store i32 19, ptr %ret, align 4
  br label %after

el:                                                ; preds = %0
  store i32 34, ptr %ret, align 4
  br label %after

after:                                                ; preds = %8, %7
  %val = load i32, ptr %ret, align 4
  ret i32 %val
}

; Function Attrs: mustprogress noinline norecurse nounwind optnone ssp uwtable
define noundef i32 @main(i32 noundef %0, ptr noundef %1) {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca ptr, align 8
  store i32 0, ptr %3, align 4
  store i32 %0, ptr %4, align 4
  store ptr %1, ptr %5, align 8
  %6 = call noundef i32 compare()
  ret i32 %6
}
