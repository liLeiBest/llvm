; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt < %s -instcombine -S | FileCheck %s

declare void @use8(i8)
declare void @use1(i1)

; Basic case - all good.
define i8 @p0(i8 %x, i8 %v0, i8 %v1) {
; CHECK-LABEL: @p0(
; CHECK-NEXT:    [[T0:%.*]] = and i8 [[X:%.*]], 1
; CHECK-NEXT:    [[T1_NOT:%.*]] = icmp eq i8 [[T0]], 0
; CHECK-NEXT:    [[R:%.*]] = select i1 [[T1_NOT]], i8 [[V1:%.*]], i8 [[V0:%.*]], !prof !0
; CHECK-NEXT:    ret i8 [[R]]
;
  %t0 = and i8 %x, 1
  %t1 = icmp eq i8 %t0, 1
  %r = select i1 %t1, i8 %v0, i8 %v1, !prof !0
  ret i8 %r
}
define i8 @p1(i8 %x, i8 %v0, i8 %v1) {
; CHECK-LABEL: @p1(
; CHECK-NEXT:    [[T0:%.*]] = and i8 [[X:%.*]], 1
; CHECK-NEXT:    [[T1_NOT:%.*]] = icmp eq i8 [[T0]], 0
; CHECK-NEXT:    [[R:%.*]] = select i1 [[T1_NOT]], i8 [[V1:%.*]], i8 [[V0:%.*]]
; CHECK-NEXT:    ret i8 [[R]]
;
  %t0 = and i8 %x, 1
  %t1 = icmp ne i8 %t0, 0
  %r = select i1 %t1, i8 %v0, i8 %v1
  ret i8 %r
}

; Can't invert all users of original condition
define i8 @n2(i8 %x, i8 %v0, i8 %v1) {
; CHECK-LABEL: @n2(
; CHECK-NEXT:    [[T0:%.*]] = and i8 [[X:%.*]], 1
; CHECK-NEXT:    [[T1:%.*]] = icmp ne i8 [[T0]], 0
; CHECK-NEXT:    call void @use1(i1 [[T1]])
; CHECK-NEXT:    [[R:%.*]] = select i1 [[T1]], i8 [[V0:%.*]], i8 [[V1:%.*]]
; CHECK-NEXT:    ret i8 [[R]]
;
  %t0 = and i8 %x, 1
  %t1 = icmp eq i8 %t0, 1
  call void @use1(i1 %t1) ; condition has un-invertable use
  %r = select i1 %t1, i8 %v0, i8 %v1
  ret i8 %r
}

; Extra use can be adjusted. While there, test multi-bb case.
define i8 @t3(i8 %x, i8 %v0, i8 %v1, i8 %v2, i8 %v3, i8* %out, i1 %c) {
; CHECK-LABEL: @t3(
; CHECK-NEXT:  bb0:
; CHECK-NEXT:    [[T0:%.*]] = and i8 [[X:%.*]], 1
; CHECK-NEXT:    [[T1_NOT:%.*]] = icmp eq i8 [[T0]], 0
; CHECK-NEXT:    br i1 [[C:%.*]], label [[BB1:%.*]], label [[BB2:%.*]]
; CHECK:       bb1:
; CHECK-NEXT:    [[R0:%.*]] = select i1 [[T1_NOT]], i8 [[V1:%.*]], i8 [[V0:%.*]]
; CHECK-NEXT:    store i8 [[R0]], i8* [[OUT:%.*]], align 1
; CHECK-NEXT:    br label [[BB2]]
; CHECK:       bb2:
; CHECK-NEXT:    [[R1:%.*]] = select i1 [[T1_NOT]], i8 [[V3:%.*]], i8 [[V2:%.*]]
; CHECK-NEXT:    ret i8 [[R1]]
;
bb0:
  %t0 = and i8 %x, 1
  %t1 = icmp eq i8 %t0, 1
  br i1 %c, label %bb1, label %bb2
bb1:
  %r0 = select i1 %t1, i8 %v0, i8 %v1
  store i8 %r0, i8* %out
  br label %bb2
bb2:
  %r1 = select i1 %t1, i8 %v2, i8 %v3
  ret i8 %r1
}
define i8 @t4(i8 %x, i8 %v0, i8 %v1, i8 %v2, i8 %v3, i8* %out) {
; CHECK-LABEL: @t4(
; CHECK-NEXT:    [[T0:%.*]] = and i8 [[X:%.*]], 1
; CHECK-NEXT:    [[T1_NOT:%.*]] = icmp eq i8 [[T0]], 0
; CHECK-NEXT:    [[R0:%.*]] = select i1 [[T1_NOT]], i8 [[V1:%.*]], i8 [[V0:%.*]]
; CHECK-NEXT:    store i8 [[R0]], i8* [[OUT:%.*]], align 1
; CHECK-NEXT:    [[R1:%.*]] = select i1 [[T1_NOT]], i8 [[V3:%.*]], i8 [[V2:%.*]]
; CHECK-NEXT:    ret i8 [[R1]]
;
  %t0 = and i8 %x, 1
  %t1 = icmp ne i8 %t0, 0
  %r0 = select i1 %t1, i8 %v0, i8 %v1
  store i8 %r0, i8* %out
  %r1 = select i1 %t1, i8 %v2, i8 %v3
  ret i8 %r1
}

; Weird comparisons
define i8 @n5(i8 %x, i8 %v0, i8 %v1) {
; CHECK-LABEL: @n5(
; CHECK-NEXT:    ret i8 [[V1:%.*]]
;
  %t0 = and i8 %x, 1
  %t1 = icmp eq i8 %t0, 2 ; checking some other bit
  %r = select i1 %t1, i8 %v0, i8 %v1
  ret i8 %r
}
define i8 @n6(i8 %x, i8 %v0, i8 %v1) {
; CHECK-LABEL: @n6(
; CHECK-NEXT:    ret i8 [[V1:%.*]]
;
  %t0 = and i8 %x, 1
  %t1 = icmp eq i8 %t0, 3 ; checking some other bit
  %r = select i1 %t1, i8 %v0, i8 %v1
  ret i8 %r
}
define i8 @n7(i8 %x, i8 %v0, i8 %v1) {
; CHECK-LABEL: @n7(
; CHECK-NEXT:    [[T0:%.*]] = and i8 [[X:%.*]], 1
; CHECK-NEXT:    [[T1_NOT_NOT:%.*]] = icmp eq i8 [[T0]], 0
; CHECK-NEXT:    [[R:%.*]] = select i1 [[T1_NOT_NOT]], i8 [[V0:%.*]], i8 [[V1:%.*]]
; CHECK-NEXT:    ret i8 [[R]]
;
  %t0 = and i8 %x, 1
  %t1 = icmp ne i8 %t0, 1 ; not checking that it's zero
  %r = select i1 %t1, i8 %v0, i8 %v1
  ret i8 %r
}

; Potentially have more than a single bit set
define i8 @n8(i8 %x, i8 %v0, i8 %v1) {
; CHECK-LABEL: @n8(
; CHECK-NEXT:    [[T0:%.*]] = and i8 [[X:%.*]], 3
; CHECK-NEXT:    [[T1:%.*]] = icmp eq i8 [[T0]], 1
; CHECK-NEXT:    [[R:%.*]] = select i1 [[T1]], i8 [[V0:%.*]], i8 [[V1:%.*]]
; CHECK-NEXT:    ret i8 [[R]]
;
  %t0 = and i8 %x, 3 ; Not a single bit
  %t1 = icmp eq i8 %t0, 1
  %r = select i1 %t1, i8 %v0, i8 %v1
  ret i8 %r
}

!0  = !{!"branch_weights", i32 0,  i32 100}

; Ensure that the branch metadata is reversed to match the reversals above.
; CHECK: !0 = {{.*}} i32 100, i32 0}
