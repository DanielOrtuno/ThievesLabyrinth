#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer LightsBuffer
// {
//
//   float3 vBufferData;                // Offset:    0 Size:    12
//   float fDissolve;                   // Offset:   12 Size:     4 [unused]
//   float3 vCameraPos;                 // Offset:   16 Size:    12
//   float fPadding;                    // Offset:   28 Size:     4 [unused]
//   
//   struct
//   {
//       
//       float4 vLightDesc;             // Offset:   32
//       float4 vColor;                 // Offset:   48
//
//   } tLights[16];                     // Offset:   32 Size:   512
//
// }
//
// cbuffer TextureBuffer
// {
//
//   float2 vScreenResolution;          // Offset:    0 Size:     8 [unused]
//   bool bHasTexture;                  // Offset:    8 Size:     4
//   bool bHasNormalMap;                // Offset:   12 Size:     4
//   bool bHasSpecular;                 // Offset:   16 Size:     4
//   float fMaskingValue;               // Offset:   20 Size:     4 [unused]
//   float fOutlineValue;               // Offset:   24 Size:     4 [unused]
//   float fTime;                       // Offset:   28 Size:     4 [unused]
//
// }
//
// cbuffer UtilityBuffer
// {
//
//   float4 vFlashColor;                // Offset:    0 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// filter                            sampler      NA          NA             s0      1 
// diffuseMap                        texture  float4          2d             t0      1 
// normalMap                         texture  float4          2d             t1      1 
// specularMap                       texture  float4          2d             t2      1 
// LightsBuffer                      cbuffer      NA          NA            cb0      1 
// TextureBuffer                     cbuffer      NA          NA            cb1      1 
// UtilityBuffer                     cbuffer      NA          NA            cb2      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_POSITION              0   xyzw        0      POS   float       
// TEXCOORD                 0   xy          1     NONE   float   xy  
// NDCPOS                   0     zw        1     NONE   float       
// WPOSITION                0   xyz         2     NONE   float   xyz 
// NORMAL                   0   xyz         3     NONE   float   xyz 
// TANGENT                  0   xyz         4     NONE   float   xyz 
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_TARGET                0   xyzw        0   TARGET   float   xyzw
//
ps_4_0
dcl_constantbuffer CB0[34], dynamicIndexed
dcl_constantbuffer CB1[2], immediateIndexed
dcl_constantbuffer CB2[1], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t1
dcl_resource_texture2d (float,float,float,float) t2
dcl_input_ps linear v1.xy
dcl_input_ps linear v2.xyz
dcl_input_ps linear v3.xyz
dcl_input_ps linear v4.xyz
dcl_output o0.xyzw
dcl_temps 8
if_nz cb1[0].z
  sample r0.xyzw, v1.xyxx, t0.xyzw, s0
else 
  mov r0.xyzw, l(0,0,0,0)
endif 
if_nz cb1[0].w
  sample r1.xyzw, v1.xyxx, t1.xyzw, s0
  mad r1.xyz, r1.xyzx, l(2.000000, 2.000000, 2.000000, 0.000000), l(-1.000000, -1.000000, -1.000000, 0.000000)
  dp3 r1.w, v4.xyzx, v3.xyzx
  mad r2.xyz, -r1.wwww, v3.xyzx, v4.xyzx
  mul r3.xyz, r2.yzxy, v3.zxyz
  mad r3.xyz, v3.yzxy, r2.zxyz, -r3.xyzx
  mul r3.xyz, r1.yyyy, r3.xyzx
  mad r1.xyw, r1.xxxx, r2.xyxz, r3.xyxz
  mad r1.xyz, r1.zzzz, v3.xyzx, r1.xywx
  dp3 r1.w, r1.xyzx, r1.xyzx
  rsq r1.w, r1.w
  mul r1.xyz, r1.wwww, r1.xyzx
else 
  mov r1.xyz, v3.xyzx
endif 
add r2.xyz, v2.xyzx, -cb0[1].xyzx
dp3 r1.w, r2.xyzx, r2.xyzx
rsq r1.w, r1.w
mul r2.xyz, r1.wwww, r2.xyzx
sample r3.xyzw, v1.xyxx, t2.xyzw, s0
mov r4.xyzw, l(0,0,0,1.000000)
mov r5.xyzw, l(0,0,0,0)
mov r1.w, cb1[1].x
mov r2.w, l(0)
loop 
  itof r6.x, r2.w
  ge r6.x, r6.x, cb0[0].x
  breakc_nz r6.x
  ishl r6.x, r2.w, l(1)
  add r6.yzw, -v2.xxyz, cb0[r6.x + 2].xxyz
  dp3 r7.x, r6.yzwy, r6.yzwy
  sqrt r7.x, r7.x
  div r6.yzw, r6.yyzw, r7.xxxx
  dp3_sat r6.y, r6.yzwy, r1.xyzx
  div_sat r6.z, r7.x, cb0[r6.x + 2].w
  add r6.z, -r6.z, l(1.000000)
  mul r7.xyzw, r6.yyyy, cb0[r6.x + 3].xyzw
  mul r6.y, r6.z, r6.z
  mad r4.xyzw, r6.yyyy, r7.xyzw, r4.xyzw
  if_nz r1.w
    add r6.yzw, v2.xxyz, -cb0[r6.x + 2].xxyz
    dp3 r7.x, r6.yzwy, r6.yzwy
    rsq r7.y, r7.x
    mul r6.yzw, r6.yyzw, r7.yyyy
    dp3 r7.y, r6.yzwy, r1.xyzx
    add r7.y, r7.y, r7.y
    mad r6.yzw, r1.xxyz, -r7.yyyy, r6.yyzw
    dp3_sat r6.y, r2.xyzx, -r6.yzwy
    log r6.y, r6.y
    mul r6.y, r6.y, l(150.000000)
    exp r6.y, r6.y
    sqrt r6.z, r7.x
    div_sat r6.z, r6.z, cb0[r6.x + 2].w
    add r6.z, -r6.z, l(1.000000)
    mul r7.xyzw, r3.xyzw, r6.yyyy
    mul r7.xyzw, r6.zzzz, r7.xyzw
    mad r5.xyzw, r7.xyzw, cb0[r6.x + 3].xyzw, r5.xyzw
  endif 
  iadd r2.w, r2.w, l(1)
endloop 
mul r1.xyzw, cb2[0].wwww, cb2[0].xyzw
mov_sat r4.xyzw, r4.xyzw
mad r1.xyzw, r0.xyzw, r4.xyzw, r1.xyzw
add r1.xyzw, r5.xyzw, r1.xyzw
mad o0.xyzw, r0.xyzw, cb0[0].yyyy, r1.xyzw
ret 
// Approximately 72 instruction slots used
#endif

const BYTE FlashPS[] =
{
     68,  88,  66,  67, 238, 159, 
     98, 218, 212,  34,  25, 117, 
    157, 129, 139, 246, 221, 107, 
    194,  98,   1,   0,   0,   0, 
     80,  14,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    112,   4,   0,   0,  72,   5, 
      0,   0, 124,   5,   0,   0, 
    212,  13,   0,   0,  82,  68, 
     69,  70,  52,   4,   0,   0, 
      3,   0,   0,   0,  80,   1, 
      0,   0,   7,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    255, 255,   0,   1,   0,   0, 
     12,   4,   0,   0, 252,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   1,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0,  14,   1,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0,  24,   1, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      2,   0,   0,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
     36,   1,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  49,   1,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  63,   1, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    102, 105, 108, 116, 101, 114, 
      0, 100, 105, 102, 102, 117, 
    115, 101,  77,  97, 112,   0, 
    110, 111, 114, 109,  97, 108, 
     77,  97, 112,   0, 115, 112, 
    101,  99, 117, 108,  97, 114, 
     77,  97, 112,   0,  76, 105, 
    103, 104, 116, 115,  66, 117, 
    102, 102, 101, 114,   0,  84, 
    101, 120, 116, 117, 114, 101, 
     66, 117, 102, 102, 101, 114, 
      0,  85, 116, 105, 108, 105, 
    116, 121,  66, 117, 102, 102, 
    101, 114,   0, 171, 171, 171, 
     36,   1,   0,   0,   5,   0, 
      0,   0, 152,   1,   0,   0, 
     32,   2,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     49,   1,   0,   0,   7,   0, 
      0,   0, 176,   2,   0,   0, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     63,   1,   0,   0,   1,   0, 
      0,   0, 216,   3,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     16,   2,   0,   0,   0,   0, 
      0,   0,  12,   0,   0,   0, 
      2,   0,   0,   0,  28,   2, 
      0,   0,   0,   0,   0,   0, 
     44,   2,   0,   0,  12,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,  56,   2, 
      0,   0,   0,   0,   0,   0, 
     72,   2,   0,   0,  16,   0, 
      0,   0,  12,   0,   0,   0, 
      2,   0,   0,   0,  28,   2, 
      0,   0,   0,   0,   0,   0, 
     83,   2,   0,   0,  28,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,  56,   2, 
      0,   0,   0,   0,   0,   0, 
     92,   2,   0,   0,  32,   0, 
      0,   0,   0,   2,   0,   0, 
      2,   0,   0,   0, 160,   2, 
      0,   0,   0,   0,   0,   0, 
    118,  66, 117, 102, 102, 101, 
    114,  68,  97, 116,  97,   0, 
      1,   0,   3,   0,   1,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 102,  68, 
    105, 115, 115, 111, 108, 118, 
    101,   0, 171, 171,   0,   0, 
      3,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 118,  67,  97, 109, 
    101, 114,  97,  80, 111, 115, 
      0, 102,  80,  97, 100, 100, 
    105, 110, 103,   0, 116,  76, 
    105, 103, 104, 116, 115,   0, 
    118,  76, 105, 103, 104, 116, 
     68, 101, 115,  99,   0, 171, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 118,  67, 
    111, 108, 111, 114,   0, 171, 
    100,   2,   0,   0, 112,   2, 
      0,   0,   0,   0,   0,   0, 
    128,   2,   0,   0, 112,   2, 
      0,   0,  16,   0,   0,   0, 
      5,   0,   0,   0,   1,   0, 
      8,   0,  16,   0,   2,   0, 
    136,   2,   0,   0,  88,   3, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,   0,   0, 
      0,   0, 108,   3,   0,   0, 
      0,   0,   0,   0, 124,   3, 
      0,   0,   8,   0,   0,   0, 
      4,   0,   0,   0,   2,   0, 
      0,   0, 136,   3,   0,   0, 
      0,   0,   0,   0, 152,   3, 
      0,   0,  12,   0,   0,   0, 
      4,   0,   0,   0,   2,   0, 
      0,   0, 136,   3,   0,   0, 
      0,   0,   0,   0, 166,   3, 
      0,   0,  16,   0,   0,   0, 
      4,   0,   0,   0,   2,   0, 
      0,   0, 136,   3,   0,   0, 
      0,   0,   0,   0, 179,   3, 
      0,   0,  20,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,  56,   2,   0,   0, 
      0,   0,   0,   0, 193,   3, 
      0,   0,  24,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,  56,   2,   0,   0, 
      0,   0,   0,   0, 207,   3, 
      0,   0,  28,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,  56,   2,   0,   0, 
      0,   0,   0,   0, 118,  83, 
     99, 114, 101, 101, 110,  82, 
    101, 115, 111, 108, 117, 116, 
    105, 111, 110,   0, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  98,  72, 
     97, 115,  84, 101, 120, 116, 
    117, 114, 101,   0,   0,   0, 
      1,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  98,  72,  97, 115, 
     78, 111, 114, 109,  97, 108, 
     77,  97, 112,   0,  98,  72, 
     97, 115,  83, 112, 101,  99, 
    117, 108,  97, 114,   0, 102, 
     77,  97, 115, 107, 105, 110, 
    103,  86,  97, 108, 117, 101, 
      0, 102,  79, 117, 116, 108, 
    105, 110, 101,  86,  97, 108, 
    117, 101,   0, 102,  84, 105, 
    109, 101,   0, 171, 171, 171, 
    240,   3,   0,   0,   0,   0, 
      0,   0,  16,   0,   0,   0, 
      2,   0,   0,   0, 252,   3, 
      0,   0,   0,   0,   0,   0, 
    118,  70, 108,  97, 115, 104, 
     67, 111, 108, 111, 114,   0, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  77, 105, 
     99, 114, 111, 115, 111, 102, 
    116,  32,  40,  82,  41,  32, 
     72,  76,  83,  76,  32,  83, 
    104,  97, 100, 101, 114,  32, 
     67, 111, 109, 112, 105, 108, 
    101, 114,  32,  49,  48,  46, 
     49,   0,  73,  83,  71,  78, 
    208,   0,   0,   0,   6,   0, 
      0,   0,   8,   0,   0,   0, 
    152,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  15,   0,   0,   0, 
    164,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   3,   3,   0,   0, 
    173,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,  12,   0,   0,   0, 
    180,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   7,   7,   0,   0, 
    190,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   3,   0, 
      0,   0,   7,   7,   0,   0, 
    197,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   4,   0, 
      0,   0,   7,   7,   0,   0, 
     83,  86,  95,  80,  79,  83, 
     73,  84,  73,  79,  78,   0, 
     84,  69,  88,  67,  79,  79, 
     82,  68,   0,  78,  68,  67, 
     80,  79,  83,   0,  87,  80, 
     79,  83,  73,  84,  73,  79, 
     78,   0,  78,  79,  82,  77, 
     65,  76,   0,  84,  65,  78, 
     71,  69,  78,  84,   0, 171, 
    171, 171,  79,  83,  71,  78, 
     44,   0,   0,   0,   1,   0, 
      0,   0,   8,   0,   0,   0, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  15,   0,   0,   0, 
     83,  86,  95,  84,  65,  82, 
     71,  69,  84,   0, 171, 171, 
     83,  72,  68,  82,  80,   8, 
      0,   0,  64,   0,   0,   0, 
     20,   2,   0,   0,  89,   8, 
      0,   4,  70, 142,  32,   0, 
      0,   0,   0,   0,  34,   0, 
      0,   0,  89,   0,   0,   4, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   2,   0,   0,   0, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   2,   0,   0,   0, 
      1,   0,   0,   0,  90,   0, 
      0,   3,   0,  96,  16,   0, 
      0,   0,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      0,   0,   0,   0,  85,  85, 
      0,   0,  88,  24,   0,   4, 
      0, 112,  16,   0,   1,   0, 
      0,   0,  85,  85,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   2,   0,   0,   0, 
     85,  85,   0,   0,  98,  16, 
      0,   3,  50,  16,  16,   0, 
      1,   0,   0,   0,  98,  16, 
      0,   3, 114,  16,  16,   0, 
      2,   0,   0,   0,  98,  16, 
      0,   3, 114,  16,  16,   0, 
      3,   0,   0,   0,  98,  16, 
      0,   3, 114,  16,  16,   0, 
      4,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      0,   0,   0,   0, 104,   0, 
      0,   2,   8,   0,   0,   0, 
     31,   0,   4,   4,  42, 128, 
     32,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  16, 
     16,   0,   1,   0,   0,   0, 
     70, 126,  16,   0,   0,   0, 
      0,   0,   0,  96,  16,   0, 
      0,   0,   0,   0,  18,   0, 
      0,   1,  54,   0,   0,   8, 
    242,   0,  16,   0,   0,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  21,   0, 
      0,   1,  31,   0,   4,   4, 
     58, 128,  32,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
     69,   0,   0,   9, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  16,  16,   0,   1,   0, 
      0,   0,  70, 126,  16,   0, 
      1,   0,   0,   0,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     50,   0,   0,  15, 114,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,  64,   0,   0, 
      0,  64,   0,   0,   0,  64, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 128, 191, 
      0,   0, 128, 191,   0,   0, 
    128, 191,   0,   0,   0,   0, 
     16,   0,   0,   7, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  18,  16,   0,   4,   0, 
      0,   0,  70,  18,  16,   0, 
      3,   0,   0,   0,  50,   0, 
      0,  10, 114,   0,  16,   0, 
      2,   0,   0,   0, 246,  15, 
     16, 128,  65,   0,   0,   0, 
      1,   0,   0,   0,  70,  18, 
     16,   0,   3,   0,   0,   0, 
     70,  18,  16,   0,   4,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   3,   0, 
      0,   0, 150,   4,  16,   0, 
      2,   0,   0,   0,  38,  25, 
     16,   0,   3,   0,   0,   0, 
     50,   0,   0,  10, 114,   0, 
     16,   0,   3,   0,   0,   0, 
    150,  20,  16,   0,   3,   0, 
      0,   0,  38,   9,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16, 128,  65,   0,   0,   0, 
      3,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      3,   0,   0,   0,  86,   5, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,  50,   0,   0,   9, 
    178,   0,  16,   0,   1,   0, 
      0,   0,   6,   0,  16,   0, 
      1,   0,   0,   0,  70,   8, 
     16,   0,   2,   0,   0,   0, 
     70,   8,  16,   0,   3,   0, 
      0,   0,  50,   0,   0,   9, 
    114,   0,  16,   0,   1,   0, 
      0,   0, 166,  10,  16,   0, 
      1,   0,   0,   0,  70,  18, 
     16,   0,   3,   0,   0,   0, 
     70,   3,  16,   0,   1,   0, 
      0,   0,  16,   0,   0,   7, 
    130,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     68,   0,   0,   5, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   1,   0, 
      0,   0, 246,  15,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     18,   0,   0,   1,  54,   0, 
      0,   5, 114,   0,  16,   0, 
      1,   0,   0,   0,  70,  18, 
     16,   0,   3,   0,   0,   0, 
     21,   0,   0,   1,   0,   0, 
      0,   9, 114,   0,  16,   0, 
      2,   0,   0,   0,  70,  18, 
     16,   0,   2,   0,   0,   0, 
     70, 130,  32, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  16,   0, 
      0,   7, 130,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  68,   0,   0,   5, 
    130,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      2,   0,   0,   0, 246,  15, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  69,   0,   0,   9, 
    242,   0,  16,   0,   3,   0, 
      0,   0,  70,  16,  16,   0, 
      1,   0,   0,   0,  70, 126, 
     16,   0,   2,   0,   0,   0, 
      0,  96,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   8, 
    242,   0,  16,   0,   4,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 128,  63,  54,   0, 
      0,   8, 242,   0,  16,   0, 
      5,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     54,   0,   0,   6, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     10, 128,  32,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     54,   0,   0,   5, 130,   0, 
     16,   0,   2,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  48,   0,   0,   1, 
     43,   0,   0,   5,  18,   0, 
     16,   0,   6,   0,   0,   0, 
     58,   0,  16,   0,   2,   0, 
      0,   0,  29,   0,   0,   8, 
     18,   0,  16,   0,   6,   0, 
      0,   0,  10,   0,  16,   0, 
      6,   0,   0,   0,  10, 128, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      4,   3,  10,   0,  16,   0, 
      6,   0,   0,   0,  41,   0, 
      0,   7,  18,   0,  16,   0, 
      6,   0,   0,   0,  58,   0, 
     16,   0,   2,   0,   0,   0, 
      1,  64,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,  11, 
    226,   0,  16,   0,   6,   0, 
      0,   0,   6,  25,  16, 128, 
     65,   0,   0,   0,   2,   0, 
      0,   0,   6, 137,  32,   6, 
      0,   0,   0,   0,   2,   0, 
      0,   0,  10,   0,  16,   0, 
      6,   0,   0,   0,  16,   0, 
      0,   7,  18,   0,  16,   0, 
      7,   0,   0,   0, 150,   7, 
     16,   0,   6,   0,   0,   0, 
    150,   7,  16,   0,   6,   0, 
      0,   0,  75,   0,   0,   5, 
     18,   0,  16,   0,   7,   0, 
      0,   0,  10,   0,  16,   0, 
      7,   0,   0,   0,  14,   0, 
      0,   7, 226,   0,  16,   0, 
      6,   0,   0,   0,  86,  14, 
     16,   0,   6,   0,   0,   0, 
      6,   0,  16,   0,   7,   0, 
      0,   0,  16,  32,   0,   7, 
     34,   0,  16,   0,   6,   0, 
      0,   0, 150,   7,  16,   0, 
      6,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     14,  32,   0,  10,  66,   0, 
     16,   0,   6,   0,   0,   0, 
     10,   0,  16,   0,   7,   0, 
      0,   0,  58, 128,  32,   6, 
      0,   0,   0,   0,   2,   0, 
      0,   0,  10,   0,  16,   0, 
      6,   0,   0,   0,   0,   0, 
      0,   8,  66,   0,  16,   0, 
      6,   0,   0,   0,  42,   0, 
     16, 128,  65,   0,   0,   0, 
      6,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128,  63, 
     56,   0,   0,  10, 242,   0, 
     16,   0,   7,   0,   0,   0, 
     86,   5,  16,   0,   6,   0, 
      0,   0,  70, 142,  32,   6, 
      0,   0,   0,   0,   3,   0, 
      0,   0,  10,   0,  16,   0, 
      6,   0,   0,   0,  56,   0, 
      0,   7,  34,   0,  16,   0, 
      6,   0,   0,   0,  42,   0, 
     16,   0,   6,   0,   0,   0, 
     42,   0,  16,   0,   6,   0, 
      0,   0,  50,   0,   0,   9, 
    242,   0,  16,   0,   4,   0, 
      0,   0,  86,   5,  16,   0, 
      6,   0,   0,   0,  70,  14, 
     16,   0,   7,   0,   0,   0, 
     70,  14,  16,   0,   4,   0, 
      0,   0,  31,   0,   4,   3, 
     58,   0,  16,   0,   1,   0, 
      0,   0,   0,   0,   0,  11, 
    226,   0,  16,   0,   6,   0, 
      0,   0,   6,  25,  16,   0, 
      2,   0,   0,   0,   6, 137, 
     32, 134,  65,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,  10,   0,  16,   0, 
      6,   0,   0,   0,  16,   0, 
      0,   7,  18,   0,  16,   0, 
      7,   0,   0,   0, 150,   7, 
     16,   0,   6,   0,   0,   0, 
    150,   7,  16,   0,   6,   0, 
      0,   0,  68,   0,   0,   5, 
     34,   0,  16,   0,   7,   0, 
      0,   0,  10,   0,  16,   0, 
      7,   0,   0,   0,  56,   0, 
      0,   7, 226,   0,  16,   0, 
      6,   0,   0,   0,  86,  14, 
     16,   0,   6,   0,   0,   0, 
     86,   5,  16,   0,   7,   0, 
      0,   0,  16,   0,   0,   7, 
     34,   0,  16,   0,   7,   0, 
      0,   0, 150,   7,  16,   0, 
      6,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
      0,   0,   0,   7,  34,   0, 
     16,   0,   7,   0,   0,   0, 
     26,   0,  16,   0,   7,   0, 
      0,   0,  26,   0,  16,   0, 
      7,   0,   0,   0,  50,   0, 
      0,  10, 226,   0,  16,   0, 
      6,   0,   0,   0,   6,   9, 
     16,   0,   1,   0,   0,   0, 
     86,   5,  16, 128,  65,   0, 
      0,   0,   7,   0,   0,   0, 
     86,  14,  16,   0,   6,   0, 
      0,   0,  16,  32,   0,   8, 
     34,   0,  16,   0,   6,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0, 150,   7, 
     16, 128,  65,   0,   0,   0, 
      6,   0,   0,   0,  47,   0, 
      0,   5,  34,   0,  16,   0, 
      6,   0,   0,   0,  26,   0, 
     16,   0,   6,   0,   0,   0, 
     56,   0,   0,   7,  34,   0, 
     16,   0,   6,   0,   0,   0, 
     26,   0,  16,   0,   6,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,  22,  67,  25,   0, 
      0,   5,  34,   0,  16,   0, 
      6,   0,   0,   0,  26,   0, 
     16,   0,   6,   0,   0,   0, 
     75,   0,   0,   5,  66,   0, 
     16,   0,   6,   0,   0,   0, 
     10,   0,  16,   0,   7,   0, 
      0,   0,  14,  32,   0,  10, 
     66,   0,  16,   0,   6,   0, 
      0,   0,  42,   0,  16,   0, 
      6,   0,   0,   0,  58, 128, 
     32,   6,   0,   0,   0,   0, 
      2,   0,   0,   0,  10,   0, 
     16,   0,   6,   0,   0,   0, 
      0,   0,   0,   8,  66,   0, 
     16,   0,   6,   0,   0,   0, 
     42,   0,  16, 128,  65,   0, 
      0,   0,   6,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
    128,  63,  56,   0,   0,   7, 
    242,   0,  16,   0,   7,   0, 
      0,   0,  70,  14,  16,   0, 
      3,   0,   0,   0,  86,   5, 
     16,   0,   6,   0,   0,   0, 
     56,   0,   0,   7, 242,   0, 
     16,   0,   7,   0,   0,   0, 
    166,  10,  16,   0,   6,   0, 
      0,   0,  70,  14,  16,   0, 
      7,   0,   0,   0,  50,   0, 
      0,  12, 242,   0,  16,   0, 
      5,   0,   0,   0,  70,  14, 
     16,   0,   7,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     10,   0,  16,   0,   6,   0, 
      0,   0,  70,  14,  16,   0, 
      5,   0,   0,   0,  21,   0, 
      0,   1,  30,   0,   0,   7, 
    130,   0,  16,   0,   2,   0, 
      0,   0,  58,   0,  16,   0, 
      2,   0,   0,   0,   1,  64, 
      0,   0,   1,   0,   0,   0, 
     22,   0,   0,   1,  56,   0, 
      0,   9, 242,   0,  16,   0, 
      1,   0,   0,   0, 246, 143, 
     32,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,  54,  32, 
      0,   5, 242,   0,  16,   0, 
      4,   0,   0,   0,  70,  14, 
     16,   0,   4,   0,   0,   0, 
     50,   0,   0,   9, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      4,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
      0,   0,   0,   7, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   5,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,  32,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     86, 133,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 116,   0, 
      0,   0,  72,   0,   0,   0, 
      8,   0,   0,   0,   0,   0, 
      0,   0,   5,   0,   0,   0, 
     47,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      5,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      7,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0
};