 %arr = alloca i64*
        %index = alloca i64
        %r0 = alloca [10 x i64]
        %r1 = bitcast [10 x i64]* %r0 to i64*
        store i64* %r1, i64** %arr
        store i64 0, i64* %index
        %r2 = load i64, i64* %index
        %r3 = load i64*, i64** %arr
        %r4 = getelementptr inbounds i64, i64* %r3, i64 %r2
        store i64 42, i64* %r4
