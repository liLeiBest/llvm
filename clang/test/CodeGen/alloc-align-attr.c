// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %clang_cc1 -triple x86_64-pc-linux -emit-llvm -o - %s | FileCheck %s

__INT32_TYPE__*m1(__INT32_TYPE__ i) __attribute__((alloc_align(1)));

// Condition where parameter to m1 is not size_t.
// CHECK-LABEL: define {{[^@]+}}@test1
// CHECK-SAME: (i32 [[A:%.*]]) #0
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A_ADDR:%.*]] = alloca i32, align 4
// CHECK-NEXT:    store i32 [[A]], i32* [[A_ADDR]], align 4
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[A_ADDR]], align 4
// CHECK-NEXT:    [[CALL:%.*]] = call i32* @m1(i32 [[TMP0]])
// CHECK-NEXT:    [[ALIGNMENTCAST:%.*]] = zext i32 [[TMP0]] to i64
// CHECK-NEXT:    [[MASK:%.*]] = sub i64 [[ALIGNMENTCAST]], 1
// CHECK-NEXT:    [[PTRINT:%.*]] = ptrtoint i32* [[CALL]] to i64
// CHECK-NEXT:    [[MASKEDPTR:%.*]] = and i64 [[PTRINT]], [[MASK]]
// CHECK-NEXT:    [[MASKCOND:%.*]] = icmp eq i64 [[MASKEDPTR]], 0
// CHECK-NEXT:    call void @llvm.assume(i1 [[MASKCOND]])
// CHECK-NEXT:    [[TMP1:%.*]] = load i32, i32* [[CALL]], align 4
// CHECK-NEXT:    ret i32 [[TMP1]]
//
__INT32_TYPE__ test1(__INT32_TYPE__ a) {
  return *m1(a);
}
// Condition where test2 param needs casting.
// CHECK-LABEL: define {{[^@]+}}@test2
// CHECK-SAME: (i64 [[A:%.*]]) #0
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A_ADDR:%.*]] = alloca i64, align 8
// CHECK-NEXT:    store i64 [[A]], i64* [[A_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load i64, i64* [[A_ADDR]], align 8
// CHECK-NEXT:    [[CONV:%.*]] = trunc i64 [[TMP0]] to i32
// CHECK-NEXT:    [[CALL:%.*]] = call i32* @m1(i32 [[CONV]])
// CHECK-NEXT:    [[ALIGNMENTCAST:%.*]] = zext i32 [[CONV]] to i64
// CHECK-NEXT:    [[MASK:%.*]] = sub i64 [[ALIGNMENTCAST]], 1
// CHECK-NEXT:    [[PTRINT:%.*]] = ptrtoint i32* [[CALL]] to i64
// CHECK-NEXT:    [[MASKEDPTR:%.*]] = and i64 [[PTRINT]], [[MASK]]
// CHECK-NEXT:    [[MASKCOND:%.*]] = icmp eq i64 [[MASKEDPTR]], 0
// CHECK-NEXT:    call void @llvm.assume(i1 [[MASKCOND]])
// CHECK-NEXT:    [[TMP1:%.*]] = load i32, i32* [[CALL]], align 4
// CHECK-NEXT:    ret i32 [[TMP1]]
//
__INT32_TYPE__ test2(__SIZE_TYPE__ a) {
  return *m1(a);
}
__INT32_TYPE__ *m2(__SIZE_TYPE__ i) __attribute__((alloc_align(1)));

// test3 param needs casting, but 'm2' is correct.
// CHECK-LABEL: define {{[^@]+}}@test3
// CHECK-SAME: (i32 [[A:%.*]]) #0
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A_ADDR:%.*]] = alloca i32, align 4
// CHECK-NEXT:    store i32 [[A]], i32* [[A_ADDR]], align 4
// CHECK-NEXT:    [[TMP0:%.*]] = load i32, i32* [[A_ADDR]], align 4
// CHECK-NEXT:    [[CONV:%.*]] = sext i32 [[TMP0]] to i64
// CHECK-NEXT:    [[CALL:%.*]] = call i32* @m2(i64 [[CONV]])
// CHECK-NEXT:    [[MASK:%.*]] = sub i64 [[CONV]], 1
// CHECK-NEXT:    [[PTRINT:%.*]] = ptrtoint i32* [[CALL]] to i64
// CHECK-NEXT:    [[MASKEDPTR:%.*]] = and i64 [[PTRINT]], [[MASK]]
// CHECK-NEXT:    [[MASKCOND:%.*]] = icmp eq i64 [[MASKEDPTR]], 0
// CHECK-NEXT:    call void @llvm.assume(i1 [[MASKCOND]])
// CHECK-NEXT:    [[TMP1:%.*]] = load i32, i32* [[CALL]], align 4
// CHECK-NEXT:    ret i32 [[TMP1]]
//
__INT32_TYPE__ test3(__INT32_TYPE__ a) {
  return *m2(a);
}

// Every type matches, canonical example.
// CHECK-LABEL: define {{[^@]+}}@test4
// CHECK-SAME: (i64 [[A:%.*]]) #0
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A_ADDR:%.*]] = alloca i64, align 8
// CHECK-NEXT:    store i64 [[A]], i64* [[A_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load i64, i64* [[A_ADDR]], align 8
// CHECK-NEXT:    [[CALL:%.*]] = call i32* @m2(i64 [[TMP0]])
// CHECK-NEXT:    [[MASK:%.*]] = sub i64 [[TMP0]], 1
// CHECK-NEXT:    [[PTRINT:%.*]] = ptrtoint i32* [[CALL]] to i64
// CHECK-NEXT:    [[MASKEDPTR:%.*]] = and i64 [[PTRINT]], [[MASK]]
// CHECK-NEXT:    [[MASKCOND:%.*]] = icmp eq i64 [[MASKEDPTR]], 0
// CHECK-NEXT:    call void @llvm.assume(i1 [[MASKCOND]])
// CHECK-NEXT:    [[TMP1:%.*]] = load i32, i32* [[CALL]], align 4
// CHECK-NEXT:    ret i32 [[TMP1]]
//
__INT32_TYPE__ test4(__SIZE_TYPE__ a) {
  return *m2(a);
}


struct Empty {};
struct MultiArgs { __INT64_TYPE__ a, b;};
// Struct parameter doesn't take up an IR parameter, 'i' takes up 2.
// Truncation to i64 is permissible, since alignments of greater than 2^64 are insane.
__INT32_TYPE__ *m3(struct Empty s, __int128_t i) __attribute__((alloc_align(2)));
// CHECK-LABEL: define {{[^@]+}}@test5
// CHECK-SAME: (i64 [[A_COERCE0:%.*]], i64 [[A_COERCE1:%.*]]) #0
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A:%.*]] = alloca i128, align 16
// CHECK-NEXT:    [[A_ADDR:%.*]] = alloca i128, align 16
// CHECK-NEXT:    [[E:%.*]] = alloca [[STRUCT_EMPTY:%.*]], align 1
// CHECK-NEXT:    [[COERCE:%.*]] = alloca i128, align 16
// CHECK-NEXT:    [[TMP0:%.*]] = bitcast i128* [[A]] to { i64, i64 }*
// CHECK-NEXT:    [[TMP1:%.*]] = getelementptr inbounds { i64, i64 }, { i64, i64 }* [[TMP0]], i32 0, i32 0
// CHECK-NEXT:    store i64 [[A_COERCE0]], i64* [[TMP1]], align 16
// CHECK-NEXT:    [[TMP2:%.*]] = getelementptr inbounds { i64, i64 }, { i64, i64 }* [[TMP0]], i32 0, i32 1
// CHECK-NEXT:    store i64 [[A_COERCE1]], i64* [[TMP2]], align 8
// CHECK-NEXT:    [[A1:%.*]] = load i128, i128* [[A]], align 16
// CHECK-NEXT:    store i128 [[A1]], i128* [[A_ADDR]], align 16
// CHECK-NEXT:    [[TMP3:%.*]] = load i128, i128* [[A_ADDR]], align 16
// CHECK-NEXT:    store i128 [[TMP3]], i128* [[COERCE]], align 16
// CHECK-NEXT:    [[TMP4:%.*]] = bitcast i128* [[COERCE]] to { i64, i64 }*
// CHECK-NEXT:    [[TMP5:%.*]] = getelementptr inbounds { i64, i64 }, { i64, i64 }* [[TMP4]], i32 0, i32 0
// CHECK-NEXT:    [[TMP6:%.*]] = load i64, i64* [[TMP5]], align 16
// CHECK-NEXT:    [[TMP7:%.*]] = getelementptr inbounds { i64, i64 }, { i64, i64 }* [[TMP4]], i32 0, i32 1
// CHECK-NEXT:    [[TMP8:%.*]] = load i64, i64* [[TMP7]], align 8
// CHECK-NEXT:    [[CALL:%.*]] = call i32* @m3(i64 [[TMP6]], i64 [[TMP8]])
// CHECK-NEXT:    [[ALIGNMENTCAST:%.*]] = trunc i128 [[TMP3]] to i64
// CHECK-NEXT:    [[MASK:%.*]] = sub i64 [[ALIGNMENTCAST]], 1
// CHECK-NEXT:    [[PTRINT:%.*]] = ptrtoint i32* [[CALL]] to i64
// CHECK-NEXT:    [[MASKEDPTR:%.*]] = and i64 [[PTRINT]], [[MASK]]
// CHECK-NEXT:    [[MASKCOND:%.*]] = icmp eq i64 [[MASKEDPTR]], 0
// CHECK-NEXT:    call void @llvm.assume(i1 [[MASKCOND]])
// CHECK-NEXT:    [[TMP9:%.*]] = load i32, i32* [[CALL]], align 4
// CHECK-NEXT:    ret i32 [[TMP9]]
//
__INT32_TYPE__ test5(__int128_t a) {
  struct Empty e;
  return *m3(e, a);
}
// Struct parameter takes up 2 parameters, 'i' takes up 2.
__INT32_TYPE__ *m4(struct MultiArgs s, __int128_t i) __attribute__((alloc_align(2)));
// CHECK-LABEL: define {{[^@]+}}@test6
// CHECK-SAME: (i64 [[A_COERCE0:%.*]], i64 [[A_COERCE1:%.*]]) #0
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A:%.*]] = alloca i128, align 16
// CHECK-NEXT:    [[A_ADDR:%.*]] = alloca i128, align 16
// CHECK-NEXT:    [[E:%.*]] = alloca [[STRUCT_MULTIARGS:%.*]], align 8
// CHECK-NEXT:    [[COERCE:%.*]] = alloca i128, align 16
// CHECK-NEXT:    [[TMP0:%.*]] = bitcast i128* [[A]] to { i64, i64 }*
// CHECK-NEXT:    [[TMP1:%.*]] = getelementptr inbounds { i64, i64 }, { i64, i64 }* [[TMP0]], i32 0, i32 0
// CHECK-NEXT:    store i64 [[A_COERCE0]], i64* [[TMP1]], align 16
// CHECK-NEXT:    [[TMP2:%.*]] = getelementptr inbounds { i64, i64 }, { i64, i64 }* [[TMP0]], i32 0, i32 1
// CHECK-NEXT:    store i64 [[A_COERCE1]], i64* [[TMP2]], align 8
// CHECK-NEXT:    [[A1:%.*]] = load i128, i128* [[A]], align 16
// CHECK-NEXT:    store i128 [[A1]], i128* [[A_ADDR]], align 16
// CHECK-NEXT:    [[TMP3:%.*]] = load i128, i128* [[A_ADDR]], align 16
// CHECK-NEXT:    [[TMP4:%.*]] = bitcast %struct.MultiArgs* [[E]] to { i64, i64 }*
// CHECK-NEXT:    [[TMP5:%.*]] = getelementptr inbounds { i64, i64 }, { i64, i64 }* [[TMP4]], i32 0, i32 0
// CHECK-NEXT:    [[TMP6:%.*]] = load i64, i64* [[TMP5]], align 8
// CHECK-NEXT:    [[TMP7:%.*]] = getelementptr inbounds { i64, i64 }, { i64, i64 }* [[TMP4]], i32 0, i32 1
// CHECK-NEXT:    [[TMP8:%.*]] = load i64, i64* [[TMP7]], align 8
// CHECK-NEXT:    store i128 [[TMP3]], i128* [[COERCE]], align 16
// CHECK-NEXT:    [[TMP9:%.*]] = bitcast i128* [[COERCE]] to { i64, i64 }*
// CHECK-NEXT:    [[TMP10:%.*]] = getelementptr inbounds { i64, i64 }, { i64, i64 }* [[TMP9]], i32 0, i32 0
// CHECK-NEXT:    [[TMP11:%.*]] = load i64, i64* [[TMP10]], align 16
// CHECK-NEXT:    [[TMP12:%.*]] = getelementptr inbounds { i64, i64 }, { i64, i64 }* [[TMP9]], i32 0, i32 1
// CHECK-NEXT:    [[TMP13:%.*]] = load i64, i64* [[TMP12]], align 8
// CHECK-NEXT:    [[CALL:%.*]] = call i32* @m4(i64 [[TMP6]], i64 [[TMP8]], i64 [[TMP11]], i64 [[TMP13]])
// CHECK-NEXT:    [[ALIGNMENTCAST:%.*]] = trunc i128 [[TMP3]] to i64
// CHECK-NEXT:    [[MASK:%.*]] = sub i64 [[ALIGNMENTCAST]], 1
// CHECK-NEXT:    [[PTRINT:%.*]] = ptrtoint i32* [[CALL]] to i64
// CHECK-NEXT:    [[MASKEDPTR:%.*]] = and i64 [[PTRINT]], [[MASK]]
// CHECK-NEXT:    [[MASKCOND:%.*]] = icmp eq i64 [[MASKEDPTR]], 0
// CHECK-NEXT:    call void @llvm.assume(i1 [[MASKCOND]])
// CHECK-NEXT:    [[TMP14:%.*]] = load i32, i32* [[CALL]], align 4
// CHECK-NEXT:    ret i32 [[TMP14]]
//
__INT32_TYPE__ test6(__int128_t a) {
  struct MultiArgs e;
  return *m4(e, a);
}

