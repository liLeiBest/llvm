# RUN: llvm-mc -triple=ve --show-encoding < %s \
# RUN:     | FileCheck %s --check-prefixes=CHECK-ENCODING,CHECK-INST
# RUN: llvm-mc -triple=ve -filetype=obj < %s | llvm-objdump -d - \
# RUN:     | FileCheck %s --check-prefixes=CHECK-INST

# CHECK-INST: b.l 8199
# CHECK-ENCODING: encoding: [0x07,0x20,0x00,0x00,0x00,0x00,0x0f,0x19]
b.l 8199

# CHECK-INST: b.l.t 20(, %s11)
# CHECK-ENCODING: encoding: [0x14,0x00,0x00,0x00,0x8b,0x00,0x3f,0x19]
b.l.t 20(, %s11)

# CHECK-INST: baf.l.nt -1(, %s11)
# CHECK-ENCODING: encoding: [0xff,0xff,0xff,0xff,0x8b,0x00,0x20,0x19]
baf.l.nt -1(, %s11)

# CHECK-INST: b.w.t 20(, %s11)
# CHECK-ENCODING: encoding: [0x14,0x00,0x00,0x00,0x8b,0x00,0x3f,0x1b]
b.w.t 20(, %s11)

# CHECK-INST: baf.d.nt -1(, %s11)
# CHECK-ENCODING: encoding: [0xff,0xff,0xff,0xff,0x8b,0x00,0x20,0x1c]
baf.d.nt -1(, %s11)

# CHECK-INST: b.s.t 20(, %s11)
# CHECK-ENCODING: encoding: [0x14,0x00,0x00,0x00,0x8b,0x00,0xbf,0x1c]
b.s.t 20(,%s11)

# CHECK-INST: bgt.d %s20, 20(, %s11)
# CHECK-ENCODING: encoding: [0x14,0x00,0x00,0x00,0x8b,0x94,0x01,0x1c]
bgt.d %s20, 20(, %s11)

# CHECK-INST: bgt.l.t %s20, 8192
# CHECK-ENCODING: encoding: [0x00,0x20,0x00,0x00,0x00,0x94,0x31,0x19]
bgt.l.t %s20, 8192

# CHECK-INST: bgt.d.nt %s20, 20(, %s11)
# CHECK-ENCODING: encoding: [0x14,0x00,0x00,0x00,0x8b,0x94,0x21,0x1c]
bgt.d.nt %s20, 20(, %s11)

# CHECK-INST: blt.w.t %s20, 8192
# CHECK-ENCODING: encoding: [0x00,0x20,0x00,0x00,0x00,0x94,0x32,0x1b]
blt.w.t %s20, 8192

# CHECK-INST: blt.s.nt %s20, (, %s11)
# CHECK-ENCODING: encoding: [0x00,0x00,0x00,0x00,0x8b,0x94,0xa2,0x1c]
blt.s.nt %s20, (, %s11)

# CHECK-INST: bne.l.t %s20, 8192
# CHECK-ENCODING: encoding: [0x00,0x20,0x00,0x00,0x00,0x94,0x33,0x19]
bne.l.t %s20, 8192

# CHECK-INST: bne.d.nt %s20, 20(, %s11)
# CHECK-ENCODING: encoding: [0x14,0x00,0x00,0x00,0x8b,0x94,0x23,0x1c]
bne.d.nt %s20, 20(, %s11)

# CHECK-INST: beq.w.t %s20, 8192
# CHECK-ENCODING: encoding: [0x00,0x20,0x00,0x00,0x00,0x94,0x34,0x1b]
beq.w.t %s20, 8192

# CHECK-INST: beq.s.nt %s20, (, %s11)
# CHECK-ENCODING: encoding: [0x00,0x00,0x00,0x00,0x8b,0x94,0xa4,0x1c]
beq.s.nt %s20, (,%s11)

# CHECK-INST: bge.l.t 63, 8192
# CHECK-ENCODING: encoding: [0x00,0x20,0x00,0x00,0x00,0x3f,0x35,0x19]
bge.l.t 63, 8192

# CHECK-INST: bge.d.nt -64, 20(, %s11)
# CHECK-ENCODING: encoding: [0x14,0x00,0x00,0x00,0x8b,0x40,0x25,0x1c]
bge.d.nt -64, 20(, %s11)

# CHECK-INST: ble.w.t %s20, 8192
# CHECK-ENCODING: encoding: [0x00,0x20,0x00,0x00,0x00,0x94,0x36,0x1b]
ble.w.t %s20, 8192

# CHECK-INST: ble.s.nt %s20, (, %s11)
# CHECK-ENCODING: encoding: [0x00,0x00,0x00,0x00,0x8b,0x94,0xa6,0x1c]
ble.s.nt %s20, (,%s11)

# CHECK-INST: bnum.s.t %s20, 8192
# CHECK-ENCODING: encoding: [0x00,0x20,0x00,0x00,0x00,0x94,0xb7,0x1c]
bnum.s.t %s20, 8192

# CHECK-INST: bnum.d.nt %s20, 20(, %s11)
# CHECK-ENCODING: encoding: [0x14,0x00,0x00,0x00,0x8b,0x94,0x27,0x1c]
bnum.d.nt %s20, 20(, %s11)

# CHECK-INST: bnan.s.t %s20, 8192
# CHECK-ENCODING: encoding: [0x00,0x20,0x00,0x00,0x00,0x94,0xb8,0x1c]
bnan.s.t %s20, 8192

# CHECK-INST: bnan.d.nt %s20, 20(, %s11)
# CHECK-ENCODING: encoding: [0x14,0x00,0x00,0x00,0x8b,0x94,0x28,0x1c]
bnan.d.nt %s20, 20(, %s11)

# CHECK-INST: bgtnan.s.t %s20, 8192
# CHECK-ENCODING: encoding: [0x00,0x20,0x00,0x00,0x00,0x94,0xb9,0x1c]
bgtnan.s.t %s20, 8192

# CHECK-INST: bltnan.d.nt %s20, 20(, %s11)
# CHECK-ENCODING: encoding: [0x14,0x00,0x00,0x00,0x8b,0x94,0x2a,0x1c]
bltnan.d.nt %s20, 20(, %s11)

# CHECK-INST: bnenan.s.t %s20, 8192
# CHECK-ENCODING: encoding: [0x00,0x20,0x00,0x00,0x00,0x94,0xbb,0x1c]
bnenan.s.t %s20, 8192

# CHECK-INST: beqnan.d.nt %s20, 20(, %s11)
# CHECK-ENCODING: encoding: [0x14,0x00,0x00,0x00,0x8b,0x94,0x2c,0x1c]
beqnan.d.nt %s20, 20(, %s11)

# CHECK-INST: bgenan.s.t %s20, 8192
# CHECK-ENCODING: encoding: [0x00,0x20,0x00,0x00,0x00,0x94,0xbd,0x1c]
bgenan.s.t %s20, 8192

# CHECK-INST: blenan.d.nt %s20, 20(, %s11)
# CHECK-ENCODING: encoding: [0x14,0x00,0x00,0x00,0x8b,0x94,0x2e,0x1c]
blenan.d.nt %s20, 20(, %s11)
