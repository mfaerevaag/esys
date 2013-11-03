define internal i32 @apply_mwi(i32* %sd, i32* %fd, i32 %count) nounwind uwtable {
  %1 = alloca i32*, align 8
  %2 = alloca i32*, align 8
  %3 = alloca i32, align 4
  %sum = alloca i32, align 4
  %i = alloca i32, align 4
  store i32* %sd, i32** %1, align 8
  store i32* %fd, i32** %2, align 8
  store i32 %count, i32* %3, align 4
  store i32 0, i32* %sum, align 4
  store i32 1, i32* %i, align 4
  br label %4

; <label>:4                                       ; preds = %19, %0
  %5 = load i32* %i, align 4
  %6 = icmp slt i32 %5, 30
  br i1 %6, label %7, label %22

; <label>:7                                       ; preds = %4
  %8 = load i32* %i, align 4
  %9 = sext i32 %8 to i64
  %10 = load i32** %1, align 8
  %11 = getelementptr inbounds i32* %10, i64 %9
  %12 = load i32* %11
  %13 = sitofp i32 %12 to double
  %14 = fdiv double %13, 3.000000e+01
  %15 = load i32* %sum, align 4
  %16 = sitofp i32 %15 to double
  %17 = fadd double %16, %14
  %18 = fptosi double %17 to i32
  store i32 %18, i32* %sum, align 4
  br label %19

; <label>:19                                      ; preds = %7
  %20 = load i32* %i, align 4
  %21 = add nsw i32 %20, 1
  store i32 %21, i32* %i, align 4
  br label %4

; <label>:22                                      ; preds = %4
  %23 = load i32* %sum, align 4
  ret i32 %23
}
